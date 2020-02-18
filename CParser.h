/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#ifndef __CPARSER_H__
#define __CPARSER_H__

namespace zetjsoncpp {

	template<typename _T>
	class CParser : public CParserBase {

	public:

		CParser() {
			m_filesrc = NULL;
			m_line = 0;
			root_struct_field = new CParserVarPropertyGroupArray<_T>;
		}

		virtual void evalString(const std::string & m_expression, int level = 0, bool ignore_warnings =
			false) = 0;

		virtual void evalFile(const std::string & m_filename, bool ignore_warnings =
			false) {


			m_filesrc = m_filename.c_str();

			char *buf = io::read_file(m_filename);
			if (buf != NULL) {
				try{
					evalString(buf, 0, ignore_warnings);
				}
				catch(zetjsoncpp::parse_error_exception & err){
					delete buf;
					throw err;
				}
				catch(zetjsoncpp::parse_warning_exception & wrn){
					delete buf;
					throw wrn;

				}
				free(buf);
			}
		}

		CParserVarPropertyGroupArray<_T> *getData() {
			return root_struct_field;
		}

		virtual ~CParser() {
			if (root_struct_field != NULL) {
				delete root_struct_field;
			}
			root_struct_field = NULL;
		}

	protected:


		CParserVarPropertyGroupArray<_T> * root_struct_field;
		const char *m_filesrc;
		int m_line;

	};

};

#include "CParserBase.inc";		void write_error(const char *file, int line, const char *start_str, char *current_ptr, const char *string_text, ...) {


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


throw parse_error_exception(file,line,temp_buff);
}

void write_warning(const char *file, int line,bool ignore_warnings, const char *string_text, ...) {

//if (!ignore_warnings) {
char temp_buff[4096]={0};
char  text[MAX_C_STRING]={0};
CAPTURE_VARIABLE_ARGS(text, string_text);


sprintf(temp_buff,"[%s:%i] %s",path::get_filename(file).c_str(),line,text);
throw parse_warning_exception(file,line,temp_buff);
}

#endif
