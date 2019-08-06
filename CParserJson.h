/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once


// static zetjsoncpp

namespace zetjsoncpp {

	//typedef void (* tJsonErrorCallback)(const char *file, int line, const char *str,const char *where);
	//typedef void (* tJsonWarningCallback)(const char *file, int line, const char *str);

	// define my exceptions


	template <typename _T>
	class CParserJson : public CParser<_T> {

		CParserVar *findProperty(CParserVar * c_data, char *property_name);
		void setPropertiesParsedToFalse(CParserVar * c_data);
		//void printJsonError(char *m_start_ptr, char *m_current_ptr, int column, const char *error_message);
		bool bothAreTypeNumbers(int type1, int type2);
		int json2cpp(const char * start_str, CParserVar *c_data, int level = 0, bool ignore_warnings = false);

	public:

		CParserJson() {}

		virtual void evalString(const std::string & m_expression, int level = 0, bool ignore_warnings = false) {

			this->m_line = 1;
			this->root_struct_field->destroy(); // destroy previous elements!

			json2cpp((const char *)m_expression.c_str(), CParser<_T>::root_struct_field, 0, ignore_warnings);
		}

		virtual ~CParserJson() {}
	};

	//void set_json_error_callback(tJsonErrorCallback _error_callback);
	//void set_json_warning_callback(tJsonWarningCallback _warning_callback);

	#include "CParserJson.inc"
};


