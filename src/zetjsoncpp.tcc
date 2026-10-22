/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#define ZJ_MAX_NAME_PROPERTY 128
#define ZJ_MAX_C_STRING 4096


#define ZJ_INI_GROUP	'{'
#define ZJ_END_GROUP	'}'
#define ZJ_IS_EMPTY(str) (str==NULL || *str==0)


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
	std::unique_ptr<_T>  deserialize(const std::string & expression) {

		int line=-1;
		auto json_var = std::unique_ptr<_T>(new _T);

		DeserializeData deserialize_data;
		deserialize_data.filename=NULL;
		deserialize_data.str_start = expression.c_str();
		deserialize_json_var(&deserialize_data,expression.c_str(),line, json_var.get());
		return json_var;
	}

	template <typename _T>
	std::unique_ptr<_T> deserialize_file(
		const std::string &_filename
	) {

	    std::string expression = file_utils::read_text(_filename);

	    int line = 1;

	    const char *aux_p = expression.c_str();

	    // Ignore UTF-8 BOM
	    const unsigned char bom_signature[] = {0xef, 0xbb, 0xbf};

	    if( expression.size() >= sizeof(bom_signature)
	        && memcmp(aux_p, bom_signature, sizeof(bom_signature)) == 0
		) {
	        aux_p += sizeof(bom_signature);
	    }

	    DeserializeData deserialize_data;
	    deserialize_data.filename = _filename.c_str();
	    deserialize_data.str_start = aux_p;

	    auto json_var = std::unique_ptr<_T>(new _T);

	    deserialize_json_var(
	        &deserialize_data
	        ,aux_p
	        ,line
	        ,json_var.get()
	    );

	    return json_var;
	}

    // overload for unique_ptr
    template<typename _T>
    std::string serialize(
        const std::unique_ptr<_T> &_json_var
		, bool _minimized
		, bool _discard_non_serialized
    ) {
        return serialize(
            _json_var.get()
            ,_minimized
            ,_discard_non_serialized
        );
    }
}

