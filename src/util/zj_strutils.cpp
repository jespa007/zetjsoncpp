/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

#define	ZJ_MAX_STR_BUFFER 	4096


namespace zetjsoncpp{

	namespace zj_strutils{

		std::string  format(const  char  *input_text, ...){
			char  _sformat_buffer[ZJ_MAX_STR_BUFFER] = { 0 };
			va_list  ap;
			va_start(ap,  input_text);
			vsprintf(_sformat_buffer,  input_text,  ap);
			va_end(ap);

			return std::string(_sformat_buffer);
		}

		STR_2_NUMBER str_to_int(int * i, const std::string & s, int base){
			 char *end;
			long  l;
			errno = 0;
			l = strtol(s.c_str(), &end, base);
			if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
				return STR_2_NUMBER_OVERFLOW;
			}
			if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
				return STR_2_NUMBER_UNDERFLOW;
			}
			if (*s.c_str() == '\0' || *end != '\0') {
				return STR_2_NUMBER_INCONVERTIBLE;
			}
			*i = l;
			return STR_2_NUMBER_SUCCESS;
		}

		STR_2_NUMBER str_to_float(float * f, const std::string & s){
			 char *end;
			 char *data=(char *)s.c_str();
			float  l;
			errno = 0;
			l = strtof(data, &end);

			if (end == data){
				return STR_2_NUMBER_INCONVERTIBLE;
			}else	if ((errno == ERANGE && l == FLT_MAX) || l > FLT_MAX) {
				return STR_2_NUMBER_OVERFLOW;
			}else if ((errno == ERANGE && l < FLT_MIN) /* || l < FLT_MIN*/) {
				return STR_2_NUMBER_UNDERFLOW;
			}
			if (*s.c_str() == '\0' || *end != '\0') {
				return STR_2_NUMBER_INCONVERTIBLE;
			}
			*f = l;
			return STR_2_NUMBER_SUCCESS;
		}


		std::string int_to_str(int number){

		   std::stringstream ss;//create a stringstream
		   ss << number;//add number to the stream
		   return ss.str();//return a string with the contents of the stream
		}

		std::string float_to_str(float number){

			char buff[100];
			sprintf(buff, "%f",number);
			std::string ss = buff;
		   return ss;//return a string with the contents of the stream
		}

		std::string to_lower(const std::string & str){

			std::string ret = str;
			for(unsigned short l = 0; l < ret.size();l++)
				ret[l] = tolower(ret[l]);
			return ret;
		}

		bool ends_with(const std::string & fullString, const std::string & ending){
			if (fullString.length() >= ending.length()) {
				return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
			}

			return false;
		}


		std::wstring to_wstring_utf8(const std::string & str){
			std::wstring_convert<std::codecvt_utf8<wchar_t>> str_utf8_to_wstring_conv;
			return str_utf8_to_wstring_conv.from_bytes(str);
		}
	}

}
