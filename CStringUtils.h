/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

namespace zetjsoncpp {

	#if  !defined(CAPTURE_VARIABLE_ARGS)
		// Util to capture args by ...
		#define CAPTURE_VARIABLE_ARGS(text_out, text_in)\
		{va_list  ap;\
		va_start(ap,  text_in);\
		vsprintf(text_out,  text_in,  ap);\
		va_end(ap);}

	#endif

	enum {
		STRING_IS_INVALID_NUMBER = 0,
		STRING_IS_HEXA,
		STRING_IS_INT,
		STRING_IS_DOUBLE
	};

	template<typename T>
	static T fromString(const std::string& str) {

		std::istringstream ss(str);
		T ret;
		ss >> ret;
		return ret;
	}


	ZETJSONCPP_MODULE_EXPORT bool isEmpty(const string & str);

	ZETJSONCPP_MODULE_EXPORT string intToString(int number);
	ZETJSONCPP_MODULE_EXPORT string floatToString(float number);
	ZETJSONCPP_MODULE_EXPORT string toLower(const string & str);
	ZETJSONCPP_MODULE_EXPORT bool endsWith(const string & fullString, const string & ending);
	ZETJSONCPP_MODULE_EXPORT int isNumber(const string & test_str_number);

};
