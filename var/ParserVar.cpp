/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp {

	char const
		ParserVar::STR_EMPTY[] = "empty";

	const char *ParserVar::idTypeToString(int index) {
		switch (index) {
		default:
		case TYPE_UNKNOWN:
			break;
		case TYPE_BOOLEAN: return "TYPE_BOOLEAN";
			//case INT32_TYPE: return "INT32_TYPE";
		case TYPE_NUMBER: return "TYPE_NUMBER";
		case TYPE_STRING: return "STRING TYPE";
		case TYPE_OBJECT: return "TYPE_OBJECT";

		case TYPE_ARRAY_BOOLEAN: return "ARRAY BOOL TYPE";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case TYPE_ARRAY_NUMBER: return "ARRAY FLOAT TYPE";
		case TYPE_ARRAY_STRING: return "ARRAY STRING TYPE";
		case TYPE_OBJECT_ARRAY: return "ARRAY PROPERTY GROUP TYPE";
		}

		return "UNKNOWN";
	}

	ParserVar::ParserVar() {
		this->variable_name = "";
		this->p_end_data = NULL;
		this->p_data = NULL;
		this->size_data = 0;
		this->p_ini_data = NULL;
		this->type = ParserVar::TYPE_UNKNOWN;
		this->is_parsed = false;
	}

	std::string & ParserVar::toString() {
		result_json = "//no data:\n{}\n";
		return result_json;
	}

	ParserVar * ParserVar::newData() {
		return NULL;
	}

	std::string & ParserVar::getStrValue(int ident, uint32_t flags) {
		this->str_value = "??";
		return str_value;
	}

	void ParserVar::add(ParserVar * s) {}



	void ParserVar::setParsed(bool parsed) {
		is_parsed = parsed;
	}

	bool ParserVar::isParsed() const {
		return is_parsed;
	}

	ParserVar::~ParserVar() {

	}
};

