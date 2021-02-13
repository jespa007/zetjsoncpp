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

		sprintf(temp_buff,"%s\n%s",text,where);
		throw parse_error_exception(file,line,temp_buff);
	}

	void throw_warning(const char *file, int line,const char *string_text, ...) {

		char temp_buff[4096]={0};
		char  text[MAX_C_STRING]={0};
		CAPTURE_VARIABLE_ARGS(text, string_text);
		sprintf(temp_buff,"[%s:%i] %s",zj_path::get_filename(file).c_str(),line,text);
		throw parse_warning_exception(file,line,temp_buff);
	}

	char * parse_json_object(const char * _str_start, char *_str_current, JsonVar *_root,const char *filename, int & line);

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

	char * parse_json_value(
		  char *_str_current
		, JsonVar *json_var
		, std::string & error
	){
		// ptr_data: can be a bool/string or number in function of type value
		// type_value: defines the value to parse
		// key in case
		char *str_current = (char *)_str_current;
		int bytes_readed=0;
		char *str_end=NULL;
		int line=0;
		bool ok=false;
		JsonVarType type_data=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		void *ptr_data=NULL;

		if(json_var !=NULL){
			type_data=json_var->getType();
			ptr_data=json_var->getPtrValue();
		}

		if (*str_current == '\"') {// try string ...
			std::string *str_aux=(std::string *)ptr_data;
			*str_current++;

			while(*str_current!='\n' && *str_current!='\r' && *str_current!=0 && (*str_current !='\"' )){
				if(str_aux != NULL){
					*str_aux+=*str_current;
				}
				str_current++;
			}

			if(*str_current !='\"'){
				error="string value not closed";
				return NULL;
			}

			str_current++;
			ok=(type_data ==  JsonVarType::JSON_VAR_TYPE_STRING);
		}
		else if (strncmp(str_current, "true", 4)==0) { // true detected ...
			if(ptr_data != NULL){
				*((bool *) ptr_data)= true;
			}
			str_current+=4;
			ok=type_data ==  JsonVarType::JSON_VAR_TYPE_BOOLEAN;
		}
		else if (strncmp(str_current, "false", 5) == 0) {// boolean detected
			if(ptr_data != NULL){
				*((bool *) ptr_data) = false;
			}
			str_current+=5;
			ok=type_data ==  JsonVarType::JSON_VAR_TYPE_BOOLEAN;
		}
		else{ // must a number
			// try read until next comma
			char str_value[1024]={0};

			str_end = advance_to_one_of_collection_of_char(str_current + 1, (char *)end_char_standard_value, line);
			bytes_readed = str_end - str_current;
			if (*str_end != 0) {
				str_end--;
			}

			if (bytes_readed > 0) {
				char *p;
				// copy string...
				strncpy(str_value,str_current,bytes_readed);
				float number_value = 0;
				number_value = (float)strtod(str_value, &p);

				if (*p == '\0') {
					if(ptr_data!=NULL){
						*((float *) ptr_data) = number_value;
					}
				}
				str_current+=bytes_readed;
				ok=type_data ==  JsonVarType::JSON_VAR_TYPE_NUMBER;
			}
		}

		// if the parse was ok or json_var was not found we advance anyway
		if(ok || json_var == NULL){
			return str_current;
		}

		return NULL;
	}

	char * parse_json_vector_of_values(
			const char *_str_start
			,char *_str_current
			, JsonVar *json_var
			, const char *filename
			, int & line
			){

		JsonVarType type_data=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		std::string error;

		if(json_var !=NULL){
			type_data=json_var->getType();

			if((type_data & JsonVarType::JSON_VAR_TYPE_VECTOR) != JsonVarType::JSON_VAR_TYPE_VECTOR){
				throw std::runtime_error("Internal error JsonVar expected as Type vector");
				return NULL;
			}
		}

		_str_current = ignore_blanks(_str_current, line);

		if(*_str_current != '['){
			throw_error(filename, line,NULL,NULL,"A '[' was expected to parse JsonVarVector type");
			return 0;
		}

		_str_current = ignore_blanks(_str_current+1, line);

		if(*_str_current != ']'){ // do parsing primitive...

			do{
				JsonVar *json_element = NULL;
				if(json_var != NULL){
					json_element = json_var->newJsonVar();

					if((type_data & JsonVarType::JSON_VAR_TYPE_OBJECT)== JsonVarType::JSON_VAR_TYPE_OBJECT){
						_str_current=parse_json_object(_str_start,_str_current,json_element,filename,line);
					}else{
						if((_str_current=parse_json_value(_str_current,json_element,error)) == NULL){
							throw_error(filename, line,_str_start, _str_current, "Impossible to parse primitive value: %s", error.c_str());
							return 0;
						}
					}
				}else{ // try to deduce
					_str_current=parse_json_var(_str_start,_str_current,json_var,filename,line);
				}

				_str_current = ignore_blanks(_str_current, line);

				if(*_str_current==','){
					_str_current = ignore_blanks(_str_current+1, line);
				}else if(*_str_current!=']'){
					throw_error(filename, line,_str_start, _str_current, "Expected ',' or ']'");
					return 0;
				}

			}while(*_str_current != ']');
		}

		return _str_current+1;
	}

	char * parse_json_map_of_values(
			const char *_str_start
			,char *_str_current
			, JsonVar *json_var
			, const char *filename
			, int & line
			){
		char *str_current = (char *)_str_current;
		JsonVarType type_data=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		std::string error;
		std::string key_id;

		if(json_var !=NULL){
			type_data=json_var->getType();

			if((type_data & JsonVarType::JSON_VAR_TYPE_MAP) != JsonVarType::JSON_VAR_TYPE_MAP){
				throw std::runtime_error("Internal error JsonVar expected as Type map");
				return NULL;
			}
		}

		str_current = ignore_blanks(str_current, line);

		if(*str_current != '{'){
			throw_error(filename, line,NULL,NULL,"A '[' was expected to parse JsonVarVector type");
			return 0;
		}

		str_current = ignore_blanks(str_current+1, line);

		if(*str_current != '}'){ // do parsing primitive...
			do{

				// read key_id
				str_current=read_string_between_quotes(_str_start,str_current,key_id,filename,line);

				if(*str_current!=':'){
					throw_error(filename, line,_str_start, str_current, "Expected ':' after map key '%s'",key_id.c_str());
				}

				str_current = ignore_blanks(str_current + 1, line);

				// read value
				JsonVar *json_element = NULL;
				if(json_var != NULL){
					json_element = json_var->newJsonVar();
				}

				if((str_current=parse_json_value(str_current,json_element,error)) == NULL){
					throw_error(filename, line,_str_start, str_current, "Impossible to parse primitive value: %s", error.c_str());
					return 0;
				}

				str_current = ignore_blanks(str_current, line);

				if(*str_current==','){
					str_current = ignore_blanks(str_current+1, line);
				}else if(*str_current!='}'){
					throw_error(filename, line,_str_start, str_current, "Expected ',' or ']'");
					return 0;
				}

			}while(*str_current != '}');
		}

		return str_current+1;
	}

	char * parse_json_var(const char * _str_start,char * _str_current, JsonVar *_json_var,const char *filename, int & line) {
		// PRE: If json_var == NULL it parses but not saves
		std::string error="";

		if(_json_var == NULL){
			//try to deduce ...
			if(*_str_current == '['){ // try parse vector
				_str_current=parse_json_vector_of_values( _str_start, _str_current+1, _json_var,filename,  line);
			}else if(*_str_current == '{') {// can be a map or object but we try as a object
				_str_current=parse_json_object( _str_start, _str_current+1, _json_var,filename,  line);
			}else{
				if((_str_current=parse_json_value(_str_current,_json_var,error))==NULL){
					throw_error(filename, line,_str_start,_str_current,"Cannot parse value");
				}
			}
		}else{

			// check if primitive
			switch(_json_var->getType()){
			case JsonVarType::JSON_VAR_TYPE_BOOLEAN:
			case JsonVarType::JSON_VAR_TYPE_NUMBER:
			case JsonVarType::JSON_VAR_TYPE_STRING:

				if((_str_current=parse_json_value(_str_current,_json_var,error))==NULL){
					throw_error(filename, line,_str_start,_str_current,"Cannot parse value as %s",_json_var->toTypeStr()));
				}
				break;
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS:
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
				_str_current=parse_json_vector_of_values(_str_start,_str_current,_json_var,filename,line);
				break;
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS:
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS:
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS:
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS:
				_str_current=parse_json_map_of_values(_str_start,_str_current,_json_var,filename,line);
				break;
			case JsonVarType::JSON_VAR_TYPE_OBJECT:
				_str_current=parse_json_object(_str_start, _str_current,_json_var,filename, line);
				break;
			}
		}

		return _str_current;
	}

	char * parse_json_object(const char * _str_start,char *_str_current, JsonVar *_json_var,const char *filename, int & line) {
		std::string variable_name,key_id;
		std::string error;
		const char *str_variable_name;

		if(*_str_current != '{'){
			throw_error(filename, line,NULL,NULL,"A '[' was expected to parse JsonVarObject type");
			return 0;
		}

		_str_current = ignore_blanks(_str_current+1, line);

		if(*_str_current != '}'){ // do parsing object values...
			do{
				JsonVar *c_property=NULL;
				_str_current =read_string_between_quotes(_str_start,_str_current,variable_name,filename,line);
				str_variable_name=variable_name.c_str();

				if (*_str_current != ':') {// ok check value
					throw_error(filename, line,_str_start, _str_current, "Error ':' expected");
				}

				_str_current = ignore_blanks(_str_current + 1, line);

				// get c property
				c_property = find_property(_json_var, variable_name);

				if (c_property != NULL){
					if (c_property->isParsed()) {
						throw_warning(filename, line,"%s was already parsed (duplicate?)", str_variable_name);
					}
				}

				_str_current=parse_json_var(_str_start,_str_current,c_property,filename,line);

				_str_current = ignore_blanks(_str_current, line);

				if(*_str_current==','){
					_str_current = ignore_blanks(_str_current+1, line);
				}else if(*_str_current!='}'){
					throw_error(filename, line,_str_start, _str_current, "Expected ',' or '}'");
					return 0;
				}

			}while(*_str_current != '}');
		}

		return _str_current+1;
	}
};

