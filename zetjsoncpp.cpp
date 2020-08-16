/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

#ifdef CAPTURE_VARIABLE_ARGS
#undef CAPTURE_VARIABLE_ARGS
#endif


// Util to capture args by ...
#define CAPTURE_VARIABLE_ARGS(text_out, text_in)\
	{va_list  ap;\
	va_start(ap,  text_in);\
	vsprintf(text_out,  text_in,  ap);\
	va_end(ap);}


namespace zetjsoncpp{






	/*void set_json_error_callback(tJsonErrorCallback _error_callback){
		json_error_callback=_error_callback;
	}

	void set_json_warning_callback(tJsonWarningCallback _warning_callback){
		json_warning_callback=_warning_callback;
	}*/

	void throw_error(const char *file, int line, const char *start_str, char *current_ptr, const char *string_text, ...) {


		char  where[1024]={0};
		char  text[MAX_C_STRING]={0};
		char temp_buff[4096]={0};
		CAPTURE_VARIABLE_ARGS(text, string_text);

		if(start_str != NULL){

			sprintf(where,"...%.15s..."
					  "\n               ^   "
					  "\n  -------------+ \n", PREVIEW_SSTRING(start_str, current_ptr, 15));
		}

		sprintf(temp_buff,"[%s:%i] %s\n%s",zj_path::get_filename(file).c_str(), line,text,where);
		throw parse_error_exception(file,line,temp_buff);
	}

	void throw_warning(const char *file, int line,const char *string_text, ...) {

		char temp_buff[4096]={0};
		char  text[MAX_C_STRING]={0};
		CAPTURE_VARIABLE_ARGS(text, string_text);
		sprintf(temp_buff,"[%s:%i] %s",zj_path::get_filename(file).c_str(),line,text);
		throw parse_warning_exception(file,line,temp_buff);

	}
};

