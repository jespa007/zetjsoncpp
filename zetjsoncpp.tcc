/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#define MAX_NAME_PROPERTY 128
#define MAX_C_STRING 4096


#define INI_GROUP	'{'
#define END_GROUP	'}'
#define IS_EMPTY(str) (str==NULL || *str==0)


#ifdef __DEBUG__
	//#define __VERBOSE_MESSAGE__
#endif


#define print_info_json print_info_cr

#ifndef  __VERBOSE_MESSAGE__
#undef print_info_json
#define print_info_json(s,...)
#endif

#define PREVIEW_SSTRING(start, current,n) (((current)-(n))<((start))?(start):((current)-(n)))

namespace zetjsoncpp{

	extern char json_message_error[16836];



	void throw_error(const char *file, int line, const char *start_str, char *current_ptr, const char *string_text, ...);
	void throw_warning(const char *file, int line, const char *string_text, ...);


	const char end_char_standard_value[] = {
			',',
			'}',
			' ',
			'\t',
			'\n',
			'\r', // for make compatible windows...
			']',
			0
	};

	void parse_main(const char * start_str, JsonVar *_root,const char *filename);

	template <typename _T>
	_T * parse(const std::string & expression) {

		_T *data=new _T;

		parse_main(expression.c_str(), data, NULL);

		return data;
	}

	template <typename _T>
	_T * parse_file(const std::string & _filename) {
		//_T * json_element;
		std::string filename = _filename.c_str();
		_T *data=NULL;

		char *buf = zj_file::read(filename);
		if (buf != NULL) {
			try{
				data=new _T;
				char *aux_p=buf;
				uint8_t bom_signature[]={0xef,0xbb,0xbf};
				if(memcmp(aux_p,bom_signature,sizeof(bom_signature))==0){ // ignore BOM signature
					aux_p+=sizeof(bom_signature);
				}

				parse_main(aux_p, data,_filename.c_str());
			}
			catch(parse_error_exception & err){
				delete data;
				free(buf);
				throw err;
			}
			catch(parse_warning_exception & wrn){
				delete data;
				free(buf);
				throw wrn;

			}
			free(buf);
		}

		return data;
	}
}

