//    This file is part of FastJson2Cpp.
//
//    FastJson2Cpp is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    FastJson2Cpp is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with FastJson2Cpp.  If not, see <http://www.gnu.org/licenses/>.


//#include "CParserJson.h"
#include <stdlib.h>

#define MAX_NAME_PROPERTY 100


#define INI_GROUP	'{'
#define END_GROUP	'}'


#ifdef __DEBUG__
#define __VERBOSE_MESSAGE__
#endif





#define JS_STRING_CAST 			(CParserVarString<> *)
#define JS_ARRAY_STRING_CAST 		(CParserVarArrayString<> *)
#define JS_BOOL_CAST 		(CParserVarBool<> *)
#define JS_ARRAY_BOOL_CAST 		(CParserVarArrayBool<> *)
//#define JS_INT32_CAST 				(CParserVarInt32<> *)
//#define JS_ARRAY_INT32_CAST 		(CParserVarArrayInt32<> *)
#define JS_NUMBER_CAST 				(CParserVarNumber<> *)
#define JS_ARRAY_NUMBER_CAST 		(CParserVarArrayNumber<> *)



#define PREVIEW_SSTRING(start, current,n) (((current)-(n))<((start))?(start):((current)-(n)))

static bool IS_SINGLE_COMMENT(char *str){

	if((*str!=0) && *str=='/'){
		return *(str+1)=='/';
	}
	return false;
}

static bool IS_START_COMMENT(char *str){

	if((*str!=0) && *str=='/'){
		return *(str+1)=='*';
	}
	return false;
}

static bool IS_END_COMMENT(char *str){

	if((*str!=0) && *str=='*'){
		return *(str+1)=='/';
	}
	return false;
}

static char *ADVANCE_TO_CHAR(char *str,char c) {
	char *aux_p = str;
	// make compatible windows format (\r)...
	while(*aux_p!='\n' && *aux_p!='\r' && *aux_p!=0 && (*aux_p !=(c) )) aux_p++;

	if(*aux_p=='\r')
		aux_p++;

	return aux_p;
}

static char *ADVANCE_TO_END_COMMENT(char *aux_p, int &m_line){

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




static char *IGNORE_BLANKS(char *str, int &m_line) {
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



static char *ADVANCE_TO_ONE_OF_COLLECTION_CHAR(char *str,char *end_char_standard_value, int &m_line) {
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

const char end_char_standard_value[]={
		',',
		'}',
		' ',
		'\t',
		'\n',
		'\r', // for make compatible windows...
		']',
		0
};

template <typename _T>
CParserVar *CParserJson<_T>::findProperty(CParserVar * c_data, char *property_name){

	// no data no search...
	if(c_data==NULL) return NULL;

	char *aux_p = (char *)c_data->p_data;
	char *end_p = (char *)c_data->p_end_data;

	//1. Iterar per tota la estructura C++
	for(;aux_p < end_p; ) {

		CParserVar * p_sv = (CParserVar *)aux_p;
		if(p_sv->_m_pvariableName == property_name)
			return p_sv;

		aux_p += p_sv->size_data;
	}

	return NULL;
}


template <typename _T>
void CParserJson<_T>::setPropertiesParsedToFalse(CParserVar * c_data){

	// no data no search...

	if(c_data == NULL)
		return;

	char *aux_p = (char *)c_data->p_data;
	char *end_p = (char *)c_data->p_end_data;

	//1. Iterar per tota la estructura C++
	for(;aux_p < end_p; ) {

		CParserVar * p_sv = (CParserVar *)aux_p;
		p_sv->setParsed(false);

		aux_p += p_sv->size_data;
	}

}


//int m_json_line=0;
template <typename _T>
void CParserJson<_T>::print_error_json(const char *start_str, char *current_ptr, const char *string_text, ...){



    char  text[500];
    CAPTURE_VARIABLE_ARGS(text, string_text);

	CLog::print(this->m_filesrc,this->m_line,CLog::LOG_ERROR	, text);
	printf("\n...%.15s...", PREVIEW_SSTRING(start_str,current_ptr,15));
	printf("\n               ^   ");
	printf("\n  -------------+ \n");


}
template <typename _T>
void CParserJson<_T>::print_warning_json(const char *string_text, ...){

	
		char  text[500];
		CAPTURE_VARIABLE_ARGS(text, string_text);
		CLog::print(this->m_filesrc,this->m_line,CLog::LOG_WARNING,text);
    

}

template <typename _T>
void CParserJson<_T>::print_info_json_debug(const char *string_text, ...){

	
		char  text[500];
		CAPTURE_VARIABLE_ARGS(text, string_text);

		CLog::print(this->m_filesrc,this->m_line,CLog::LOG_INFO,text);
		
}

#define print_info_json print_info_json_debug

#ifndef  __VERBOSE_MESSAGE__
#undef print_info_json
#define print_info_json(s,...)
#endif

template <typename _T>
int CParserJson<_T>::json2cpp(const char * start_str,CParserVar *_root, int level, bool ignore_warnings) {

	char property_name[MAX_NAME_PROPERTY];
	char old_property_name[MAX_NAME_PROPERTY]={0};
	char val[512];
	int  size;
	bool isArray = false;
	char *str_end=NULL;

	char *current_ptr = (char *)start_str;
	CParserVar *c_property,*c_data;
	int bytes_readed;
	bool end = false;
	bool ok = false;
	//int column = 0;
	bool anonymous_array=false;
	bool more_group_properties=true;

	int type_value;

	bool another_element;

	// values to store...
	bool boolValue=false;
	float numberValue=0;


	current_ptr = IGNORE_BLANKS(current_ptr, this->m_line);
	
	if(*current_ptr == '[' && (level ==0)){ // detected anonymous array (only valid for first level)...
		anonymous_array	= true;
		current_ptr++;
		current_ptr = IGNORE_BLANKS(current_ptr, this->m_line);
		
	}
	
	while(more_group_properties){//(*current_ptr == INI_GROUP || *current_ptr == '[')){ // valid group...
	
		//current_ptr = IGNORE_BLANKS(current_ptr, this->m_line);
		
		if(*current_ptr == INI_GROUP){
	
			
			// create first property group and add it...
			if(level==0){ // create properties for first level only ...
				c_data = _root->newData();
				_root->add(c_data);
			}else{ // else root is c_data itself.
				c_data = _root;
			}
			
			setPropertiesParsedToFalse(c_data);

			current_ptr++;
			
			// the action starts here! looking for the properties and its values inside property group.
			while(!end) {
				
					// start working with ...
					// capture property inside...
					current_ptr = IGNORE_BLANKS(current_ptr, this->m_line);
					
					
					
					if(*current_ptr != END_GROUP) // void property return...
					{
						
						str_end = current_ptr;

						if(*current_ptr == '\'') // try to advance double quote
							str_end   = ADVANCE_TO_CHAR(current_ptr+1,'\'');
						else // try to single quote...
						if(*current_ptr == '\"')
							str_end   = ADVANCE_TO_CHAR(current_ptr+1,'\"');


						if(*current_ptr != *str_end){
							print_error_json(start_str,current_ptr,"Was expect a double/single quote. format example --> \"property\":\"value\"");
							return 0;
						}

						size = str_end - current_ptr-1;


							if(size > 0 && size < MAX_NAME_PROPERTY){

								memset(property_name,0,sizeof(property_name));

								strncpy(property_name,current_ptr+1,size);

								// get c property
								c_property = findProperty(c_data,property_name);

								if(c_property!= NULL)
									if(c_property->isParsed()){

										print_warning_json("%s was already parsed (duplicate?)", property_name);
									}

								// next.. get value...
								current_ptr = IGNORE_BLANKS(str_end+1, this->m_line);

								if(*current_ptr == ':') {// ok check value

									CParserVar *process_group=NULL;
									// check if group
									current_ptr = IGNORE_BLANKS(current_ptr+1, this->m_line);
									isArray = *current_ptr == '[';
									type_value = -1;

									another_element = false;



									if(isArray /*&& (c_property != NULL)*/){

										print_info_json("property \"%s\" detected as array ",property_name);
										current_ptr = IGNORE_BLANKS(current_ptr+1, this->m_line);
									}

									// capture values ...
									if(!isArray || (isArray && *current_ptr!= ']')){
									
										do{
											//str_begin = IGNORE_BLANKS(str_begin+1);
											ok = true;
											type_value = -1;

											if(*current_ptr == INI_GROUP) {// group detected...
												
												process_group = NULL;

												if(isArray) { // make add...
													if(c_property!=NULL){
														process_group = c_property->newData();
														c_property->add(process_group);
													}
												}
												else{
													print_info_json("property %s detected as group processing deep...",property_name);
													process_group = c_property;
												}

												// passing NULL if the record has been initialized (it doens't matter any c property in advence...
												if((bytes_readed = json2cpp(current_ptr, process_group,level+1,ignore_warnings))==0){
													return 0;
												}

												type_value = PROPERTY_GROUP_TYPE;

											}else{ // string, number, boolean, etc ...
												bytes_readed=0;
												if(*current_ptr == '\'' || *current_ptr == '\"') {// try string ...

													if(*current_ptr == '\'') // try to advance double quote
														str_end   = ADVANCE_TO_CHAR(current_ptr+1,'\'');
													else // try to single quote...
													if(*current_ptr == '\"')
														str_end   = ADVANCE_TO_CHAR(current_ptr+1,'\"');

													if(*current_ptr == *str_end){
														if(!isArray)
															print_info_json("property \"%s\" detected as string",property_name);
														bytes_readed = str_end-current_ptr+1;
														memset(val,0,sizeof(val));
														type_value = STRING_TYPE;
														if(bytes_readed > 2){
															strncpy(val,current_ptr+1,bytes_readed-2);
														}
													}
													else{
														print_info_json("Error reading property \"%s\" as string",property_name);
														return 0;
													}

												}else if(!strncmp(current_ptr,"true",4)){ // true detected ...
													if(!isArray)
														print_info_json("property \"%s\" detected as boolean",property_name);
														
													type_value = BOOL_TYPE;
													strcpy(val,"true");
													bytes_readed=4;
													boolValue = true;
												}else if(!strncmp(current_ptr,"false",5)) {// boolean detected
													if(!isArray)
														print_info_json("property \"%s\"detected as boolean",property_name);
														
													type_value = BOOL_TYPE;
													strcpy(val,"false");
													bytes_readed=5;
													boolValue = false;
												}else{ // must a number in ex or double format
													// try read until next comma
													str_end   = ADVANCE_TO_ONE_OF_COLLECTION_CHAR(current_ptr+1,(char *)end_char_standard_value,this->m_line);
													bytes_readed=str_end-current_ptr;
													if(*str_end !=0) {
														str_end--;
													}

													ok = false;

													if(bytes_readed>0){
														memset(val,0, sizeof(val));
														strncpy(val,current_ptr,bytes_readed);

														// and try to convert in to standard number ...
														int type_number = isNumber(val);
														
														//if(type_number != 0){
															if(type_number == STRING_IS_INT) { //RE2::FullMatch(val,"[-]?[0-9]*")) {// check for normal int...
																	if(!isArray)
																		print_info_json("property \"%s\" detected as int32",property_name);

																	numberValue=(float)strtol(val, NULL, 10);
																	type_value = NUMBER_TYPE;
																	ok=true;
															}else  if(type_number==STRING_IS_HEXA){//RE2::FullMatch(val,"0[xX][0-9a-fA-F]+")) {// check for hexadecimal...
																if(!isArray)
																	print_info_json("property \"%s\" detected as hex",property_name);

																numberValue=(float)strtol(val, NULL, 16);
																type_value = NUMBER_TYPE;
																ok=true;

															}else{ //if(type_number == STRING_IS_DOUBLE){//RE2::FullMatch(val, "[-]?[0-9]*\\.?[0-9]*")){ // check for double / float...
																char *p;
																numberValue=(float)strtod(val,&p);
																
																if(*p == '\0'){
																
																	if(!isArray)
																		print_info_json("property \"%s\" detected as float/double",property_name);
																	
																	ok=true;
																	type_value = NUMBER_TYPE;
																}
															}
															
															
															

														//}
									
													}
												}
											}

											if(!bytes_readed || !ok){
												print_error_json(start_str,current_ptr,"Impossible to parse value of property \"%s\"",property_name);
												return 0;
											}else{ // value ok
												/*if(first_type_value == -1)
													first_type_value = type_value;*/
												/*else if(first_type_value != type_value && !(bothAreTypeNumbers(first_type_value, type_value))){
													print_error_json(start_str,current_ptr,"array values in property \"%s\" have different values.",property_name);
													return 0;
												}*/
												

												if(isArray)
													type_value+=ARRAY_TYPE;

												// ok, check if the value parsed is the same as c_property (only saves particular elements (string/boolean/etc) but not property groups (it was saved already in recursion before)
												if( c_property != NULL && !c_property->isParsed()){

													//bool is_a_number = bothAreTypeNumbers(type_value,c_property->_m_iType);
													//float numberValue;

													//if(is_a_number){
													//	numberValue=((type_value&0xff) == FLOAT_TYPE)?floatValue:intValue;
													//}

													if(type_value == c_property->_m_iType /*||
															is_a_number*/
													   ){
													   
							

														/*if((type_value&0xff) == FLOAT_TYPE && (c_property->_m_iType&0xff) == INT32_TYPE)
															print_warning_json("\"%s\" have an array of floats but c-struct is int32. Possible lose of precision",property_name);
														*/
														switch(c_property->_m_iType) {
															default:
															case 	UNKNOWN_TYPE:
																	print_error("unknown type %i",type_value);
																	return 0;
																	break;
															case 	ARRAY_BOOL_TYPE:
															case 	BOOL_TYPE:
																		if(isArray){
																			print_info_json("added value boolean %i into array \"%s\"",boolValue,property_name);
																			(*(JS_ARRAY_BOOL_CAST c_property)).add(boolValue);
																		}else{
																			print_info_json("set value %i into variable \"%s\"",boolValue,property_name);
																			*(JS_BOOL_CAST c_property) = boolValue;
																		}
																	break;
															case 	ARRAY_NUMBER_TYPE:
															case 	NUMBER_TYPE:
																	if(isArray){
																		print_info_json("added value number %f into array \"%s\"",numberValue,property_name);
																		(*(JS_ARRAY_NUMBER_CAST c_property)).add(numberValue);
																	}else{
																		print_info_json("set value %f into variable \"%s\"",numberValue,property_name);
																		*(JS_NUMBER_CAST c_property) = numberValue;
																	}
																	break;
															case 	ARRAY_STRING_TYPE:
															case 	STRING_TYPE:
																	if(isArray){
																		print_info_json("added value string %s into array \"%s\"",val,property_name);
																		(*(JS_ARRAY_STRING_CAST c_property)).add(val);
																	}else{
																		print_info_json("set value %s into variable \"%s\"",val,property_name);
																		*(JS_STRING_CAST c_property) = val;
																	}
																	break;
															case 	ARRAY_PROPERTY_GROUP_TYPE:
															case 	PROPERTY_GROUP_TYPE:
																	// Nothing ... is well done!
																	break;

														}

														// set parsed element...
														if(!isArray)
															c_property->setParsed(true);

													}else{
														print_warning_json("variable \"%s\"not matches. JSon is %s and C struct is %s",property_name, CParserVar::idTypeToString(type_value), CParserVar::idTypeToString(c_property->_m_iType));
													}
												}else{

													/*if(!strcmp(property_name,"stage")){
														int kk=0;
														kk++;
													}*/
													if(c_data != NULL && strcmp(old_property_name, property_name))
														print_warning_json("Variable name \"%s\" NOT registered in c-struct",property_name);
												}

											}

											strcpy(old_property_name, property_name);

											current_ptr+=bytes_readed;

											current_ptr=IGNORE_BLANKS(current_ptr,this->m_line);
											another_element = false;
											// special case (another array element is needed)
											if(isArray) {
												if(*current_ptr == ',') {
													current_ptr = IGNORE_BLANKS(current_ptr+1,this->m_line);
													another_element = true;

												}
												else if(*current_ptr != ']'){
													print_error_json(start_str,current_ptr,"Was expect a ',' , ']' or '{' ");
													return 0;
												}
											}


										}while((isArray && *current_ptr != ']') || another_element);
									}

									// increment to next variable (set parsed as true)...
									if(isArray && *current_ptr == ']') {
											if(c_property)
												c_property->setParsed(true);
											current_ptr = IGNORE_BLANKS(current_ptr+1,this->m_line);
									}
								}
								else{
									print_error_json(start_str,current_ptr,"Error ':' expected");
									return 0;
								}
						}
						else{
							print_error_json(start_str,current_ptr,"invalid size property ");
							return 0;
						}

						end = (*current_ptr == '}');
						if(!end)
							if(*current_ptr != ','){
								print_error_json(start_str,current_ptr,"an \',\' was expected!");
								return 0;
							}

						// forward to next property
						current_ptr++;
					//an_element_need = (*current_ptr == ',');
					}else{
						print_error_json(start_str,current_ptr,"void property group!");
						current_ptr++;
					}
						

				}
				
				
		
		}
		else{
			print_error_json(start_str,current_ptr,"It doesn't possible check begin/end group {");
			return 0;
		}
		if(anonymous_array){
			current_ptr = IGNORE_BLANKS(current_ptr, this->m_line);
			if(*current_ptr==']')
				more_group_properties = false;
			else if(*current_ptr==','){
				end = false; // set for next property group ...
				current_ptr++;
			}else{
				more_group_properties = false;
				print_error_json(start_str,current_ptr,"Impossible to find ']' current caracter is %c",*current_ptr);
			}
			
		}else // breaks the main root.
			more_group_properties = false;
	}

	return current_ptr-start_str;
}
