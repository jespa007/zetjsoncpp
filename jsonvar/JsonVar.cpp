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
		case JSON_VAR_TYPE_BOOLEAN: return "JsonVarBoolean";
			//case INT32_TYPE: return "INT32_TYPE";
		case JSON_VAR_TYPE_NUMBER: return "JsonVarNumber";
		case JSON_VAR_TYPE_STRING: return "JsonVarString";
		case JSON_VAR_TYPE_OBJECT: return "JsonVarObject";

		case JSON_VAR_TYPE_VECTOR_OF_BOOLEANS: return "JsonVarVectorBoolean";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case JSON_VAR_TYPE_VECTOR_OF_NUMBERS: return "JsonVarVectorNumber";
		case JSON_VAR_TYPE_VECTOR_OF_STRINGS: return "JsonVarVectorString";
		case JSON_VAR_TYPE_VECTOR_OF_OBJECTS: return "JsonVarVectorObject";

		case JSON_VAR_TYPE_MAP_OF_BOOLEANS: return "JsonVarMapBoolean";
		case JSON_VAR_TYPE_MAP_OF_NUMBERS: return "JsonVarMapNumber";
		case JSON_VAR_TYPE_MAP_OF_STRINGS: return "JsonVarMapString";
		case JSON_VAR_TYPE_MAP_OF_OBJECTS: return "JsonVarMapObject";
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

	JsonVar *JsonVar::newJsonVar(){
		return NULL;
	}

	JsonVar *JsonVar::newJsonVar(const std::string & key){
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

