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
			float  l;
			errno = 0;
			l = strtof(s.c_str(), &end);
			if ((errno == ERANGE && l == FLT_MAX) || l > FLT_MAX) {
				return STR_2_NUMBER_OVERFLOW;
			}
			if ((errno == ERANGE && l == FLT_MIN) || l < FLT_MIN) {
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


		bool IsDigit(char c){
			return (('0' <= c) && (c<='9'));
		}

		bool is_hexa_digit(char c){
			return ((('0' <= c) && (c<='9')) || ((tolower(c)<='a')&&(tolower(c)<='f')));
		}


		char *ADVANCE_DIGITS(char *aux_p){

			while(IsDigit(*aux_p))	aux_p++;
			return aux_p;
		}

		char *ADVANCE_HEXADIGITS(char *aux_p){

			while(is_hexa_digit(*aux_p))	aux_p++;
			return aux_p;
		}

		STR_NUMBER_TYPE is_number(const std::string & test_str_number){
			bool isHexa=false;
			char *str = (char *)test_str_number.c_str();

			switch(*str){
			case '-': str++; // negative numbers ...
					   break;
			case '0':
					  if(tolower(*str+1)=='x')  {
						  isHexa = true;
						  str+=2;
					  }
					  break;
			default:
					break;
			};

			char *start_str = str; // saves position...
			if(isHexa) {
				str = ADVANCE_HEXADIGITS(str);
				if(str == start_str)
					return STR_NUMBER_TYPE_INVALID;

				if(*str == ' ' || *str == 0) return STR_NUMBER_TYPE_HEXA;
			}else{
				str = ADVANCE_DIGITS(str);
				if(str == start_str)
					return STR_NUMBER_TYPE_INVALID;

				if(*str=='.') { // is candidate to double
					str++;
					str = ADVANCE_DIGITS(str);
					if(*str == ' ' || *str == 0)
						return STR_NUMBER_TYPE_DOUBLE;

					return STR_NUMBER_TYPE_INVALID;
				}

				if(*str == ' ' || *str == 0){
					return STR_NUMBER_TYPE_INT;
				}
			}

			return STR_NUMBER_TYPE_INVALID;

		}

		std::wstring to_wstring_utf8(const std::string & str){
			std::wstring_convert<std::codecvt_utf8<wchar_t>> str_utf8_to_wstring_conv;
			return str_utf8_to_wstring_conv.from_bytes(str);
		}
	}

};
