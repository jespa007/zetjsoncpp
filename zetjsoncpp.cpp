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

	void throw_error(const char *file, int line, const char *str_start, char *str_current, const char *string_text, ...) {


		char  where[1024]={0};
		char  text[MAX_C_STRING]={0};
		char temp_buff[4096]={0};
		CAPTURE_VARIABLE_ARGS(text, string_text);

		if(str_start != NULL){

			sprintf(where,"...%.15s..."
					  "\n               ^   "
					  "\n  -------------+ \n", PREVIEW_SSTRING(str_start, str_current, 15));
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

	bool is_single_comment(char *str){

		if((*str!=0) && *str=='/'){
			return *(str+1)=='/';
		}
		return false;
	}

	bool is_start_comment(char *str){

		if((*str!=0) && *str=='/'){
			return *(str+1)=='*';
		}
		return false;
	}

	bool is_end_comment(char *str){

		if((*str!=0) && *str=='*'){
			return *(str+1)=='/';
		}
		return false;
	}

	char *advance_to_char(char *str,char c) {
		char *aux_p = str;
		// make compatible windows format (\r)...
		while(*aux_p!='\n' && *aux_p!='\r' && *aux_p!=0 && (*aux_p !=(c) )) aux_p++;

		if(*aux_p=='\r')
			aux_p++;

		return aux_p;
	}

	char *advance_to_end_comment(char *aux_p, int &line){

		if(is_start_comment(aux_p)){
			aux_p+=2; //advance first
			while(!is_end_comment(aux_p) && *aux_p != 0){
				aux_p = advance_to_char(aux_p,'*');
				if(*aux_p == '\n') aux_p++; // make compatible windows format...
				if(*aux_p == '\r') aux_p++;
				if(*(aux_p+1) != '/') aux_p++; // not end comment ... advance ...
			}
		}

		return aux_p;
	}

	char *ignore_blanks(char *str, int &line) {
		char *aux_p = str;
		bool end = false;
		while(!end){
			end = true;
			while(*aux_p!=0 && ((*aux_p==' ')  || (*aux_p=='\t'))) aux_p++;

			if(is_single_comment(aux_p)) {// ignore line
				aux_p = advance_to_char(aux_p,'\n');
			}
			else if(is_start_comment(aux_p)){
				// ignore until get the end of the comment...
				aux_p = advance_to_end_comment(aux_p, line);

				if(is_end_comment(aux_p)){
					aux_p+=2;
				}
				end=false;
			}
			// make compatible windows format...
			if(*aux_p == '\r')
				aux_p++;

			if(*aux_p == '\n') {
				line=line+1;
				end=false;
				aux_p++;
			}
		}
		return aux_p;
	}

	char *advance_to_one_of_collection_of_char(char *str,char *end_char_standard_value, int &line) {
		char *aux_p = str;
		char *chk_char;
		while(*aux_p!=0){
			chk_char = end_char_standard_value;

			// comment blocks also is returned (these lines must be ignored)
			if(is_start_comment(aux_p)) {
				aux_p = advance_to_end_comment(aux_p, line);
				if(is_end_comment(aux_p))
					aux_p+=2;
			}

			if(is_single_comment(aux_p)) {
				aux_p = advance_to_char(aux_p,'\n');
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

	JsonVar *find_property(JsonVar * c_data, const std::string & variable_name) {
		// no data no search...
		if (c_data == NULL) return NULL;

		char *aux_p = (char *)c_data->getPtrData();
		char *end_p = (char *)c_data->getPtrDataEnd();

		// Main loop iteration to whole C struct
		for (; aux_p < end_p; ) {

			JsonVar * p_sv = (JsonVar *)aux_p;
			if (p_sv->getVariableName() == variable_name)
				return p_sv;

			aux_p += p_sv->getSizeData();
		}

		return NULL;
	}

	void set_parsed_to_false_all_properies(JsonVar * c_data) {
		// no data no search...
		if (c_data == NULL){
			return;
		}

		char *aux_p = (char *)c_data->getPtrData();
		char *end_p = (char *)c_data->getPtrDataEnd();

		// Main loop iteration to whole C struct
		for (; aux_p < end_p; ) {

			JsonVar * p_sv = (JsonVar *)aux_p;
			p_sv->setParsed(false);

			aux_p += p_sv->getSizeData();
		}
	}

	char * read_string_between_quotes(const char *str_start, char *str_current,std::string & str_out, const char *filename,int line){
		size_t str_size;
		char *str_end;
		char str_aux[128]={0};
		str_out = "";

		if (*str_current == '\'') // try to advance double quote
			str_end = advance_to_char(str_current + 1, '\'');
		else if (*str_current == '\"'){ // try to single quote...
			str_end = advance_to_char(str_current + 1, '\"');
		}

		if (*str_current != *str_end) {
			throw_error(filename, line,str_start, str_current, "Was expect a double/single quote. format example --> \"property\":\"value\"");
		}

		str_size = str_end - str_current - 1;


		if (str_size < sizeof(str_aux)) {

			strncpy(str_aux, str_current + 1, str_size);

			str_out=str_aux;
		}
		else {
			throw_error(filename, line,str_start, str_current, "invalid size property (%i)", str_size);
		}
		return ignore_blanks(str_end + 1, line);
	}

	char * parse_primitive(
			  const char *str_start
			, char *str_current
			, JsonVar *json_var
			, const std::string & variable_name=""
			, const std::string & key_id=""
			, const char *filename=""
			, int line=-1){
		// ptr_data: can be a bool/string or number in function of type value
		// type_value: defines the value to parse
		// key in case
		int bytes_readed=0;
		char *str_end=NULL;
		void *ptr_data=NULL;
		float number_aux=0;
		bool bool_aux=false;
		std::string str_aux="";
		JsonVarType js_container_type=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		int type_value=JsonVarType::JSON_VAR_TYPE_UNKNOWN;

		if(json_var->getType()  == JsonVarType::JSON_VAR_TYPE_MAP){
			js_container_type=JsonVarType::JSON_VAR_TYPE_MAP;
		}else if(JsonVarType::JSON_VAR_TYPE_VECTOR){ // create a new slot
			js_container_type=JsonVarType::JSON_VAR_TYPE_VECTOR;
		}
		/*else{

			switch(json_var->getType()){
			case 	JsonVarType::JSON_VAR_TYPE_BOOLEAN:
			case 	JsonVarType::JSON_VAR_TYPE_NUMBER:
			case 	JsonVarType::JSON_VAR_TYPE_STRING:
			default: // unexpected
				break;
			}
		}*/

		if (*str_current == '\'' || *str_current == '\"') {// try string ...

			char start_chr=*str_current++;

			while(*str_current!='\n' && *str_current!='\r' && *str_current!=0 && (*str_current !=(start_chr) )){
				str_aux=*str_current++;
			}

			if(*str_current !=(start_chr)){

				throw_error(filename, line,str_start, str_current, "string not closed with %s", start_chr);
			}

			str_current++;

			type_value = JsonVarType::JSON_VAR_TYPE_STRING;
		}
		else if (!strncmp(str_current, "true", 4)) { // true detected ...
			type_value = JsonVarType::JSON_VAR_TYPE_BOOLEAN;
			bool_aux = true;
			str_current+=4;
		}
		else if (!strncmp(str_current, "false", 5)) {// boolean detected
			type_value = JsonVarType::JSON_VAR_TYPE_BOOLEAN;
			bool_aux = false;
			str_current+=5;
		}
		else { // must a number
			// try read until next comma
			char str_value[1024]={0};
			str_end = advance_to_one_of_collection_of_char(str_current + 1, (char *)end_char_standard_value, line);
			bytes_readed = str_end - str_current;
			if (*str_end != 0) {
				str_end--;
			}

			if (bytes_readed > 0) {
				char *p;
				float number_value = 0;
				number_value = (float)strtod(str_value, &p);
				if (*p == '\0') {
					type_value = JsonVarType::JSON_VAR_TYPE_NUMBER;
					number_aux = number_value;
				}

				str_current+=bytes_readed;
			}
		}

		// if container type is map/vector addit
		type_value += (int)js_container_type;

		// ok, check if the value parsed is the same as c_property (only saves particular elements (string/boolean/etc) but not property groups (it was saved already in recursion before)
		if (!json_var->isParsed()){

			if ((type_value & json_var->getType()) == type_value) {

				switch (json_var->getType()) {
				default:
				case 	JsonVarType::JSON_VAR_TYPE_UNKNOWN:
					fprintf(stderr,"unknown type %i", type_value);
					return 0;
					break;
				case 	JsonVarType::JSON_VAR_TYPE_BOOLEAN:
					print_info_json("set value %i into variable \"%s\"", bool_value, str_variable_name);
					*(ZJ_CAST_JSON_VAR_BOOLEAN json_var) = bool_aux;
					break;
				case 	JsonVarType::JSON_VAR_TYPE_NUMBER:
					print_info_json("set value %f into variable \"%s\"", number_value, str_variable_name);
					*(ZJ_CAST_JSON_VAR_NUMBER json_var) = number_aux;
					break;
				case 	JsonVarType::JSON_VAR_TYPE_STRING:
					print_info_json("set value %s into variable \"%s\"", val, str_variable_name);
					*(ZJ_CAST_JSON_VAR_STRING json_var) = str_aux;
					break;

					// VECTORS
				case 	JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
					print_info_json("added value %s into vector \"%s\"", bool_aux?"true":"false", str_variable_name);
					(*(ZJ_CAST_JSON_VAR_VECTOR_OF_BOOLEANS json_var)).add(bool_aux);
					break;

				case 	JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
					print_info_json("added value %f into vector \"%s\"", number_aux, str_variable_name);
					(*(ZJ_CAST_JSON_VAR_VECTOR_OF_NUMBERS json_var)).add(number_aux);
					break;

				case 	JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS:
					print_info_json("added value string %s into vector \"%s\"", val, str_variable_name);
					(*(ZJ_CAST_JSON_VAR_VECTOR_OF_STRINGS json_var)).add(str_aux);
					break;

					// MAPS
				case 	JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS:
					print_info_json("added value number %s=%s into map \"%s\"", keyid.c_str(),bool_aux?"true":"false", str_variable_name);
					(*(ZJ_CAST_JSON_VAR_MAP_OF_BOOLEANS json_var)).insert(key_id,bool_aux);
					break;
				case 	JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS:
					print_info_json("added value number %s=%f into map \"%s\"", keyid.c_str(),number_aux, str_variable_name);
					(*(ZJ_CAST_JSON_VAR_MAP_OF_NUMBERS json_var)).insert(key_id,number_aux);
					break;
				case 	JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS:
					print_info_json("added value string %s=%s into map \"%s\"", key_id.c_str(), str_aux.c_str(), str_variable_name);
					(*(ZJ_CAST_JSON_VAR_MAP_OF_STRINGS json_var)).insert(key_id,str_aux);
					break;

				case 	JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS:
				case 	JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
				case 	JsonVarType::JSON_VAR_TYPE_OBJECT:
					// Do nothing
					break;
				}
				// set parsed element...
				if (js_container_type == JsonVarType::JSON_VAR_TYPE_UNKNOWN){
					json_var->setParsed(true);
				}
			}
			else {
				throw_warning(filename
						, line
						,"variable \"%s\"not matches. JSon is %s and C struct is %s"
						, variable_name.c_str()
						, JsonVar::idTypeToString(type_value)
						, json_var->toTypeStr());
			}

			return str_current;
		}

		return NULL;
	}

	int parse_main_recursive(const char * str_start, JsonVar *_root,const char *filename, int & line, int level) {
		std::string variable_name,key_id;
		const char *str_variable_name;

		JsonVarType js_container_type=JsonVarType::JSON_VAR_TYPE_UNKNOWN,
					type_value=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		char *str_end = NULL;
		char *str_current = (char *)str_start;
		JsonVar *c_property=NULL, *c_data=NULL;
		int bytes_readed;
		bool end = false;
		bool ok = false;
		bool starts_with_vector = false;
		bool more_group_properties = true;
		bool another_element;


		if (IS_EMPTY(str_start)){
			return 0;
			//throw_error(this->filename, -1,NULL, NULL, "Empty string");
		}

		str_current = ignore_blanks(str_current, line);

		if (*str_current == '[' && (level == 0)) { // detected anonymous vector (only valid for first level)...
			starts_with_vector = true;
			str_current++;
			str_current = ignore_blanks(str_current, line);

		}

		while (more_group_properties) {//(*str_current == INI_GROUP || *str_current == '[')){ // valid group...

			str_current = ignore_blanks(str_current, line);

			if (*str_current == INI_GROUP) {

				c_data = _root;
				// because we find a vector of objects at start, we manage this particular case to create a new object
				if (level == 0) {
					if(_root->getType() == JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS){
						c_data=_root->newData();
					}
				}

				set_parsed_to_false_all_properies(c_data);

				str_current++;

				// the action starts here! looking for the properties and its values inside property group.
				while (!end) {
					js_container_type=JsonVarType::JSON_VAR_TYPE_UNKNOWN;

					// start working with ...
					// capture property inside...
					str_current = ignore_blanks(str_current, line);

					if (*str_current != END_GROUP) // void property return...
					{
						bool parse_value = true;
						JsonVarType c_property_type = JsonVarType::JSON_VAR_TYPE_UNKNOWN;
						str_current =read_string_between_quotes(str_start,str_current,variable_name,filename,line);
						str_variable_name=variable_name.c_str();

						if (*str_current != ':') {// ok check value
							throw_error(filename, line,str_start, str_current, "Error ':' expected");
						}

						str_current = ignore_blanks(str_current + 1, line);

						// get c property
						c_property = find_property(c_data, variable_name);

						if (c_property != NULL){
							c_property_type=c_property->getType();
							if (c_property->isParsed()) {
								throw_warning(filename, line,"%s was already parsed (duplicate?)", str_variable_name);
							}
						}

						// check if group
						js_container_type = // is starting vector
											(*str_current == '[') ? JsonVarType::JSON_VAR_TYPE_VECTOR
											// is a map is everything that starts with { and the variable type to parse is not a JsonVarObject
											:(*str_current == '{') && (c_property_type & JsonVarType::JSON_VAR_TYPE_MAP)? JsonVarType::JSON_VAR_TYPE_MAP
											// not a container
											:JsonVarType::JSON_VAR_TYPE_UNKNOWN; // gets a pair (name,value) per iteration

						type_value = JsonVarType::JSON_VAR_TYPE_UNKNOWN;

						another_element = false;

						if (js_container_type != JsonVarType::JSON_VAR_TYPE_UNKNOWN) {
							str_current = ignore_blanks(str_current + 1, line);

							if(js_container_type != JsonVarType::JSON_VAR_TYPE_VECTOR && *str_current == ']'){
								str_current = ignore_blanks(str_current + 1, line);
								parse_value = false;
							}else if(js_container_type != JsonVarType::JSON_VAR_TYPE_MAP && *str_current == '}'){
								str_current = ignore_blanks(str_current + 1, line);
								parse_value = false;
							}
						}

						// capture values ...
						if (parse_value) {
							do {
								ok = true;
								type_value = JsonVarType::JSON_VAR_TYPE_UNKNOWN;

								if(js_container_type == JsonVarType::JSON_VAR_TYPE_MAP){ // we have to get the key first
									//
									str_current=read_string_between_quotes(str_start,str_current,key_id,filename,line);

									if(*str_current!=':'){
										throw_error(filename, line,str_start, str_current, "Expected ':' after map key '%s'",key_id.c_str());
									}

									str_current = ignore_blanks(str_current + 1, line);
								}

								// get the value
								if (*str_current == INI_GROUP) {// starting object detected...
									JsonVar *json_object = c_property;

									if (json_object != NULL) {
										switch(js_container_type){
										case JsonVarType::JSON_VAR_TYPE_VECTOR: // vector of objects...
											json_object = json_object->newData();
											break;
										case JsonVarType::JSON_VAR_TYPE_MAP: // map of objects...
											json_object = json_object->newData(key_id);
											break;
										}
									}

									// passing NULL if the record has been initialized (it doens't matter any c property in advence...
									if ((bytes_readed = parse_main_recursive(str_current, json_object, filename, line, level + 1)) == 0) {
										return 0;
									}

									type_value = JsonVarType::JSON_VAR_TYPE_OBJECT;

								}
								else { // parse primitive ...

									if((str_current=parse_primitive(str_start,str_current,c_property,variable_name,key_id,filename,line)) == NULL){
										throw_error(filename, line,str_start, str_current, "Impossible to parse value of property \"%s\"", str_variable_name);
										return 0;
									}
								}

								//str_current += bytes_readed;

								str_current = ignore_blanks(str_current, line);
								another_element = false;

								// another element...
								if((js_container_type !=JsonVarType::JSON_VAR_TYPE_UNKNOWN)  && *str_current == ',') {
									str_current = ignore_blanks(str_current + 1, line);
									another_element = true;
								}
								else{

									// special case (another vector/map element is needed)
									switch(js_container_type){
									default:
									case  JsonVarType::JSON_VAR_TYPE_UNKNOWN:
										break;
									case JsonVarType::JSON_VAR_TYPE_VECTOR:
										if(*str_current != ']') {
											throw_error(filename, line,str_start, str_current, "Was expect a ',' , ']' ");
										}
										break;
									case JsonVarType::JSON_VAR_TYPE_MAP:
										if(*str_current != '}') {
											throw_error(filename, line,str_start, str_current, "Was expect a ',' , '}' ");
										}
										break;
									}
								}

							} while (
								another_element					// any other
							);
						}

						if(js_container_type !=  JsonVarType::JSON_VAR_TYPE_UNKNOWN){
							if (c_property){
								c_property->setParsed(true);
							}
							str_current = ignore_blanks(str_current + 1, line);
						}

						end = (*str_current == '}');
						if (!end){
							if (*str_current != ',') {
								throw_error(filename, line,str_start, str_current, "an \',\' was expected!");
							}
						}
						// forward to next property
						str_current = ignore_blanks(str_current + 1, line);
					}
					else { // void property group
						str_current = ignore_blanks(str_current + 1, line);
						return str_current - str_start; // return..
					}
				}
			}
			else {
				throw_error(filename, line,str_start, str_current, "It doesn't possible check begin/end group {");
			}

			if (starts_with_vector) {
				str_current = ignore_blanks(str_current, line);
				if (*str_current == ']')
					more_group_properties = false;
				else if (*str_current == ',') {
					end = false; // set for next property group ...
					str_current++;
				}
				else {
					more_group_properties = false;
					throw_error(filename, line,str_start, str_current, "Impossible to find ']' current caracter is %c", *str_current);
				}
			}
			else // breaks the main root.
				more_group_properties = false;
		}
		return str_current - str_start;
	}


	void parse_main(const char * str_start, JsonVar *_root,const char *filename) {
		int line=1;

		// check if primitive
		switch(_root->getType()){
		case JsonVarType::JSON_VAR_TYPE_BOOLEAN:
		case JsonVarType::JSON_VAR_TYPE_NUMBER:
		case JsonVarType::JSON_VAR_TYPE_STRING:
			parse_primitive(str_start,(char *)str_start,_root,"","",filename,0);
			break;
		}

		parse_main_recursive(str_start, _root,filename, line, 0);

	}
};

