/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

#define PREVIEW_SSTRING(start, current,n) (((current)-(n))<((start))?(start):((current)-(n)))

void CParserBase::writeError(const char *file, int line, const char *start_str, char *current_ptr, const char *string_text, ...) {


	char  where[1024]={0};
	char  text[MAX_C_STRING]={0};
	char temp_buff[4096]={0};
	CAPTURE_VARIABLE_ARGS(text, string_text);

	if(start_str != NULL){

	sprintf(where,"...%.15s..."
				  "\n               ^   "
				  "\n  -------------+ \n", PREVIEW_SSTRING(start_str, current_ptr, 15));
	}


	sprintf(temp_buff,"[%s:%i] %s\n%s",path::get_filename(file).c_str(), line,text,where);


	m_error=temp_buff;
}

void CParserBase::writeWarning(const char *file, int line,bool ignore_warnings, const char *string_text, ...) {

	//if (!ignore_warnings) {
	char temp_buff[4096]={0};
	char  text[MAX_C_STRING]={0};
	CAPTURE_VARIABLE_ARGS(text, string_text);


	sprintf(temp_buff,"[%s:%i] %s",path::get_filename(file).c_str(),line,text);
	m_error=temp_buff;

}
