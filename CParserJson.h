#pragma once


// static zetjsoncpp

namespace zetjsoncpp {


	template <typename _T>
	class CParserJson : public CParser<_T> {

		CParserVar *findProperty(CParserVar * c_data, char *property_name);
		void setPropertiesParsedToFalse(CParserVar * c_data);
		//void printJsonError(char *m_start_ptr, char *m_current_ptr, int column, const char *error_message);
		bool bothAreTypeNumbers(int type1, int type2);
		int json2cpp(const char * start_str, CParserVar *c_data, int level = 0, bool ignore_warnings = false);

	public:

		CParserJson() {}

		virtual bool evalString(const string & m_expression, int level = 0, bool ignore_warnings = false) {

			this->m_line = 1;
			this->root_struct_field->destroy(); // destroy previous elements!

			return (json2cpp((const char *)m_expression.c_str(), CParser<_T>::root_struct_field, 0, ignore_warnings) > 0);
		}

		const char *getError();


		virtual ~CParserJson() {}
	};



	#include "CParserJson.cxx"
};


