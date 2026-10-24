/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

#define ZJ_FORMAT_OUTPUT_IDENT(str_value,ident)  for (int k = 0; k < (ident); k++) str_value += "\t";
#define ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident) \
	str_value += "\n";\
	for (int k = 0; k < (ident); k++)	str_value += "\t";

namespace zetjsoncpp{

	typedef struct{

	}TestVoid;

	struct SerializeObjectContext {
	    std::string *result;
	    int indent;
	    bool minimized;
	    bool discard_non_serialized;
	    int serialized_count;
	};



	void serialize_json_var(
		std::string & _str_result
		,JsonVar *_json_var
		,int _ident
		,bool _minimized
		,bool _discard_non_serialized
	);

	template<typename _T>
	void serialize_json_var_map(
		std::string & _str_result
		,_T * _json_var_map
		,int _ident
		,bool _minimized
		,bool _discard_non_serialized
	) {

		_str_result += "{";

		if (_minimized==false){
			ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident+1);
		}

		int j=0;
		for (auto it=_json_var_map->begin();it !=_json_var_map->end();it++) {

			auto element=_json_var_map->getJsonVarPtr(it->first);

			// discard element
			if(_discard_non_serialized==true && element->isDeserialized() == false){
				continue;
			}

			if (j > 0){
				if (_minimized==false){
					ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident+1);
				}
				_str_result += ",";
			}

			_str_result += "\""+it->first +"\":";
			serialize_json_var(
				_str_result
				,element
				,_ident+1
				,_minimized
				,_discard_non_serialized
			);

			j++;

		}

		if (_minimized==false){
			ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident);
		}
		_str_result += "}";
	}

	template<typename _T>
	void serialize_json_var_array(
		std::string & _str_result
		, _T * _json_var_array
		,int _ident
		,bool _minimized
		,bool _discard_non_serialized
	){

		_str_result+="[";

		if (_minimized==false && _json_var_array->getType() !=JsonVarType::JSON_VAR_TYPE_ARRAY_OF_OBJECTS){
			ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident+1);
		}

		unsigned j=0;
		for (unsigned i = 0; i < _json_var_array->size(); i++) {

			auto element=_json_var_array->getJsonVarPtr(i);

			// discard element
			if(_discard_non_serialized==true && element->isDeserialized() == false){
				continue;
			}

			if (j > 0) {
				_str_result += ",";
			}

			serialize_json_var(
				_str_result
				,element
				,_ident
				,_minimized
				,_discard_non_serialized
			);

			j++;
		}
		if (_minimized==false && _json_var_array->getType() !=JsonVarType::JSON_VAR_TYPE_ARRAY_OF_OBJECTS){
			ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident);
		}
		_str_result+="]";
	}

	static void serializeObjectFieldCallback(
	    const JsonVar *_field
	    ,void *_context
	) {
	    auto *ctx = static_cast<SerializeObjectContext *>(_context);

	    if(ctx->discard_non_serialized
	        && !_field->isDeserialized()) {
	        return;
	    }

	    std::string &result = *ctx->result;

	    if(ctx->serialized_count > 0) {
	        result += ",";
	    }

	    if(!ctx->minimized) {
	        result += "\n";

	        for(int i = 0; i <= ctx->indent; i++) {
	            result += "\t";
	        }
	    }

	    result += "\"";
	    result += _field->getVariableName();
	    result += "\":";

	    // Serialize the actual field value
	    serialize_json_var(
	        result
	        ,const_cast<JsonVar *>(_field)
	        ,ctx->indent + 1
	        ,ctx->minimized
	        ,ctx->discard_non_serialized
	    );

	    ctx->serialized_count++;
	}

	void serialize_json_var_object(
	    std::string &_str_result
	    ,JsonVar *_json_var
	    ,int _indent
	    ,bool _minimized
	    ,bool _discard_non_serialized
	) {
	    if(_json_var->getType() != JsonVarType::JSON_VAR_TYPE_OBJECT) {
	        throw std::runtime_error("Expected JSON object");
	    }

	    _str_result += "{";

	    SerializeObjectContext ctx = {
	        &_str_result
	        ,_indent
	        ,_minimized
	        ,_discard_non_serialized
	        ,0
	    };

	    // Invoke the const visitation interface
	    static_cast<const JsonVar *>(_json_var)->forEachField(
	        serializeObjectFieldCallback
	        ,&ctx
	    );

	    if(!_minimized && ctx.serialized_count > 0) {
	        _str_result += "\n";

	        for(int i = 0; i < _indent; i++) {
	            _str_result += "\t";
	        }
	    }

	    _str_result += "}";
	}

	void serialize_json_var(
			std::string & _str_result
			,JsonVar *_json_var
			,int _ident
			,bool _minimized
			,bool _discard_non_serialized
	){
		switch(_json_var->getType()){
		default:
			break;
		case JSON_VAR_TYPE_BOOLEAN:
			_str_result+=((BooleanJsonVar *)_json_var)->getValue() ?"true":"false";
			break;
		case JSON_VAR_TYPE_NUMBER:
			_str_result+=string_utils::floatToString(((NumberJsonVar *)_json_var)->getValue());
			break;
		case JSON_VAR_TYPE_STRING:
			_str_result+=std::string("\"") + ((StringJsonVar *)_json_var)->getValue() + "\"";
			break;
		case JSON_VAR_TYPE_OBJECT:
			serialize_json_var_object(
				_str_result
				, _json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_ARRAY_OF_BOOLEANS:
			serialize_json_var_array<ArrayBooleanJsonVar>(
				_str_result
				, (ArrayBooleanJsonVar *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_ARRAY_OF_NUMBERS:
			serialize_json_var_array<ArrayNumberJsonVar>(
				_str_result
				,(ArrayNumberJsonVar *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_ARRAY_OF_STRINGS:
			serialize_json_var_array<ArrayStringJsonVar>(
				_str_result
				,(ArrayStringJsonVar *)(_json_var)
				,_ident,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_ARRAY_OF_OBJECTS:
			serialize_json_var_array<ArrayObjectJsonVar<TestVoid>>(
				_str_result
				,(ArrayObjectJsonVar<TestVoid> *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_BOOLEANS:
			serialize_json_var_map<MapBooleanJsonVar>(
				_str_result
				, (MapBooleanJsonVar *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_NUMBERS:
			serialize_json_var_map<MapNumberJsonVar>(
				_str_result
				, (MapNumberJsonVar *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_STRINGS:
			serialize_json_var_map<MapStringJsonVar>(
				_str_result
				, (MapStringJsonVar *)_json_var
				,_ident,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_OBJECTS:
			serialize_json_var_map<MapObjectJsonVar<TestVoid>>(
				_str_result
				, (MapObjectJsonVar<TestVoid> *)_json_var
				,_ident,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_ARRAY_OF_STRINGS:
			serialize_json_var_map<MapArrayStringJsonVar>(
				_str_result
				, (MapArrayStringJsonVar *)_json_var
				,_ident,_minimized
				,_discard_non_serialized
			);
			break;
		}
	}

	std::string serialize(
			JsonVar *  _json_var
			,bool _minimized
			,bool _discard_non_serialized
	){
		std::string serialized_var="";

		serialize_json_var(
			serialized_var
			,_json_var
			,0
			,_minimized
			,_discard_non_serialized
		);

		return serialized_var;
	}

	std::string serialize(
		JsonVar & _json_var
		, bool _minimized
		, bool _discard_non_serialized
	){
	    return serialize(
	        &_json_var
	        ,_minimized
	        ,_discard_non_serialized
	    );
	}


}
