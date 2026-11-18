/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

#define	ZJ_MAX_STR_BUFFER 	4096


namespace zetjsoncpp{

	namespace string_utils{

		std::string  format(const  char  *input_text, ...){
			char  _sformat_buffer[ZJ_MAX_STR_BUFFER] = { 0 };
			va_list  ap;
			va_start(ap,  input_text);
			vsnprintf(_sformat_buffer, ZJ_MAX_STR_BUFFER, input_text,  ap);
			va_end(ap);

			return std::string(_sformat_buffer);
		}

		STR_2_NUMBER stringToInteger(int * i, const std::string & s, int base){
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

		STR_2_NUMBER stringToFloat(float * f, const std::string & s){
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

		STR_2_NUMBER stringToDouble(
		    double *_f
		    ,const std::string &_s
		) {
		    char *end = nullptr;

		    errno = 0;

		    const char *data = _s.c_str();
		    double value = std::strtod(data, &end);

		    if(end == data || *end != '\0') {
		        return STR_2_NUMBER_INCONVERTIBLE;
		    }

		    if(errno == ERANGE) {
		        if(value == HUGE_VAL || value == -HUGE_VAL) {
		            return STR_2_NUMBER_OVERFLOW;
		        }

		        return STR_2_NUMBER_UNDERFLOW;
		    }

		    if(!std::isfinite(value)) {
		        return STR_2_NUMBER_INCONVERTIBLE;
		    }

		    *_f = value;

		    return STR_2_NUMBER_SUCCESS;
		}


		std::string integerToString(int number){

		   std::stringstream ss;//create a stringstream
		   ss << number;//add number to the stream
		   return ss.str();//return a string with the contents of the stream
		}

		std::string floatToString(float number){

			char buff[100];
			snprintf(buff,100, "%f",number);
			std::string ss = buff;
		   return ss;//return a string with the contents of the stream
		}

		std::string doubleToString(double number) {

		    if(!std::isfinite(number)) {
		        throw std::runtime_error("Invalid JSON number");
		    }

		    std::ostringstream stream;

		    stream.imbue(std::locale::classic());

		    stream << std::setprecision(
		        std::numeric_limits<double>::max_digits10
		    ) << number;

		    return stream.str();
		}

		std::string toLower(const std::string & str){

			std::string ret = str;
			for(unsigned short l = 0; l < ret.size();l++)
				ret[l] = tolower(ret[l]);
			return ret;
		}

		bool endsWith(const std::string & fullString, const std::string & ending){
			if (fullString.length() >= ending.length()) {
				return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
			}

			return false;
		}

        static uint32_t readHex4(const char *&_cursor) {
            uint32_t value = 0;
            for(int i = 0; i < 4; ++i) {
                unsigned char c = static_cast<unsigned char>(*_cursor);
                unsigned digit;
                if(c >= '0' && c <= '9') digit = c - '0';
                else if(c >= 'a' && c <= 'f') digit = c - 'a' + 10;
                else if(c >= 'A' && c <= 'F') digit = c - 'A' + 10;
                else throw std::runtime_error("Invalid Unicode escape");
                value = (value << 4) | digit;
                ++_cursor;
            }
            return value;
        }

        static void appendUtf8(std::string &_out, uint32_t _cp) {
            if(_cp > 0x10FFFF || (_cp >= 0xD800 && _cp <= 0xDFFF)) {
                throw std::runtime_error("Invalid Unicode code point");
            }
            if(_cp <= 0x7F) {
                _out += static_cast<char>(_cp);
            } else if(_cp <= 0x7FF) {
                _out += static_cast<char>(0xC0 | (_cp >> 6));
                _out += static_cast<char>(0x80 | (_cp & 0x3F));
            } else if(_cp <= 0xFFFF) {
                _out += static_cast<char>(0xE0 | (_cp >> 12));
                _out += static_cast<char>(0x80 | ((_cp >> 6) & 0x3F));
                _out += static_cast<char>(0x80 | (_cp & 0x3F));
            } else {
                _out += static_cast<char>(0xF0 | (_cp >> 18));
                _out += static_cast<char>(0x80 | ((_cp >> 12) & 0x3F));
                _out += static_cast<char>(0x80 | ((_cp >> 6) & 0x3F));
                _out += static_cast<char>(0x80 | (_cp & 0x3F));
            }
        }

        const char *readJsonString(const char *_input,std::string *_out) {

            const char *p = _input;

            if(*p != '"') {
            	throw std::runtime_error("Expected JSON string");
            }

            ++p;

            if(_out) _out->clear();

            while(*p != '\0') {

                unsigned char c = static_cast<unsigned char>(*p++);
                if(c == '"') return p;
                if(c < 0x20) throw std::runtime_error("Unescaped control character");
                if(c != '\\') {
                    if(_out) *_out += static_cast<char>(c);
                    continue;
                }

                if(*p == '\0') throw std::runtime_error("Incomplete JSON escape");
                switch(*p++) {
					case '"': c = '"'; break;
					case '\\': c = '\\'; break;
					case '/': c = '/'; break;
					case 'b': c = '\b'; break;
					case 'f': c = '\f'; break;
					case 'n': c = '\n'; break;
					case 'r': c = '\r'; break;
					case 't': c = '\t'; break;
					case 'u': {
						uint32_t cp = readHex4(p);
						if(cp >= 0xD800 && cp <= 0xDBFF) {
							if(*p != '\\' || p[1] != 'u') {
								throw std::runtime_error("Missing low surrogate");
							}
							p += 2;
							uint32_t low = readHex4(p);
							if(low < 0xDC00 || low > 0xDFFF) {
								throw std::runtime_error("Invalid low surrogate");
							}
							cp = 0x10000 + ((cp - 0xD800) << 10) + (low - 0xDC00);
						} else if(cp >= 0xDC00 && cp <= 0xDFFF) {
							throw std::runtime_error("Unexpected low surrogate");
						}

						if(_out) {
							appendUtf8(*_out, cp);
						}
						continue;
					}
					default:
						throw std::runtime_error("Invalid JSON escape");
                }

                if(_out) {
                	*_out += static_cast<char>(c);
                }
            }

            throw std::runtime_error("Unterminated JSON string");
        }

        void appendJsonString( std::string &_out,const std::string &_value) {

            static const char hex[] = "0123456789abcdef";
            _out += '"';

            for(unsigned char c : _value) {
                switch(c) {
                case '"': _out += "\\\""; break;
                case '\\': _out += "\\\\"; break;
                case '\b': _out += "\\b"; break;
                case '\f': _out += "\\f"; break;
                case '\n': _out += "\\n"; break;
                case '\r': _out += "\\r"; break;
                case '\t': _out += "\\t"; break;
                default:
                    if(c < 0x20) {
                        _out += "\\u00";
                        _out += hex[c >> 4];
                        _out += hex[c & 0x0F];
                    } else {
                        _out += static_cast<char>(c);
                    }
                }
            }
            _out += '"';
        }

	}

}
