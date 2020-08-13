/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>
#include <stdexcept>
#include <float.h>
#include <limits.h>


#define ZETJSONCPP_MAJOR_VERSION 1
#define ZETJSONCPP_MINOR_VERSION 3
#define ZETJSONCPP_PATCH_VERSION 0

#ifdef __MEMMANAGER__
#include "memmgr.h"
#endif

#include "util/StrUtils.h"
#include "util/File.h"
#include "util/Path.h"


#include "var/ZJ_Boolean.h"
#include "var/ZJ_Number.h"
#include "var/ZJ_String.h"


#include "exception.h"
#include "parser_var/CParserVar.h"
#include "ParserBase.h"
#include "Parser.h"


// static zetjsoncpp

namespace zetjsoncpp {

	//typedef void (* tJsonErrorCallback)(const char *file, int line, const char *str,const char *where);
	//typedef void (* tJsonWarningCallback)(const char *file, int line, const char *str);

	// define my exceptions


	template <typename _T>
	class ZetJsonCpp : public Parser<_T> {

		CParserVar *findProperty(CParserVar * c_data, char *property_name);
		void setPropertiesParsedToFalse(CParserVar * c_data);
		//void printJsonError(char *m_start_ptr, char *m_current_ptr, int column, const char *error_message);
		bool bothAreTypeNumbers(int type1, int type2);
		int json2cpp(const char * start_str, CParserVar *c_data, int level = 0, bool ignore_warnings = false);

	public:

		ZetJsonCpp() {}

		virtual void evalString(const std::string & m_expression, int level = 0, bool ignore_warnings = false) {

			this->m_line = 1;
			this->root_struct_field->destroy(); // destroy previous elements!

			json2cpp((const char *)m_expression.c_str(), Parser<_T>::root_struct_field, 0, ignore_warnings);
		}

		virtual ~ZetJsonCpp() {}
	};

	//void set_json_error_callback(tJsonErrorCallback _error_callback);
	//void set_json_warning_callback(tJsonWarningCallback _warning_callback);
};

#include "zetjsoncpp.inc"


