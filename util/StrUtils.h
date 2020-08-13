/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

namespace zetjsoncpp {

	namespace StrUtils{

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


		bool IsEmpty(const std::string & str);

		STR_2_NUMBER str2int(int * i, const std::string & s, int base = 0);
		STR_2_NUMBER str2float(float * f, const std::string & s);
		std::string int2str(int number);
		std::string float2str(float number);

		std::string ToLower(const std::string & str);
		bool EndsWith(const std::string & fullString, const std::string & ending);
		STR_NUMBER_TYPE is_number(const std::string & test_str_number);


	}

};
