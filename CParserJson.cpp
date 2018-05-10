/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp{


	char json_message_error[16836]={0};

	bool IS_SINGLE_COMMENT(char *str){

		if((*str!=0) && *str=='/'){
			return *(str+1)=='/';
		}
		return false;
	}


	bool IS_START_COMMENT(char *str){

		if((*str!=0) && *str=='/'){
			return *(str+1)=='*';
		}
		return false;
	}


	bool IS_END_COMMENT(char *str){

		if((*str!=0) && *str=='*'){
			return *(str+1)=='/';
		}
		return false;
	}


	char *ADVANCE_TO_CHAR(char *str,char c) {
		char *aux_p = str;
		// make compatible windows format (\r)...
		while(*aux_p!='\n' && *aux_p!='\r' && *aux_p!=0 && (*aux_p !=(c) )) aux_p++;

		if(*aux_p=='\r')
			aux_p++;

		return aux_p;
	}


	char *ADVANCE_TO_END_COMMENT(char *aux_p, int &m_line){

		if(IS_START_COMMENT(aux_p)){
			aux_p+=2; //advance first
			while(!IS_END_COMMENT(aux_p) && *aux_p != 0){
				aux_p = ADVANCE_TO_CHAR(aux_p,'*');
				if(*aux_p == '\n') aux_p++; // make compatible windows format...
				if(*aux_p == '\r') aux_p++;
				if(*(aux_p+1) != '/') aux_p++; // not end comment ... advance ...
			}
		}

		return aux_p;

	}

	char *IGNORE_BLANKS(char *str, int &m_line) {
		char *aux_p = str;
		bool end = false;
		while(!end){
			end = true;
			while(*aux_p!=0 && ((*aux_p==' ')  || (*aux_p=='\t'))) aux_p++;

			if(IS_SINGLE_COMMENT(aux_p)) // ignore line
				aux_p = ADVANCE_TO_CHAR(aux_p,'\n');

			else if(IS_START_COMMENT(aux_p)){
				// ignore until get the end of the comment...
				aux_p = ADVANCE_TO_END_COMMENT(aux_p, m_line);

				if(IS_END_COMMENT(aux_p))
					aux_p+=2;

				end=false;
			}
			// make compatible windows format...
			if(*aux_p == '\r')
				aux_p++;

			if(*aux_p == '\n') {
				m_line=m_line+1;
				end=false;
				aux_p++;
			}
		}
		return aux_p;
	}

	char *ADVANCE_TO_ONE_OF_COLLECTION_CHAR(char *str,char *end_char_standard_value, int &m_line) {
		char *aux_p = str;
		char *chk_char;
		while(*aux_p!=0){
			chk_char = end_char_standard_value;

			// comment blocks also is returned (these lines must be ignored)
			if(IS_START_COMMENT(aux_p)) {
				aux_p = ADVANCE_TO_END_COMMENT(aux_p, m_line);
				if(IS_END_COMMENT(aux_p))
					aux_p+=2;
			}

			if(IS_SINGLE_COMMENT(aux_p)) {
				aux_p = ADVANCE_TO_CHAR(aux_p,'\n');
			}

			while(*chk_char != 0){
				if(*chk_char == *aux_p)
					return aux_p;
				chk_char++;
			}
			aux_p++;
		}
		return aux_p;
	}

	void clear_message_error(){
		memset(json_message_error,0,sizeof(json_message_error));
	}

	void print_json_error(const char *file, int line, const char *start_str, char *current_ptr, const char *string_text, ...) {

		char  out[MAX_C_STRING];
		char  text[MAX_C_STRING];
		CAPTURE_VARIABLE_ARGS(text, string_text);

		sprintf(out,"[%s:%i] %s",extractFile(file).c_str(), line,text);

		//CLog::print(this->m_filesrc, this->m_line, CLog::LOG_ERROR, true, text);
		sprintf(out,"%s\n...%.15s...", out,PREVIEW_SSTRING(start_str, current_ptr, 15));
		sprintf(out,"%s\n               ^   ",out);
		sprintf(out,"%s\n  -------------+ \n",out);

		sprintf(json_message_error,out);
	}

	void print_json_warning(const char *file, int line,bool ignore_warnings, const char *string_text, ...) {

		if (!ignore_warnings) {
			char  out[MAX_C_STRING];
			char  text[MAX_C_STRING];
			CAPTURE_VARIABLE_ARGS(text, string_text);

			sprintf(out,"[%s:%i] %s",extractFile(file).c_str(),line,text);
			sprintf(json_message_error,out);
		}
	}
};


