/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#ifndef __CPARSER_JSON_H__
#define __CPARSER_JSON_H__

#define ZJ_ERROR	-1

namespace zetjsoncpp {

	template <typename _T>
	class CParserJson : public CParser<_T> {

		CParserVar *findProperty(CParserVar * c_data, char *property_name);
		void setPropertiesParsedToFalse(CParserVar * c_data);
		bool bothAreTypeNumbers(int type1, int type2);
		int json2cpp(const char * start_str, CParserVar *c_data, int level = 0, bool ignore_warnings = false);

	public:

		CParserJson() {}

		virtual bool evalString(const std::string & m_expression, int level = 0, bool ignore_warnings = false) {

			this->m_line = 1;
			this->root_struct_field->destroy(); // destroy previous elements!

			return (json2cpp((const char *)m_expression.c_str(), CParser<_T>::root_struct_field, 0, ignore_warnings) != ZJ_ERROR);
		}

		virtual ~CParserJson() {}
	};

};



#endif
