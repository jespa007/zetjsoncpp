/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

namespace zetjsoncpp {

	namespace string{

		typedef enum {
			STRING_IS_INVALID_NUMBER = 0,
			STRING_IS_HEXA,
			STRING_IS_INT,
			STRING_IS_DOUBLE
		}NUMBER_STRING_TYPE;

		template<typename T>
		T to_number(const std::string& str) {

			std::istringstream ss(str);
			T ret;
			ss >> ret;
			return ret;
		}


		bool is_empty(const std::string & str);

		std::string int_to_string(int number);
		std::string float_to_string(float number);
		std::string to_lower(const std::string & str);
		bool ends_with(const std::string & fullString, const std::string & ending);
		int is_number(const std::string & test_str_number);


	}

};
