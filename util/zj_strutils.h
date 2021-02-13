/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

namespace zetjsoncpp {

	namespace zj_strutils{

		typedef enum {
			STR_2_NUMBER_SUCCESS,
			STR_2_NUMBER_OVERFLOW,
			STR_2_NUMBER_UNDERFLOW,
			STR_2_NUMBER_INCONVERTIBLE
		} STR_2_NUMBER;

		typedef enum {
			STR_NUMBER_TYPE_INVALID = 0,
			STR_NUMBER_TYPE_HEXA,
			STR_NUMBER_TYPE_INT,
			STR_NUMBER_TYPE_DOUBLE
		}STR_NUMBER_TYPE;


		bool is_empty(const std::string & str);

		std::string  format(const  char  *input_text, ...);
		STR_2_NUMBER str_to_int(int * i, const std::string & s, int base = 0);
		STR_2_NUMBER str_to_float(float * f, const std::string & s);
		std::string int_to_str(int number);
		std::string float_to_str(float number);

		std::string to_lower(const std::string & str);
		bool ends_with(const std::string & fullString, const std::string & ending);
		STR_NUMBER_TYPE is_number(const std::string & test_str_number);
		std::wstring to_wstring_utf8(const std::string & s);


	}

};
