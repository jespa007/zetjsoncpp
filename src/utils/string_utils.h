/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

namespace zetjsoncpp {

	namespace string_utils{

		typedef enum {
			STR_2_NUMBER_SUCCESS,
			STR_2_NUMBER_OVERFLOW,
			STR_2_NUMBER_UNDERFLOW,
			STR_2_NUMBER_INCONVERTIBLE
		} STR_2_NUMBER;

		 bool 			isEmpty(const std::string & str);

		 std::string  	format(const  char  *input_text, ...);
		 STR_2_NUMBER 	stringToInteger(int * i, const std::string & s, int base = 0);
		 STR_2_NUMBER 	stringToFloat(float * f, const std::string & s);
		 std::string 	integerToString(int number);
		 std::string 	floatToString(float number);

		 std::string 	toLower(const std::string & str);
		 bool 			endsWith(const std::string & fullString, const std::string & ending);
		 std::wstring 	toWStringUtf8(const std::string & s);
	}

}
