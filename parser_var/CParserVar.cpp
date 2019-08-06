/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp {

	char const
		CParserVar::STR_EMPTY[] = "empty";

	const char *CParserVar::idTypeToString(int index) {
		switch (index) {
		default:
		case TYPE_UNKNOWN:
			break;
		case TYPE_BOOL: return "TYPE_BOOL";
			//case INT32_TYPE: return "INT32_TYPE";
		case TYPE_NUMBER: return "TYPE_NUMBER";
		case TYPE_STRING: return "STRING TYPE";
		case TYPE_PROPERTY_GROUP: return "TYPE_PROPERTY_GROUP";

		case TYPE_ARRAY_BOOL: return "ARRAY BOOL TYPE";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case TYPE_ARRAY_NUMBER: return "ARRAY FLOAT TYPE";
		case TYPE_ARRAY_STRING: return "ARRAY STRING TYPE";
		case TYPE_ARRAY_PROPERTY_GROUP: return "ARRAY PROPERTY GROUP TYPE";
		}

		return "UNKNOWN";
	}

	CParserVar::CParserVar() {
		this->_m_pvariableName = "pvar_noname";
		this->p_end_data = NULL;
		this->p_data = NULL;
		this->size_data = 0;
		this->p_ini_data = NULL;
		this->_m_iType = CParserVar::TYPE_UNKNOWN;
		this->m_isParsed = false;
	}

	virtual std::string & CParserVar::cpp2json() {
		result_json = "//no data:\n{}\n";
		return result_json;
	}

	virtual CParserVar * CParserVar::newData() {
		return NULL;
	}

	virtual std::string & CParserVar::getStrValue(int ident, uint32_t flags) {
		this->str_value = "??";
		return str_value;
	}

	virtual void CParserVar::add(CParserVar * s) {}



	void CParserVar::setParsed(bool parsed) {
		m_isParsed = parsed;
	}

	bool CParserVar::isParsed() const {
		return m_isParsed;
	}

	virtual CParserVar::~CParserVar() {

	}
};

