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



namespace zetjsoncpp{

	typedef struct{
		const char *filename;
		const char *str_start;
	}DeserializeData;

	extern char json_message_error[16836];



	void throw_error(DeserializeData *deserialize_data, const char * str_current, int line, const char *string_text, ...);
	void throw_warning(DeserializeData *deserialize_data, const char * str_current, int line, const char *string_text, ...);


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

	char * deserialize_json_var(DeserializeData *deserialize_data, const char * str_current, int & line,JsonVar *json_var);

	template <typename _T>
	_T * deserialize(const std::string & expression) {

		int line=-1;
		_T *json_var=new _T;

		try{
			DeserializeData deserialize_data;
			deserialize_data.filename=NULL;
			deserialize_data.str_start=expression.c_str();
			deserialize_json_var(&deserialize_data,expression.c_str(),line, json_var);
		}catch(deserialize_error_exception & err){
			delete json_var;
			json_var=NULL;
			throw err;
		}

		return json_var;
	}

	template <typename _T>
	_T * deserialize_file(const std::string & _filename) {
		//_T * json_element;
		std::string filename = _filename.c_str();
		_T *json_var=NULL;
		int line=1;

		char *buf = zj_file::read(filename);
		if (buf != NULL) {
			try{
				json_var=new _T;
				char *aux_p=buf;
				uint8_t bom_signature[]={0xef,0xbb,0xbf};
				DeserializeData deserialize_data;
				if(memcmp(aux_p,bom_signature,sizeof(bom_signature))==0){ // ignore BOM signature
					aux_p+=sizeof(bom_signature);
				}

				deserialize_data.filename=_filename.c_str();
				deserialize_data.str_start=aux_p;

				deserialize_json_var(&deserialize_data,aux_p,line,json_var);
			}
			catch(deserialize_error_exception & err){
				delete json_var;
				free(buf);
				throw err;
			}
			free(buf);
		}

		return json_var;
	}
}

