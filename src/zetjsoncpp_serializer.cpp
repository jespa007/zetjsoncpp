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

	void serialize_json_var(
		std::string & _str_result
		,const JsonVar *_json_var
		,int _ident
		,bool _minimized
		,bool _discard_non_serialized
	);

	struct SerializeContext {
	    std::string *result;
	    int indent;
	    bool minimized;
	    bool discard_non_serialized;
	    int serialized_count;
	};

	static void serializeArrayElementCallback(
	    const JsonVar *_element
	    ,void *_context
	) {
	    auto *ctx = static_cast<SerializeContext *>(_context);


	    if(ctx->serialized_count > 0) {
	        *ctx->result += ",";
	    }

	    serialize_json_var(
	        *ctx->result
	        ,_element
	        ,ctx->indent
	        ,ctx->minimized
	        ,ctx->discard_non_serialized
	    );

	    ctx->serialized_count++;
	}

	static void serializeMapEntryCallback(
	    const std::string &_key
	    ,const JsonVar *_element
	    ,void *_context
	) {
	    auto *ctx = static_cast<SerializeContext *>(_context);

	    std::string &result = *ctx->result;

	    if(ctx->serialized_count > 0) {

	        if(!ctx->minimized) {
	            ZJ_FORMAT_OUTPUT_NEW_LINE(result,ctx->indent+1);
	        }

	        result += ",";
	    }

	    result += "\"" + _key + "\":";

	    serialize_json_var(
	        result
	        ,_element
	        ,ctx->indent+1
	        ,ctx->minimized
	        ,ctx->discard_non_serialized
	    );

	    ctx->serialized_count++;
	}

	void serialize_json_var_map(
	    std::string &_str_result
	    ,const JsonVar *_json_var
	    ,int _ident
	    ,bool _minimized
	    ,bool _discard_non_serialized
	) {
	    _str_result += "{";

	    if(!_minimized) {
	        ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident+1);
	    }

	    SerializeContext ctx = {
	        &_str_result
	        ,_ident
	        ,_minimized
	        ,_discard_non_serialized
	        ,0
	    };

	    _json_var->forEachMapEntry(
	        serializeMapEntryCallback
	        ,&ctx
	    );

	    if(!_minimized) {
	        ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident);
	    }

	    _str_result += "}";
	}

	void serialize_json_var_array(
	    std::string &_str_result
	    ,const JsonVar *_json_var
	    ,int _ident
	    ,bool _minimized
	    ,bool _discard_non_serialized
	) {
	    _str_result += "[";

	    bool multiline =
	        !_minimized
	        && _json_var->getType() != JSON_VAR_TYPE_ARRAY_OF_OBJECTS;

	    if(multiline) {
	        ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident+1);
	    }

	    SerializeContext ctx = {
	        &_str_result
	        ,_ident
	        ,_minimized
	        ,_discard_non_serialized
	        ,0
	    };

	    _json_var->forEachArrayElement(
	        serializeArrayElementCallback
	        ,&ctx
	    );

	    if(multiline) {
	        ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident);
	    }

	    _str_result += "]";
	}

	static void serializeObjectFieldCallback(
	    const JsonVar *_field
	    ,void *_context
	) {
	    auto *ctx = static_cast<SerializeContext *>(_context);

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
	        ,_field
	        ,ctx->indent + 1
	        ,ctx->minimized
	        ,ctx->discard_non_serialized
	    );

	    ctx->serialized_count++;
	}

	void serialize_json_var_object(
	    std::string &_str_result
	    ,const JsonVar *_json_var
	    ,int _indent
	    ,bool _minimized
	    ,bool _discard_non_serialized
	) {
	    if(_json_var->getType() != JsonVarType::JSON_VAR_TYPE_OBJECT) {
	        throw std::runtime_error("Expected JSON object");
	    }

	    _str_result += "{";

	    SerializeContext ctx = {
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
	    std::string &_str_result
	    ,const JsonVar *_json_var
	    ,int _ident
	    ,bool _minimized
	    ,bool _discard_non_serialized
	) {
	    switch(_json_var->getType()) {

	    case JSON_VAR_TYPE_BOOLEAN:
	        _str_result +=
	            static_cast<const BooleanJsonVar *>(_json_var)
	                ->getValue() ? "true" : "false";
	        break;

	    case JSON_VAR_TYPE_NUMBER:
	        _str_result += string_utils::doubleToString(
	            static_cast<const NumberJsonVar *>(_json_var)
	                ->getValue()
	        );
	        break;

	    case JSON_VAR_TYPE_STRING:
	        _str_result += std::string("\"")
	            + static_cast<const StringJsonVar *>(_json_var)
	                ->getValue()
	            + "\"";
	        break;

	    case JSON_VAR_TYPE_OBJECT:

	        serialize_json_var_object(
	            _str_result
	            ,_json_var
	            ,_ident
	            ,_minimized
	            ,_discard_non_serialized
	        );
	        break;

	    case JSON_VAR_TYPE_ARRAY_OF_BOOLEANS:
	    case JSON_VAR_TYPE_ARRAY_OF_NUMBERS:
	    case JSON_VAR_TYPE_ARRAY_OF_STRINGS:
	    case JSON_VAR_TYPE_ARRAY_OF_OBJECTS:

	        serialize_json_var_array(
	            _str_result
	            ,_json_var
	            ,_ident
	            ,_minimized
	            ,_discard_non_serialized
	        );
	        break;

	    case JSON_VAR_TYPE_MAP_OF_BOOLEANS:
	    case JSON_VAR_TYPE_MAP_OF_NUMBERS:
	    case JSON_VAR_TYPE_MAP_OF_STRINGS:
	    case JSON_VAR_TYPE_MAP_OF_OBJECTS:
	    case JSON_VAR_TYPE_MAP_OF_ARRAY_OF_STRINGS:

	        serialize_json_var_map(
	            _str_result
	            ,_json_var
	            ,_ident
	            ,_minimized
	            ,_discard_non_serialized
	        );
	        break;

	    default:
	        throw std::runtime_error("Unsupported JSON variable type");
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
