/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp {

	char const
		JsonVar::STR_EMPTY[] = "empty";

	const char *JsonVar::idTypeToString(int index) {
		switch (index) {
		default:
		case JSON_VAR_TYPE_UNKNOWN:
			break;
		case JSON_VAR_TYPE_BOOLEAN: return "BooleanJsonVar";
			//case INT32_TYPE: return "INT32_TYPE";
		case JSON_VAR_TYPE_NUMBER: return "NumberJsonVar";
		case JSON_VAR_TYPE_STRING: return "StringJsonVar";
		case JSON_VAR_TYPE_OBJECT: return "ObjectJsonVar";

		case JSON_VAR_TYPE_VECTOR_OF_BOOLEANS: return "ArrayBooleanJsonVar";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case JSON_VAR_TYPE_VECTOR_OF_NUMBERS: return "ArrayJsonVarNumber";
		case JSON_VAR_TYPE_VECTOR_OF_STRINGS: return "ArrayStringJsonVar";
		case JSON_VAR_TYPE_VECTOR_OF_OBJECTS: return "ArrayObjectJsonVar";

		case JSON_VAR_TYPE_MAP_OF_BOOLEANS: return "MapBooleanJsonVar";
		case JSON_VAR_TYPE_MAP_OF_NUMBERS: return "MapNumberJsonVar";
		case JSON_VAR_TYPE_MAP_OF_STRINGS: return "MapStringJsonVar";
		case JSON_VAR_TYPE_MAP_OF_OBJECTS: return "MapObjectJsonVar";
		}

		return "UNKNOWN";
	}

	JsonVar::JsonVar() {
		memset(this->__zj_variable_name__,0,sizeof(this->__zj_variable_name__));// = "";
		this->__zj_ptr_data_end__ = NULL;
		this->__zj_ptr_data_start__ = NULL;
		this->__zj_size_data__ = 0;
		this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		this->__zj_is_parsed__ = false;
	}

	JsonVar *JsonVar::newJsonVar(){
		throw std::runtime_error("internal error: newJsonVar not implemented");
		return NULL;
	}

	JsonVar *JsonVar::newJsonVar(const std::string & key){
		throw std::runtime_error("internal error: newJsonVar not implemented");
	}

	const char *JsonVar::getTypeStr(){
		return idTypeToString(this->__zj_type__);
	}

	void JsonVar::setParsed(bool parsed) {
		__zj_is_parsed__ = parsed;
	}

	bool JsonVar::isDeserialized() const {
		return __zj_is_parsed__;
	}

	JsonVar::~JsonVar() {

	}
}

