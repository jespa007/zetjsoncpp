/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp{



	string CZetJsonCppUtils::intToString(int number){

	   std::stringstream ss;//create a stringstream
	   ss << number;//add number to the stream
	   return ss.str();//return a string with the contents of the stream
	}

	string CZetJsonCppUtils::floatToString(float number){

		char buff[100];
		sprintf(buff, "%f",number);
		string ss = buff;
	   return ss;//return a string with the contents of the stream
	}

	string CZetJsonCppUtils::toLower(const string & str){

		string ret = str;
		for(unsigned short l = 0; l < ret.size();l++)
			ret[l] = tolower(ret[l]);
		return ret;
	}

	bool CZetJsonCppUtils::endsWith(const string & fullString, const string & ending){
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
		}

		return false;
	}


	bool isDigit(char c){
		return (('0' <= c) && (c<='9'));
	}

	bool isHexaDigit(char c){
		return ((('0' <= c) && (c<='9')) || ((tolower(c)<='a')&&(tolower(c)<='f')));
	}


	char *ADVANCE_DIGITS(char *aux_p){

		while(isDigit(*aux_p))	aux_p++;
		return aux_p;
	}

	char *ADVANCE_HEXADIGITS(char *aux_p){

		while(isHexaDigit(*aux_p))	aux_p++;
		return aux_p;
	}



	bool CZetJsonCppUtils::isEmpty(const string & str){
		return str.empty();
	}

	int CZetJsonCppUtils::isNumber(const string & test_str_number){
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
				return STRING_IS_INVALID_NUMBER;

			if(*str == ' ' || *str == 0) return STRING_IS_HEXA;
		}else{
			str = ADVANCE_DIGITS(str);
			if(str == start_str)
				return STRING_IS_INVALID_NUMBER;

			if(*str=='.') { // is candidate to double
				str++;
				str = ADVANCE_DIGITS(str);
				if(*str == ' ' || *str == 0)
					return STRING_IS_DOUBLE;

				return STRING_IS_INVALID_NUMBER;
			}

			if(*str == ' ' || *str == 0)
				return STRING_IS_INT;

		}

		return STRING_IS_INVALID_NUMBER;


	}

	bool CZetJsonCppUtils::fileExists(const string & m_file) {

		if (endsWith(m_file, "/"))
			return false;

		if (m_file == "")
			return false;

		struct stat buffer;
		return (stat(m_file.c_str(), &buffer) == 0);

	}

	char * CZetJsonCppUtils::readFile(const string & filename, bool end_string_char){

		int  file_length, readed_elements;
			FILE  *fp;
			int with_end_char=0;

			if(end_string_char){
				with_end_char=1;
			}

			if((fp  =  fopen(filename.c_str(),"rb"))  !=  NULL)
			{
				if((file_length = getLengthFile(filename)) != -1) {


					char *buffer = (char *)malloc (file_length+with_end_char);
					memset(buffer,0,file_length+with_end_char );
					readed_elements = fread(buffer, 1, file_length, fp);

					if(readed_elements != file_length) {
						//fprintf(stderr,"number elements doesn't match with length file (%s)\n",filename.c_str());
						free(buffer);

						throw std::runtime_error("number elements doesn't match with length file ("+filename+")");

					}

					//ByteBuffer *ch = new ByteBuffer(buffer, file_length+with_end_char);

					//delete [] buffer;

					fclose(fp);

					return buffer;
				}
				else  throw std::runtime_error("I can't read file \""+filename+"\"");
			}
			else  throw std::runtime_error("I can't open file \""+filename+"\"");



			return NULL;
	}


	int  CZetJsonCppUtils::getLengthFile(const  string  & file)
	{
		int  ini, end;
		FILE  *fp;

		if ((fp = fopen(file.c_str(), "rb")) != NULL)
		{

			fseek(fp, 0, SEEK_SET);
			ini = ftell(fp);
			fseek(fp, 0, SEEK_END);
			end = ftell(fp);

			fclose(fp);

			return  (end - ini);

		}

		return    -1;
	}

	string  CZetJsonCppUtils::extractFile(const string & _filename) {
		size_t found;
		string ss = _filename;
		found = _filename.find_last_of("/\\");
		if ((int)found != -1)
			ss = _filename.substr(found + 1);
		return ss;
	}

};
