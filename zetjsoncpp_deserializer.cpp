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

#define PREVIEW_SSTRING(start, current,n) (((current)-(n))<((start))?(start):((current)-(n)))

namespace zetjsoncpp{

	char * deserialize_json_var_object(DeserializeData *deserialize_data, const char *str_current, int & line, JsonVar *json_var);

	void json_deserialize_error(DeserializeData *deserialize_data, const char *str_current,int line, const char *string_text, ...) {


		char  where[1024]={0};
		char  text[MAX_C_STRING]={0};
		char temp_buff[1024]={0};
		CAPTURE_VARIABLE_ARGS(text, string_text);
		char *aux=(char *)str_current-1;
		char captured[100]={0};

		int n=0;

		/*if(*(aux) == '\r' || *(aux) == '\n' ){
			aux--;
		}

		while(n<40 && deserialize_data->str_start<aux){
			if(*(aux-1) == '\r' || *(aux-1) == '\n'){
				break;
			}
			aux--;
			n++;
		}

		strncpy(captured,aux,n);*/


		/*sprintf(where,"...%s..."
				  "\n              ^   "
				  "\n  ------------+ \n", captured);//PREVIEW_SSTRING(deserialize_data->str_start, aux, n));
		//strncpy(where,str_start,str_end-str_start);

		sprintf(temp_buff,"%s\n%s\n",text,where);*/
		throw deserialize_error_exception(deserialize_data->filename,line,text);
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

		char *aux_p = (char *)c_data->getPtrDataStart();
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

		char *aux_p = (char *)c_data->getPtrDataStart();
		char *end_p = (char *)c_data->getPtrDataEnd();

		// Main loop iteration to whole C struct
		for (; aux_p < end_p; ) {

			JsonVar * p_sv = (JsonVar *)aux_p;
			p_sv->setParsed(false);

			aux_p += p_sv->getSizeData();
		}
	}

	char * read_string_between_quotes(DeserializeData *deserialize_data, const char *str_start,int & line, std::string * str_out){
		char *str_current = (char *) str_start;
		size_t str_size;

		if(str_out != NULL){
			*str_out="";
		}

		if (*str_current == '\"'){ // try to single quote...
			str_current++;
			while(*str_current!='\n' && *str_current!='\r' && *str_current!=0 &&  (*str_current=='\"' && *(str_current-1)!='\\')==false){
				if(str_out != NULL){
					(*str_out)+=*str_current;
				}
				str_current++;
			}
		}else{
			json_deserialize_error(deserialize_data,str_start,line,"expected string value");
		}

		if(*str_current != '\"'){
			json_deserialize_error(deserialize_data,str_start,line,"string value not closed");
		}

		return ignore_blanks(str_current+1, line);
	}

	char * deserialize_json_var_value(
		DeserializeData *deserialize_data
		,const char *str_start
		, int & line
		, JsonVar *json_var
	){
		// ptr_data: can be a bool/string or number in function of type value
		// type_value: defines the value to parse
		// key in case
		char *str_current = (char *)str_start;
		int bytes_readed=0;
		std::string str_value="";
		char *str_end=NULL;
		bool ok=false;
		JsonVarType type_data=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		void *ptr_data=NULL;

		if(json_var !=NULL){
			type_data=json_var->getType();
			ptr_data=json_var->getPtrValue();
		}

		if (*str_current == '\"') {// try string ...
			//std::string str_aux;
			str_current=read_string_between_quotes(deserialize_data,str_current,line,&str_value);

			if(type_data ==  JsonVarType::JSON_VAR_TYPE_STRING){ // is string, save...
				*(std::string *)ptr_data = str_value;
				ok=true;
			}
		}
		else if (strncmp(str_current, "true", 4)==0) { // true detected ...
			str_value="true";
			str_current+=4;
			if(type_data ==  JsonVarType::JSON_VAR_TYPE_BOOLEAN){
				if(ptr_data != NULL){
					*((bool *) ptr_data)= true;
				}
				ok=true;
			}
		}
		else if (strncmp(str_current, "false", 5) == 0) {// boolean detected
			str_value="false";
			str_current+=5;


			if(type_data ==  JsonVarType::JSON_VAR_TYPE_BOOLEAN){
				if(ptr_data != NULL){
					*((bool *) ptr_data) = false;
				}

				ok=true;
			}
		}
		else{ // must a number
			// try read until next comma
			char str_char_value[1024]={0};

			str_end = advance_to_one_of_collection_of_char(str_current, (char *)end_char_standard_value, line);
			bytes_readed = str_end - str_current;
			if (*str_end != 0) {
				str_end--;
			}

			if (bytes_readed > 0) {
				// copy string...
				strncpy(str_char_value,str_current,bytes_readed);
				str_value=str_char_value;
				str_current+=bytes_readed;


				float number_value = 0;
				if(zetjsoncpp::zj_strutils::str_to_float(&number_value,str_value) == zetjsoncpp::zj_strutils::STR_2_NUMBER_SUCCESS){
					if(type_data ==  JsonVarType::JSON_VAR_TYPE_NUMBER){
						if(ptr_data!=NULL){
							*((float *) ptr_data) = number_value;
						}

						ok=true;
					}

				}
			}
		}

		// if the parse was ok or json_var was not found we advance anyway
		if(ok || json_var == NULL){
			if(ok == true && json_var != NULL){
				json_var->setParsed(true);
			}

			return str_current;
		}
		else{
			if(json_var != NULL){

				throw deserialize_error_exception(
						zj_path::get_filename(deserialize_data->filename).c_str()
						,line,zetjsoncpp::zj_strutils::format(
								"Cannot parse value \"%s\" as %s"
								,str_value.c_str()
								,json_var->getTypeStr()
						)
				);

			}
		}

		return NULL;
	}

	char * deserialize_json_var_vector(
			DeserializeData *deserialize_data
			,const char *str_start
			, int & line
			, JsonVar *json_var
			){
		char *str_current = (char *)str_start;
		JsonVarType type_data=JsonVarType::JSON_VAR_TYPE_UNKNOWN;
		std::string error;

		if(json_var !=NULL){
			type_data=json_var->getType();
			if((type_data & JsonVarType::JSON_VAR_TYPE_VECTOR) != JsonVarType::JSON_VAR_TYPE_VECTOR){
				throw std::runtime_error("Internal error JsonVar expected as Type vector");
				return NULL;
			}
		}

		str_current = ignore_blanks(str_current, line);

		if(*str_current != '['){
			json_deserialize_error(deserialize_data,str_start,line,"A '[' was expected to parse JsonVarVector type");
			return 0;
		}

		str_current = ignore_blanks(str_current+1, line);

		if(*str_current != ']'){ // do parsing primitive...

			do{
				JsonVar *json_var_property = NULL;
				if(json_var != NULL){
					json_var_property = json_var->newJsonVar();

					if((type_data & JsonVarType::JSON_VAR_TYPE_OBJECT)== JsonVarType::JSON_VAR_TYPE_OBJECT){
						str_current=deserialize_json_var_object(deserialize_data, str_current, line, json_var_property);
					}else{
						str_current=deserialize_json_var_value(deserialize_data,str_current,line, json_var_property);
					}
				}else{ // try to deduce
					str_current=deserialize_json_var(deserialize_data,str_current,line,json_var);
				}

				str_current = ignore_blanks(str_current, line);

				if(*str_current==','){
					str_current = ignore_blanks(str_current+1, line);
				}else if(*str_current!=']'){
					json_deserialize_error(deserialize_data, str_current, line,  "Expected ',' or ']'");
					return 0;
				}

			}while(*str_current != ']');
		}

		if(json_var != NULL){
			json_var->setParsed(true);
		}

		return str_current+1;
	}

	char * deserialize_json_var_object(DeserializeData *deserialize_data, const char * str_start, int & line, JsonVar *json_var) {
		char *str_current = (char *)str_start;
		std::string variable_name,key_id;
		std::string error;
		JsonVarType type=JsonVarType::JSON_VAR_TYPE_UNKNOWN;

		if(json_var != NULL){
			type=json_var->getType();
		}

		str_current = ignore_blanks(str_current, line);

		if(*str_current != '{'){
			json_deserialize_error(deserialize_data, str_start, line, "A '{' was expected to parse %s type",json_var!=NULL?json_var->getTypeStr():"");
			return NULL;
		}

		str_current = ignore_blanks(str_current+1, line);

		if(*str_current != '}'){ // do parsing object values...
			do{
				JsonVar *json_var_property=NULL;
				str_current =read_string_between_quotes(deserialize_data, str_current, line, &key_id);
				if (*str_current != ':') {// ok check value
					json_deserialize_error(deserialize_data, str_current, line, "Error ':' expected");
					return NULL;
				}

				str_current = ignore_blanks(str_current + 1, line);

				// get c property
				if(json_var==NULL || type == JsonVarType::JSON_VAR_TYPE_OBJECT){ // parse json object
					json_var_property = find_property(json_var, key_id);
					if (json_var_property != NULL){
						if (json_var_property->isDeserialized()) {
							json_deserialize_error(deserialize_data, str_current, line,"property name \"%s\" already exist", key_id.c_str());
							return NULL;
						}
					}

				}else{ // parse map...
					if(json_var != NULL){
						try{
							json_var_property = json_var->newJsonVar(key_id);
						}catch(std::exception &ex){
							json_deserialize_error(deserialize_data, str_current, line,ex.what());
							return NULL;
						}
					}
				}

				str_current=deserialize_json_var(deserialize_data, str_current, line, json_var_property);


				str_current = ignore_blanks(str_current, line);

				if(*str_current==','){
					str_current = ignore_blanks(str_current+1, line);
				}else if(*str_current!='}'){
					json_deserialize_error(deserialize_data, str_current, line, "Expected ',' or '}'");
					return NULL;
				}

			}while(*str_current != '}');
		}

		if(json_var != NULL){
			json_var->setParsed(true);
		}


		return str_current+1;
	}

	char * deserialize_json_var(DeserializeData *deserialize_data, const char * str_start, int & line,JsonVar *json_var) {
		// PRE: If json_var == NULL it parses but not saves
		char * str_current = (char *)str_start;
		std::string error="";
		str_current = ignore_blanks(str_current, line);

		if(json_var == NULL){ // continue parse file/string
			//try to deduce ...
			if(*str_current == '['){ // try parse vector
				str_current=deserialize_json_var_vector(deserialize_data, str_current, line,json_var);
			}else if(*str_current == '{') {// can be a map or object but we try as a object
				str_current=deserialize_json_var_object(deserialize_data, str_current, line,json_var);
			}else{
				str_current=deserialize_json_var_value(deserialize_data, str_current,line,json_var);
			}
		}else{

			// check if primitive
			switch(json_var->getType()){
			case JsonVarType::JSON_VAR_TYPE_BOOLEAN:
			case JsonVarType::JSON_VAR_TYPE_NUMBER:
			case JsonVarType::JSON_VAR_TYPE_STRING:
				str_current=deserialize_json_var_value(deserialize_data,str_current,line,json_var);
				break;
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS:
			case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
				str_current=deserialize_json_var_vector(deserialize_data, str_current, line, json_var);
				break;
			default: // tries to parse a map of values or object
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS:
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS:
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS:
			case JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS:
			case JsonVarType::JSON_VAR_TYPE_OBJECT:
				str_current=deserialize_json_var_object(deserialize_data, str_current, line, json_var);
				break;
			}
		}

		return str_current;
	}
};

