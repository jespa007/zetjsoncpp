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

	//	tJsonWarningCallback json_warning_callback=NULL;
		//tJsonErrorCallback json_error_callback=NULL;
	template<typename _T>
	bool ZetJsonCpp<_T>::isSingleComment(char *str){

		if((*str!=0) && *str=='/'){
			return *(str+1)=='/';
		}
		return false;
	}

	template<typename _T>
	bool ZetJsonCpp<_T>::isStartComment(char *str){

		if((*str!=0) && *str=='/'){
			return *(str+1)=='*';
		}
		return false;
	}

	template<typename _T>
	bool ZetJsonCpp<_T>::isEndComment(char *str){

		if((*str!=0) && *str=='*'){
			return *(str+1)=='/';
		}
		return false;
	}

	template<typename _T>
	char *ZetJsonCpp<_T>::advanceToChar(char *str,char c) {
		char *aux_p = str;
		// make compatible windows format (\r)...
		while(*aux_p!='\n' && *aux_p!='\r' && *aux_p!=0 && (*aux_p !=(c) )) aux_p++;

		if(*aux_p=='\r')
			aux_p++;

		return aux_p;
	}

	template<typename _T>
	char *ZetJsonCpp<_T>::advanceToEndComment(char *aux_p, int &line){

		if(isStartComment(aux_p)){
			aux_p+=2; //advance first
			while(!isEndComment(aux_p) && *aux_p != 0){
				aux_p = advanceToChar(aux_p,'*');
				if(*aux_p == '\n') aux_p++; // make compatible windows format...
				if(*aux_p == '\r') aux_p++;
				if(*(aux_p+1) != '/') aux_p++; // not end comment ... advance ...
			}
		}

		return aux_p;
	}

	template<typename _T>
	char *ZetJsonCpp<_T>::ignoreBlanks(char *str, int &line) {
		char *aux_p = str;
		bool end = false;
		while(!end){
			end = true;
			while(*aux_p!=0 && ((*aux_p==' ')  || (*aux_p=='\t'))) aux_p++;

			if(isSingleComment(aux_p)) {// ignore line
				aux_p = advanceToChar(aux_p,'\n');
			}
			else if(isStartComment(aux_p)){
				// ignore until get the end of the comment...
				aux_p = advanceToEndComment(aux_p, line);

				if(isEndComment(aux_p)){
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

	template<typename _T>
	char *ZetJsonCpp<_T>::advanceToOneOfCollectionOfChar(char *str,char *end_char_standard_value, int &line) {
		char *aux_p = str;
		char *chk_char;
		while(*aux_p!=0){
			chk_char = end_char_standard_value;

			// comment blocks also is returned (these lines must be ignored)
			if(isStartComment(aux_p)) {
				aux_p = advanceToEndComment(aux_p, line);
				if(isEndComment(aux_p))
					aux_p+=2;
			}

			if(isSingleComment(aux_p)) {
				aux_p = advanceToChar(aux_p,'\n');
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

	template <typename _T>
	ParserVar *ZetJsonCpp<_T>::findProperty(ParserVar * c_data, char *variable_name) {

		// no data no search...
		if (c_data == NULL) return NULL;

		char *aux_p = (char *)c_data->p_data;
		char *end_p = (char *)c_data->p_end_data;

		// Main loop iteration to whole C struct
		for (; aux_p < end_p; ) {

			ParserVar * p_sv = (ParserVar *)aux_p;
			if (p_sv->variable_name == variable_name)
				return p_sv;

			aux_p += p_sv->size_data;
		}

		return NULL;
	}

	template <typename _T>
	void ZetJsonCpp<_T>::setPropertiesParsedToFalse(ParserVar * c_data) {
		// no data no search...
		if (c_data == NULL)
			return;

		char *aux_p = (char *)c_data->p_data;
		char *end_p = (char *)c_data->p_end_data;

		// Main loop iteration to whole C struct
		for (; aux_p < end_p; ) {

			ParserVar * p_sv = (ParserVar *)aux_p;
			p_sv->setParsed(false);

			aux_p += p_sv->size_data;
		}

	}

	template<typename _T>
	int ZetJsonCpp<_T>::eval(const char * start_str, ParserVar *_root, int level) {

		char variable_name[MAX_NAME_PROPERTY];
		char old_variable_name[MAX_NAME_PROPERTY] = { 0 };
		char val[4096];
		int  size;
		bool is_array = false;
		char *str_end = NULL;

		char *current_ptr = (char *)start_str;
		ParserVar *c_property, *c_data;
		int bytes_readed;
		bool end = false;
		bool ok = false;
		//int column = 0;
		bool anonymous_array = false;
		bool more_group_properties = true;

		int type_value;

		bool another_element;

		// values to store...
		bool bool_value = false;
		float number_value = 0;

		if (IS_EMPTY(start_str)){
			throw_error(this->filename, -1,NULL, NULL, "Empty string");
		}


		current_ptr = ignoreBlanks(current_ptr, this->line);

		if (*current_ptr == '[' && (level == 0)) { // detected anonymous array (only valid for first level)...
			anonymous_array = true;
			current_ptr++;
			current_ptr = ignoreBlanks(current_ptr, this->line);

		}

		while (more_group_properties) {//(*current_ptr == INI_GROUP || *current_ptr == '[')){ // valid group...

			current_ptr = ignoreBlanks(current_ptr, this->line);

			if (*current_ptr == INI_GROUP) {


				// create first property group and add it...
				if (level == 0) { // create properties for first level only ...
					c_data = _root->newData();
					_root->add(c_data);
				}
				else { // else root is c_data itself.
					c_data = _root;
				}

				setPropertiesParsedToFalse(c_data);

				current_ptr++;

				// the action starts here! looking for the properties and its values inside property group.
				while (!end) {

					// start working with ...
					// capture property inside...
					current_ptr = ignoreBlanks(current_ptr, this->line);

					if (*current_ptr != END_GROUP) // void property return...
					{

						str_end = current_ptr;

						if (*current_ptr == '\'') // try to advance double quote
							str_end = advanceToChar(current_ptr + 1, '\'');
						else // try to single quote...
							if (*current_ptr == '\"')
								str_end = advanceToChar(current_ptr + 1, '\"');


						if (*current_ptr != *str_end) {
							throw_error(this->filename, this->line,start_str, current_ptr, "Was expect a double/single quote. format example --> \"property\":\"value\"");
						}

						size = str_end - current_ptr - 1;


						if (size > 0 && size < MAX_NAME_PROPERTY) {

							memset(variable_name, 0, sizeof(variable_name));

							strncpy(variable_name, current_ptr + 1, size);

							// get c property
							c_property = findProperty(c_data, variable_name);

							if (c_property != NULL)
								if (c_property->isParsed()) {

									throw_warning(this->filename, this->line,"%s was already parsed (duplicate?)", variable_name);
								}

							// next.. get value...
							current_ptr = ignoreBlanks(str_end + 1, this->line);

							if (*current_ptr == ':') {// ok check value

								ParserVar *process_group = NULL;
								// check if group
								current_ptr = ignoreBlanks(current_ptr + 1, this->line);
								is_array = *current_ptr == '[';
								type_value = -1;

								another_element = false;

								if (is_array /*&& (c_property != NULL)*/) {

									print_info_json("property \"%s\" detected as array ", variable_name);
									current_ptr = ignoreBlanks(current_ptr + 1, this->line);
								}

								// capture values ...
								if (!is_array || (is_array && *current_ptr != ']')) {

									do {

										ok = true;
										type_value = -1;

										if (*current_ptr == INI_GROUP) {// group detected...

											process_group = NULL;

											if (is_array) { // make add...
												if (c_property != NULL) {
													process_group = c_property->newData();
													c_property->add(process_group);
												}
											}
											else {
												print_info_json("property %s detected as group processing deep...", variable_name);
												process_group = c_property;
											}

											// passing NULL if the record has been initialized (it doens't matter any c property in advence...
											if ((bytes_readed = eval(current_ptr, process_group, level + 1)) == 0) {
												return 0;
											}

											type_value = ParserVar::TYPE_OBJECT;

										}
										else { // string, number, boolean, etc ...
											bytes_readed = 0;
											if (*current_ptr == '\'' || *current_ptr == '\"') {// try string ...

												if (*current_ptr == '\'') // try to advance double quote
													str_end = advanceToChar(current_ptr + 1, '\'');
												else // try to single quote...
													if (*current_ptr == '\"')
														str_end = advanceToChar(current_ptr + 1, '\"');

												if (*current_ptr == *str_end) {
													if (!is_array) {
														print_info_json("property \"%s\" detected as string", variable_name);
													}
													bytes_readed = str_end - current_ptr + 1;
													memset(val, 0, sizeof(val));
													type_value = ParserVar::TYPE_STRING;
													if (bytes_readed > 2) {
														unsigned copy_bytes = bytes_readed - 2;
														if ((unsigned)bytes_readed >= sizeof(val)) {
															fprintf(stderr,"Reached max size value \"%s\" (max:%i)\n", variable_name, (int)(sizeof(val)));
															copy_bytes = sizeof(val) - 1;
														}
														strncpy(val, current_ptr + 1, copy_bytes);
													}
												}
												else {
													throw_error(
															this->filename
															, this->line
															,NULL
															,NULL
															,"Error reading property \"%s\" as string", variable_name);
												}

											}
											else if (!strncmp(current_ptr, "true", 4)) { // true detected ...
												if (!is_array) {
													print_info_json("property \"%s\" detected as boolean", variable_name);
												}

												type_value = ParserVar::TYPE_BOOLEAN;
												strcpy(val, "true");
												bytes_readed = 4;
												bool_value = true;
											}
											else if (!strncmp(current_ptr, "false", 5)) {// boolean detected
												if (!is_array) {
													print_info_json("property \"%s\"detected as boolean", variable_name);
												}

												type_value = ParserVar::TYPE_BOOLEAN;
												strcpy(val, "false");
												bytes_readed = 5;
												bool_value = false;
											}
											else { // must a number in ex or double format
												// try read until next comma
												str_end = advanceToOneOfCollectionOfChar(current_ptr + 1, (char *)end_char_standard_value, this->line);
												bytes_readed = str_end - current_ptr;
												if (*str_end != 0) {
													str_end--;
												}

												ok = false;

												if (bytes_readed > 0) {
													memset(val, 0, sizeof(val));
													strncpy(val, current_ptr, bytes_readed);

													// and try to convert in to standard number ...
													zj_strutils::STR_NUMBER_TYPE type_number = zj_strutils::is_number(val);

													//if(type_number != 0){
													if (type_number == zj_strutils::STR_NUMBER_TYPE_INT) { //RE2::FullMatch(val,"[-]?[0-9]*")) {// check for normal int...
														if (!is_array) {
															print_info_json("property \"%s\" detected as int32", variable_name);
														}

														number_value = (float)strtol(val, NULL, 10);
														type_value = ParserVar::TYPE_NUMBER;
														ok = true;
													}
													else  if (type_number == zj_strutils::STR_NUMBER_TYPE_HEXA) {//RE2::FullMatch(val,"0[xX][0-9a-fA-F]+")) {// check for hexadecimal...
														if (!is_array) {
															print_info_json("property \"%s\" detected as hex", variable_name);
														}

														number_value = (float)strtol(val, NULL, 16);
														type_value = ParserVar::TYPE_NUMBER;
														ok = true;

													}
													else { //if(type_number == STRING_IS_DOUBLE){//RE2::FullMatch(val, "[-]?[0-9]*\\.?[0-9]*")){ // check for double / float...
														char *p;
														number_value = (float)strtod(val, &p);

														if (*p == '\0') {

															if (!is_array) {
																print_info_json("property \"%s\" detected as float/double", variable_name);
															}

															ok = true;
															type_value = ParserVar::TYPE_NUMBER;
														}
													}
												}
											}
										}

										if (!bytes_readed || !ok) {
											throw_error(this->filename, this->line,start_str, current_ptr, "Impossible to parse value of property \"%s\"", variable_name);
											return 0;
										}
										else { // value ok
											if (is_array)
												type_value += ParserVar::TYPE_ARRAY;

											// ok, check if the value parsed is the same as c_property (only saves particular elements (string/boolean/etc) but not property groups (it was saved already in recursion before)
											if (c_property != NULL && !c_property->isParsed()) {

												if (type_value == c_property->type /*||
														is_a_number*/
													) {


													switch (c_property->type) {
													default:
													case 	ParserVar::TYPE_UNKNOWN:
														fprintf(stderr,"unknown type %i", type_value);
														return 0;
														break;
													case 	ParserVar::TYPE_ARRAY_BOOLEAN:
													case 	ParserVar::TYPE_BOOLEAN:
														if (is_array) {
															print_info_json("added value boolean %i into array \"%s\"", bool_value, variable_name);
															(*(ZJ_ARRAY_BOOLEAN_CAST c_property)).add(bool_value);
														}
														else {
															print_info_json("set value %i into variable \"%s\"", bool_value, variable_name);
															*(ZJ_BOOLEAN_CAST c_property) = bool_value;
														}
														break;
													case 	ParserVar::TYPE_ARRAY_NUMBER:
													case 	ParserVar::TYPE_NUMBER:
														if (is_array) {
															print_info_json("added value number %f into array \"%s\"", number_value, variable_name);
															(*(ZJ_ARRAY_NUMBER_CAST c_property)).add(number_value);
														}
														else {
															print_info_json("set value %f into variable \"%s\"", number_value, variable_name);
															*(ZJ_NUMBER_CAST c_property) = number_value;
														}
														break;
													case 	ParserVar::TYPE_ARRAY_STRING:
													case 	ParserVar::TYPE_STRING:
														if (is_array) {
															print_info_json("added value string %s into array \"%s\"", val, variable_name);
															(*(ZJ_ARRAY_STRING_CAST c_property)).add(val);
														}
														else {
															print_info_json("set value %s into variable \"%s\"", val, variable_name);
															*(ZJ_STRING_CAST c_property) = val;
														}
														break;
													case 	ParserVar::TYPE_OBJECT_ARRAY:
													case 	ParserVar::TYPE_OBJECT:
														// Nothing ... is well done!
														break;
													}

													// set parsed element...
													if (!is_array)
														c_property->setParsed(true);

												}
												else {
													throw_warning(this->filename, this->line,"variable \"%s\"not matches. JSon is %s and C struct is %s", variable_name, ParserVar::idTypeToString(type_value), ParserVar::idTypeToString(c_property->type));
												}
											}
											/* do not throw if there's json variables not registered in struct...
											else {

												if (c_data != NULL && strcmp(old_variable_name, variable_name))
													throw_warning(this->filename, this->line,"Variable name \"%s\" NOT registered in c-struct", variable_name);
											}*/
										}

										strcpy(old_variable_name, variable_name);

										current_ptr += bytes_readed;

										current_ptr = ignoreBlanks(current_ptr, this->line);
										another_element = false;
										// special case (another array element is needed)
										if (is_array) {
											if (*current_ptr == ',') {
												current_ptr = ignoreBlanks(current_ptr + 1, this->line);
												another_element = true;

											}
											else if (*current_ptr != ']') {
												throw_error(this->filename, this->line,start_str, current_ptr, "Was expect a ',' , ']' or '{' ");

											}
										}

									} while ((is_array && *current_ptr != ']') || another_element);
								}

								// increment to next variable (set parsed as true)...
								if (is_array && *current_ptr == ']') {
									if (c_property)
										c_property->setParsed(true);
									current_ptr = ignoreBlanks(current_ptr + 1, this->line);
								}
							}
							else {
								throw_error(this->filename, this->line,start_str, current_ptr, "Error ':' expected");

							}
						}
						else {
							throw_error(this->filename, this->line,start_str, current_ptr, "invalid size property (%i)", size);

						}

						end = (*current_ptr == '}');
						if (!end)
							if (*current_ptr != ',') {
								throw_error(this->filename, this->line,start_str, current_ptr, "an \',\' was expected!");

							}

						// forward to next property
						current_ptr++;
						//an_element_need = (*current_ptr == ',');
					}
					else { // void property group
						//throw_warning(start_str,current_ptr,"void property group!");
						current_ptr++;
						return current_ptr - start_str; // return..
					}
				}
			}
			else {
				throw_error(this->filename, this->line,start_str, current_ptr, "It doesn't possible check begin/end group {");

			}
			if (anonymous_array) {
				current_ptr = ignoreBlanks(current_ptr, this->line);
				if (*current_ptr == ']')
					more_group_properties = false;
				else if (*current_ptr == ',') {
					end = false; // set for next property group ...
					current_ptr++;
				}
				else {
					more_group_properties = false;
					throw_error(this->filename, this->line,start_str, current_ptr, "Impossible to find ']' current caracter is %c", *current_ptr);
				}

			}
			else // breaks the main root.
				more_group_properties = false;
		}
		return current_ptr - start_str;
	}
}

