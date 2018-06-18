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

class CZetJsonCppUtils{

public:
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


	static ZETJSONCPP_MODULE_EXPORT bool isEmpty(const string & str);

	static ZETJSONCPP_MODULE_EXPORT string intToString(int number);
	static ZETJSONCPP_MODULE_EXPORT string floatToString(float number);
	static ZETJSONCPP_MODULE_EXPORT string toLower(const string & str);
	static ZETJSONCPP_MODULE_EXPORT bool endsWith(const string & fullString, const string & ending);
	static ZETJSONCPP_MODULE_EXPORT int isNumber(const string & test_str_number);

	static bool fileExists(const string & m_file) ;
	static ZETJSONCPP_MODULE_EXPORT ByteBuffer * readFile(const string & filename, bool end_string_char=true);
	static int  getLengthFile(const  string  & file);
	static string extractFile(const string & _filename);

};

};
