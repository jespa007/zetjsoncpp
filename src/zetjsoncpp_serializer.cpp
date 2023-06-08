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
	void serialize_json_var_vector(
		std::string & _str_result
		, _T * _json_var_vector
		,int _ident
		,bool _minimized
		,bool _discard_non_serialized
	){

		_str_result+="[";

		if (_minimized==false && _json_var_vector->getType() !=JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS){
			ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident+1);
		}

		unsigned j=0;
		for (unsigned i = 0; i < _json_var_vector->size(); i++) {

			auto element=_json_var_vector->getJsonVarPtr(i);

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
		if (_minimized==false && _json_var_vector->getType() !=JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS){
			ZJ_FORMAT_OUTPUT_NEW_LINE(_str_result,_ident);
		}
		_str_result+="]";
	}

	void serialize_json_var_object(
		std::string & _str_result
		, JsonVar *_json_var
		, int _ident
		, bool _minimized
		, bool _discard_non_serialized
	){
		int k=0;

		if(_json_var->getType() != JsonVarType::JSON_VAR_TYPE_OBJECT){
			throw std::runtime_error(
				string_utils::format(
						"Expected json object but it was %s"
						,_json_var->getTypeStr()
				)
			);
		}

		_str_result += "{";

		if (_minimized == false){
			_str_result += "\n";
		}

		char *aux_p = (char *)_json_var->getPtrDataStart();
		char *end_p = (char *)_json_var->getPtrDataEnd();
		int i=0;
		for (; aux_p < end_p; k++) {
			JsonVar * p_sv = (JsonVar *)aux_p;
			bool serialize=p_sv != NULL && p_sv->isDeserialized();

			// show non serialized
			if(p_sv != NULL && serialize==false && _discard_non_serialized==false){
				serialize=true;
			}

			if (serialize == true) {

				if (_minimized==false){
					for (int i = 0; i <= (_ident); i++){
						_str_result += "\t";
					}
				}

				if (i > 0){
					_str_result += ",";
				}

				_str_result += "\"" + p_sv->getVariableName()+ "\":";

				switch (p_sv->getType())// == )
				{
				case JsonVarType::JSON_VAR_TYPE_BOOLEAN:
				case JsonVarType::JSON_VAR_TYPE_NUMBER:
				case JsonVarType::JSON_VAR_TYPE_STRING:
					serialize_json_var(
						_str_result
						,p_sv
						,0
						,_minimized
						,_discard_non_serialized
					);
					break;

				case JsonVarType::JSON_VAR_TYPE_OBJECT:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS:
					if (_minimized==false){
						_str_result += "\n";
						for (int i = 0; i <= _ident; i++){
							_str_result += "\t";
						}
					}
					serialize_json_var(
						_str_result
						,p_sv
						,_ident+1
						, _minimized
						,_discard_non_serialized
					);
					break;
				}

				if (_minimized == false){
					_str_result += "\n";
				}

				i++;
			}
			aux_p += p_sv->getSizeData();
		}

		if (_minimized == false){
			for (int i = 0; i < _ident; i++){
				_str_result += "\t";
			}
		}

		_str_result += "}";

		if (_minimized == false){
			"\n";
		}
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
			_str_result+=(*((BooleanJsonVar<> *)_json_var)==true)?"true":"false";
			break;
		case JSON_VAR_TYPE_NUMBER:
			_str_result+=string_utils::floatToString(*((NumberJsonVar<> *)_json_var));
			break;
		case JSON_VAR_TYPE_STRING:
			_str_result+=std::string("\"") + *((StringJsonVar<> *)_json_var) + "\"";
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
		case JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
			serialize_json_var_vector<ArrayBooleanJsonVar<>>(
				_str_result
				, (ArrayBooleanJsonVar<> *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
			serialize_json_var_vector<ArrayJsonVarNumber<>>(
				_str_result
				,(ArrayJsonVarNumber<> *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_VECTOR_OF_STRINGS:
			serialize_json_var_vector<ArrayStringJsonVar<>>(
				_str_result
				,(ArrayStringJsonVar<> *)(_json_var)
				,_ident,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
			serialize_json_var_vector<ArrayObjectJsonVar<TestVoid>>(
				_str_result
				,(ArrayObjectJsonVar<TestVoid> *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_BOOLEANS:
			serialize_json_var_map<MapBooleanJsonVar<>>(
				_str_result
				, (MapBooleanJsonVar<> *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_NUMBERS:
			serialize_json_var_map<MapNumberJsonVar<>>(
				_str_result
				, (MapNumberJsonVar<> *)_json_var
				,_ident
				,_minimized
				,_discard_non_serialized
			);
			break;
		case JSON_VAR_TYPE_MAP_OF_STRINGS:
			serialize_json_var_map<MapStringJsonVar<>>(
				_str_result
				, (MapStringJsonVar<> *)_json_var
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
		}
	}

	std::string serialize(
			JsonVar *_json_var
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


}
