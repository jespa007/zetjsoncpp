//    This file is part of json2cpp.
//
//    json2cpp is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    json2cpp is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with json2cpp.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

namespace json2cpp {

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


	bool isEmpty(const string & str);

	string intToString(int number);
	string floatToString(float number);
	string toLower(const string & str);
	bool endsWith(const string & fullString, const string & ending);
	int isNumber(const string & test_str_number);

};
