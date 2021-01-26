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

		case JSON_VAR_TYPE_VECTOR_BOOLEAN: return "VECTOR BOOL TYPE";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case JSON_VAR_TYPE_VECTOR_NUMBER: return "VECTOR FLOAT TYPE";
		case JSON_VAR_TYPE_VECTOR_STRING: return "VECTOR STRING TYPE";
		case JSON_VAR_TYPE_VECTOR_OBJECT: return "VECTOR PROPERTY GROUP TYPE";

		case JSON_VAR_TYPE_MAP_STRING: return "MAP STRING TYPE";
		}

		return "UNKNOWN";
	}

	JsonVar::JsonVar() {
		this->variable_name = "";
		this->p_end_data = NULL;
		this->p_data = NULL;
		this->size_data = 0;
		this->p_ini_data = NULL;
		this->type = JsonVar::JSON_VAR_TYPE_UNKNOWN;
		this->is_parsed = false;
	}

	std::string & JsonVar::toString() {
		result_json = "//no data:\n{}\n";
		return result_json;
	}

	JsonVar * JsonVar::newData() {
		return NULL;
	}

	std::string & JsonVar::getStrValue(int ident, uint32_t flags) {
		this->str_value = "??";
		return str_value;
	}

	void JsonVar::add(JsonVar * s) {}



	void JsonVar::setParsed(bool parsed) {
		is_parsed = parsed;
	}

	bool JsonVar::isParsed() const {
		return is_parsed;
	}

	JsonVar::~JsonVar() {

	}
};

