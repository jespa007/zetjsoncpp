//    This file is part of FastJson2Cpp.
//
//    FastJson2Cpp is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    FastJson2Cpp is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with FastJson2Cpp.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "CCommon.h"
#include "CFile.h"
#include "CString.h"
#include "CLog.h"
#include "CParserVar.h"



template <typename _T>
class CParserJson{

protected:
    string filename;
	string m_error;

	CParserVarArrayPropertyGroup<_T> * root_struct_field;
	const char *m_filesrc;
	int m_line;


	CParserVar *findProperty(CParserVar * c_data, char *property_name);
	void setPropertiesParsedToFalse(CParserVar * c_data);
	//void printJsonError(char *m_start_ptr, char *m_current_ptr, int column, const char *error_message);
	bool bothAreTypeNumbers(int type1, int type2);
	void print_error_json(const char *start_str, char *current_ptr,const char *str, ...);
	void print_warning_json(const char *str, ...);
	void print_info_json_debug(const char *str, ...);

	int json2cpp(const char * start_str,CParserVar *c_data, int level, bool ignore_warnings);

public:
	CParserJson(){
		root_struct_field = new CParserVarArrayPropertyGroup<_T>;
	}

	bool parseString(const string & m_expression, bool ignore_warnings=false){

		this->m_line = 1;
		
		// detect if starts with [ or  { ...

		return (json2cpp((const char *)m_expression.c_str(), CParserJson<_T>::root_struct_field, 0,ignore_warnings) > 0);
	}

	bool parseFile(const string & m_filename, bool ignore_warnings =
			false) {

		bool ok = false;
		if (fileExists(m_filename)) {
			int size = getLengthFile(m_filename) + 1;
			m_filesrc = (const char *)m_filename.c_str();
			if (size > 0) {
				char *buffer = (char *) malloc(size);
				if (readFile(m_filename, buffer, size)) {
					ok = (parseString(buffer, ignore_warnings) > 0);
				}
				free(buffer);
			}
		} else {
			print_error("file \"%s\" not exist", m_filename.c_str());
		}

		return ok;
	}


	CParserVarArrayPropertyGroup<_T> *getData() {
		return root_struct_field;
	}

	~CParserJson() {
		if (root_struct_field != NULL) {
			delete root_struct_field;
		}
		root_struct_field = NULL;
	}

};

#include "CParserJson.cxx"

