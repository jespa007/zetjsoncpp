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
		case JSON_VAR_TYPE_BOOLEAN: return "TYPE_BOOLEAN";
			//case INT32_TYPE: return "INT32_TYPE";
		case JSON_VAR_TYPE_NUMBER: return "TYPE_NUMBER";
		case JSON_VAR_TYPE_STRING: return "STRING TYPE";
		case JSON_VAR_TYPE_OBJECT: return "TYPE_OBJECT";

		case JSON_VAR_TYPE_VECTOR_OF_BOOLEANS: return "VECTOR BOOL TYPE";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case JSON_VAR_TYPE_VECTOR_OF_NUMBERS: return "VECTOR FLOAT TYPE";
		case JSON_VAR_TYPE_VECTOR_OF_STRINGS: return "VECTOR STRING TYPE";
		case JSON_VAR_TYPE_VECTOR_OF_OBJECTS: return "VECTOR PROPERTY GROUP TYPE";

		case JSON_VAR_TYPE_MAP_OF_BOOLEANS: return "MAP BOOLEAN TYPE";
		case JSON_VAR_TYPE_MAP_OF_NUMBERS: return "MAP NUMBER TYPE";
		case JSON_VAR_TYPE_MAP_OF_STRINGS: return "MAP STRING TYPE";
		case JSON_VAR_TYPE_MAP_OF_OBJECTS: return "MAP OBJECT TYPE";
		}

		return "UNKNOWN";
	}

	JsonVar::JsonVar() {
		this->__js_variable_name__ = "";
		this->__js_ptr_data_end__ = NULL;
		this->__js_ptr_data_start__ = NULL;
		this->__js_size_data__ = 0;
		this->__js_type__ = JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		this->__js_is_parsed__ = false;
	}

	JsonVar *JsonVar::newData(){
		return NULL;
	}

	JsonVar *JsonVar::newData(const std::string & key){
		return NULL;
	}

	const char *JsonVar::toTypeStr(){
		return idTypeToString(this->__js_type__);
	}

	std::string JsonVar::toStringFormatted(int ident, uint16_t properties) {
		return "";
	}

	std::string JsonVar::toString() {
		return toStringFormatted(0,0);
	}

	void JsonVar::setParsed(bool parsed) {
		__js_is_parsed__ = parsed;
	}

	bool JsonVar::isParsed() const {
		return __js_is_parsed__;
	}

	JsonVar::~JsonVar() {

	}
};

