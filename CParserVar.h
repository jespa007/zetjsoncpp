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


#pragma once

#include "CCommon.h"
#include "CString.h"
#include "CLog.h"

#define MAX_CONST_CHAR 50


#define _CONST_CHAR(s)\
getChr(s,0),\
getChr(s,1),\
getChr(s,2),\
getChr(s,3),\
getChr(s,4),\
getChr(s,5),\
getChr(s,6),\
getChr(s,7),\
getChr(s,8),\
getChr(s,9),\
getChr(s,10),\
getChr(s,11),\
getChr(s,12),\
getChr(s,13),\
getChr(s,14),\
getChr(s,15),\
getChr(s,16),\
getChr(s,17),\
getChr(s,18),\
getChr(s,19),\
getChr(s,20),\
getChr(s,21),\
getChr(s,22),\
getChr(s,23),\
getChr(s,24),\
getChr(s,25),\
getChr(s,26),\
getChr(s,27),\
getChr(s,28),\
getChr(s,29),\
getChr(s,30),\
getChr(s,31),\
getChr(s,32),\
getChr(s,33),\
getChr(s,34),\
getChr(s,35),\
getChr(s,36),\
getChr(s,37),\
getChr(s,38),\
getChr(s,39),\
getChr(s,40),\
getChr(s,41),\
getChr(s,42),\
getChr(s,43),\
getChr(s,44),\
getChr(s,45),\
getChr(s,46),\
getChr(s,47),\
getChr(s,48),\
getChr(s,49),\
getChr(s,50)

#define getChr(name, ii) ((MIN(ii,MAX_CONST_CHAR))<strlen(name)?name[ii]:0)


//#include "CVariable.h"
enum{
	UNKNOWN_TYPE = 0, // 0
	BOOL_TYPE, // 1
	NUMBER_TYPE,// 2
	STRING_TYPE, // 3
	PROPERTY_GROUP_TYPE,
	ARRAY_TYPE=0x100,
	ARRAY_BOOL_TYPE=BOOL_TYPE+ARRAY_TYPE, // 6
	ARRAY_NUMBER_TYPE=NUMBER_TYPE+ARRAY_TYPE, // 7
	ARRAY_STRING_TYPE=STRING_TYPE+ARRAY_TYPE, // 9
	ARRAY_PROPERTY_GROUP_TYPE=PROPERTY_GROUP_TYPE+ARRAY_TYPE
};

enum{
	PROPERTY_STR_MINIMIZED=0x1 <<0
};

#define N_ELEMENTS_JSON_ARRAY_PRINT	10


#define JS_STRING_CAST 		(CParserVarString<> *)
#define JS_ARRAY_STRING_CAST 	(CParserVarArrayString<> *)
#define JS_BOOL_CAST 		(CParserVarBool<> *)
#define JS_FLOAT_CAST 		(CParserVarNumber<> *)



class CParserVar {
protected:
	std::string result_json;
	std::string str_value;
	bool m_isParsed;

public:

	static const char *idTypeToString(int index) {
		switch(index){
			default:
			case UNKNOWN_TYPE:
				break;
			case BOOL_TYPE: return "BOOL_TYPE";
			case NUMBER_TYPE: return "INT32_NUMBER";
			case STRING_TYPE: return "STRING TYPE";
			case PROPERTY_GROUP_TYPE: return "PROPERTY_GROUP_TYPE";

			case ARRAY_BOOL_TYPE: return "ARRAY BOOL TYPE";
			case ARRAY_NUMBER_TYPE: return "ARRAY NUMBER TYPE";
			case ARRAY_STRING_TYPE: return "ARRAY STRING TYPE";
			case ARRAY_PROPERTY_GROUP_TYPE: return "ARRAY PROPERTY GROUP TYPE";
		}

		return "UNKNOWN";
	}

    static char const STR_EMPTY[];
	int _m_iType;
	int size_data;
	string  _m_pvariableName;
	CParserVar *p_ini_data;
	void 	     *p_data; // can be int, bool, vector, prop_grp, etc ...
	CParserVar *p_end_data;
	//_T_NAME name;

	CParserVar() {
		this->p_end_data = NULL;
		this->p_data = NULL;
		this->size_data = 0;
		this->p_ini_data = NULL;
		this->_m_iType = UNKNOWN_TYPE;
		this->m_isParsed = false;
	}

	virtual string & cpp2json() {
		result_json ="//void\n{}";
		return result_json;
	}

	virtual CParserVar * newData() {
		return NULL;
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		this->str_value = "??"; 
		return str_value;
	}

	virtual void add(CParserVar * s){}

	virtual ~CParserVar() {

	}

	void setParsed(bool parsed){
		m_isParsed=parsed;
	}

	bool isParsed() const{
		return m_isParsed;
	}
};

template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarNamed : public CParserVar{
public:
	//----------------------------------------------------------------
	// DON'T js_ini AND NOT DECLARE ANY CParserVar UNDER IT !!!!

	CParserVar 	js_ini;

	//----------------------------------------------------------------

	CParserVarNamed() {

		std::vector<char> vec={chr1, chr2,_T_NAME...};
		string s_aux(vec.begin(), vec.end());

		char buffer[512]={0};

		strcpy(buffer, s_aux.c_str());

		if(strlen(buffer) == 0)
		{
			print_error("Parser variable with name! Advice: put a breakpoint here to known source of anonymous template!!!");
		}

		//strcpy(this->_m_pvariableName,  _T_NAME);
		this->_m_pvariableName = buffer;
		this->size_data = sizeof(CParserVarNamed);
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)
	{
		this->str_value ="??";
		return this->str_value;
	}

	virtual ~CParserVarNamed(){}
};


template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarNumber: public CParserVarNamed<chr1,chr2, _T_NAME ...>{

	float number;
	bool m_forceInteger;
	void init() {

		number = 0;
		this->_m_iType = NUMBER_TYPE;
		this->size_data = sizeof(CParserVarNumber<chr1, chr2,_T_NAME...>);
		this->p_data = &number;
		m_forceInteger=false;
		if(this->_m_pvariableName == "") {

			print_error("parse variable is empty, it's impossible to load any empty variable!");
		}
	}

public:

	CParserVarNumber() {
		init();
	}

	explicit CParserVarNumber(float i) {
		init();
		number = i;


	}

	CParserVarNumber & operator =(float b) {

		number = b;
		return *this;
	}

	void setForceInteger(bool force){
			m_forceInteger = force;
	}

	CParserVarNumber & operator =(int i) {

		number = (float)i;
		return *this;
	}


	operator Sint32 () const {
		return (Sint32)(*((float *)this->p_data));
	}

	CParserVarNumber & operator =(const string & intStr) {

		number = fromString<float>(intStr);
		return *this;
	}

	operator float () {

		return number;
	}

	virtual string & getStrValue(int ident, Uint32 flags=0) {

		if(m_forceInteger)
			this->str_value =""+intToString(number);
		else
			this->str_value =""+floatToString(number);
		return this->str_value;
	}

	//virtual ~CParserVarNumber(){}
};

template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarBool: public CParserVarNamed<chr1,chr2,_T_NAME ...> {
	bool b_value;

	void init() {

		this->b_value = false;
		this->_m_iType = BOOL_TYPE;
		this->size_data = sizeof(CParserVarBool<chr1, chr2,_T_NAME...>);
		this->p_data = &b_value;

		if(this->_m_pvariableName == "")
		{
			print_error("parse variable is empty, it's impossible to load any empty variable!");
		}
	}

public:
	//_T_NAME name;
	explicit CParserVarBool(bool b=false) {
		init();
		*((bool *)this->p_data) = b;

	}

	operator bool () {
		return *((bool *)this->p_data);
	}

	bool operator ==(bool b) {
		return *((bool *)this->p_data) == b;
	}

	bool operator !=(bool b) {
		return *((bool *)this->p_data) != b;
	}

	CParserVarBool & operator =(bool b) {

		*((bool *)this->p_data) = b;
		return *this;
	}

	CParserVarBool & operator =(const string & str) {

		if(toLower(str) == "true") *((bool *)this->p_data) = true;
		else if(toLower(str) == "false") *((bool *)this->p_data) = false;
		else print_error("undefined value to assign bool value");
		return *this;
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {

		string result_bool=(*((bool *)this->p_data)==false?"false":"true");
		this->str_value =""+result_bool;
		return this->str_value;
	}

//	virtual ~CParserVarBool(){}

};

template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarString: public CParserVarNamed<chr1,chr2, _T_NAME... >{
protected:
	virtual void init() {


	 	this->_m_iType = STRING_TYPE;
	 	this->size_data = sizeof(CParserVarString<chr1, chr2,_T_NAME...>);
		this->p_data = &this->s_value;

		if(this->_m_pvariableName == "")
		{
			print_error("parse variable is empty, it's impossible to load any empty variable!");
		}

	}
	
public:
  string s_value;

	//_T_NAME name;
	CParserVarString() {
	init();
	}

  	explicit CParserVarString(string & s) {
	  init();
		*((string *)this->p_data) = s;
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		this->str_value ="\""+*((string *)this->p_data)+"\"";
		return this->str_value;
	}

	CParserVarString & operator = (const string & s) {

		this->s_value = s;
		return *this;
	}
	
	bool operator == (const string & s) const{
		return this->s_value == s;

	}

	bool operator == (const char * s) const{
		return !strcmp(this->s_value.c_str(),s);

	}

	operator string () const{
		 return this->s_value;
	}

	operator const char *() {
		 return (const char *)this->s_value.c_str();
	}

	CParserVarString & operator = (const char * s) {

		this->s_value = s;
		return *this;
	}

	operator string() {
		return this->s_value;

	}

	//virtual ~CParserVarString(){}
};



template<typename _T_DATA, char chr1='a', char chr2='b', char... _T_NAME>
class CParserVarPropertyGroup: public CParserVarNamed<chr1, chr2,_T_NAME...>,public _T_DATA{
public:
	//----------------------------------------------------------------
	// DON'T MOVE js_end ON THIS CLASS !!!!

	CParserVar 	js_end;

	//----------------------------------------------------------------
	CParserVarPropertyGroup(Uint32 numParam=0,...) {
		// PRE: All args must be string. The program can parse the apropiate type var
		// with its emmbedded type.

		this->_m_iType = PROPERTY_GROUP_TYPE;
	 	this->size_data = sizeof(CParserVarPropertyGroup<_T_DATA,chr1,chr2, _T_NAME...>);
		
		CParserVar *ptr = ((CParserVar *)&this->js_ini + 1);
		this->p_data = ptr;
		this->p_end_data = ((CParserVar *)&js_end - 1);

		//-------
		// Iterate on all its elements ...
		char *aux_p = (char *)this->p_data;
		char *end_p = (char *)this->p_end_data;

		va_list arg_list;
		// inicialize all vars struct in order of pass parameters ...
		va_start( arg_list, numParam );
		for( unsigned i = 0; i < numParam && (aux_p < end_p); i++ ) {
			const char * variable = va_arg( arg_list, const char *);
			CParserVar * p_sv = (CParserVar *)aux_p;

			switch(p_sv->_m_iType)
			{
			case STRING_TYPE:
				//print_info("string ...!\n\n");
				*(JS_STRING_CAST p_sv) = variable;//->assign();
				break;
			}

			aux_p += p_sv->size_data;
		}
		va_end( arg_list );
		//---------

	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		this->str_value ="??";
		return this->str_value;
	}

	//std::string result_json;
	virtual string & cpp2json(Uint32 flags=0) {
		bool not_minimized = ((flags & PROPERTY_STR_MINIMIZED) == 0);
		this->result_json = "";
		cpp2jsonRecursive(this, this->result_json, 0, flags);

		if(not_minimized)
			this->result_json += "\n";

		return this->result_json;

	}

	void cpp2jsonRecursive(CParserVar * c_data, std::string & result_s, int level, Uint32 flags = 0) {

		bool not_minimized = ((flags & PROPERTY_STR_MINIMIZED) == 0);

		if(not_minimized)
		for(int i = 0; i < level; i++)
			result_s = result_s + "\t";
		result_s = result_s + "{";

		if(not_minimized)
			result_s += "\n";
	
		char *aux_p = (char *)c_data->p_data;
		char *end_p = (char *)c_data->p_end_data;

		for(;aux_p < end_p; ) {
			// if(chkType()) // --> get and parse ...
			CParserVar * p_sv = (CParserVar *)aux_p;
			if(p_sv != NULL){
				if(not_minimized)
				for(int i = 0; i <= level; i++)
					result_s = result_s + "\t";


				result_s = result_s + "\""+p_sv->_m_pvariableName+"\":";

				switch(p_sv->_m_iType)// == )
				{
				case BOOL_TYPE:

				case NUMBER_TYPE:
				case STRING_TYPE:
					result_s = result_s + p_sv->getStrValue(level,flags);
					break;

				case PROPERTY_GROUP_TYPE:
					//printf("Accessing property groupr %s ...\n", p_sv->_m_pvariableName);
					if(not_minimized)
						result_s += "\n";

					cpp2jsonRecursive(p_sv, result_s, level+1, flags);
					break;
				// arrays
				case ARRAY_BOOL_TYPE:

				case ARRAY_STRING_TYPE:
				case ARRAY_PROPERTY_GROUP_TYPE:

					if(not_minimized){
						result_s += "\n";

						for(int i = 0; i <= level; i++)
							result_s = result_s + "\t";
					}

					result_s = result_s + "[";

					if(not_minimized)
						result_s += "\n";

					if(p_sv->_m_iType != ARRAY_PROPERTY_GROUP_TYPE)
						result_s  = result_s  + p_sv->getStrValue(level, flags);
					else
					{
					//result_s = result_s + "\""+p_sv->name+"\": [\n";

						//first_element_array=true;
						vector <CParserVar *>  *vec = (vector<CParserVar *> *)(p_sv->p_data);

						for(unsigned k = 0; k < vec->size(); k++)
						{
							if(k > 0)
								result_s = result_s + ",";

							if(not_minimized)
								result_s += "\n";


							cpp2jsonRecursive(vec->at(k), result_s, level+2, flags);
						}
					}

					if(not_minimized){
						result_s += "\n";

						for(int i = 0; i <= level; i++)
							result_s = result_s + "\t";
					}

					result_s = result_s + "]";


					break;
				}
			}
			aux_p += p_sv->size_data;

			if(aux_p < end_p)
				result_s = result_s + ",";

			if(not_minimized)
				result_s += "\n";

		}

		if(not_minimized)
			for(int i = 0; i < level; i++)
				result_s = result_s + "\t";

		result_s = result_s + "}";	}	

	//virtual ~CParserVarPropertyGroup(){};
};


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//   ARRAYS
//

template<typename _T_DATA, char a='a', char b='b'>
class CDinamicVector{
protected:
	vector<_T_DATA> vec_data;
public:

	CDinamicVector(){}

	_T_DATA & 	operator[](int i) {
		return vec_data.at(i);
	}

	_T_DATA const& 	at(unsigned int i) {

		return vec_data.at(i);
	}

	void			 	push_back(const _T_DATA & tt) {
		vec_data.push_back(tt);
	}

	void			 	clear() {
		vec_data.clear();
	}

	void 	erase(unsigned int i) {
		if(i < vec_data.size()) {
			vec_data.erase(vec_data.begin()+i);
		}
	}

	unsigned 			size() {
		return vec_data.size();
	}

	vector<_T_DATA> * getStdVector() {
		return &vec_data;
	}
};

// ARRAY BOOL
template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarArrayBool: public CParserVarNamed<chr1,chr2,_T_NAME...>, public CDinamicVector<bool>{
public:
	//_T_NAME name;
	CParserVarArrayBool(){
		this->_m_iType = ARRAY_BOOL_TYPE;
		this->size = sizeof(CParserVarArrayBool<chr1,chr2, _T_NAME...>);
		this->p_data = &this->vec_data;////new vector<string>;
	}

	void add(bool s) {
		((vector<bool> *)this->p_data)->push_back(s);
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		//this->str_value ="";
		vector<bool> * v = (vector<bool> *)this->p_data;
		string m_sfValue;
		for(int k = 0; k <= (ident+1); k++)
				this->str_value = this->str_value + "\t";

		for(int j = 0; j < v->size(); j++) {

			if(j>0)
				this->str_value=this->str_value+",";

			m_sfValue = "False";
			if(v->at(j)==true)
				m_sfValue = "True";


			this->str_value=this->str_value+""+m_sfValue+" ";

			if(j!=0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT)==0)) {
				for(int k = 0; k <= (ident+1); k++)
					this->str_value = this->str_value + "\t";
				this->str_value=this->str_value+"\n";
			}

		}
		return this->str_value;
	}

	//virtual ~CParserVarArrayBool(){}

};

// ARRAY NUMBER
template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarArrayNumber: public CParserVarNamed<chr1,chr2,_T_NAME...>, public CDinamicVector<float>{


public:
	//_T_NAME name;
	CParserVarArrayNumber(){

		this->_m_iType = ARRAY_NUMBER_TYPE;
		this->size_data = sizeof(CParserVarArrayNumber<chr1,chr2, _T_NAME...>);
		this->p_data = &this->vec_data;////new vector<string>;
	}

	void add(float s) {
		((vector<float> *)this->p_data)->push_back(s);
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		//this->str_value ="";
		bool not_minimized = ((flags & PROPERTY_STR_MINIMIZED) == 0);
		vector<float> * v = (vector<float> *)this->p_data;
		this->str_value = "";
		string m_sfValue;
		for(int k = 0; k <= (ident+1); k++)
				this->str_value = this->str_value + "\t";

		for(unsigned j = 0; j < v->size(); j++) {

			if(j>0)
				this->str_value=this->str_value+",";
			m_sfValue = floatToString(v->at(j));

			this->str_value=this->str_value+""+m_sfValue+" ";

			if(not_minimized){
				if(j!=0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT)==0)) {
					for(int k = 0; k <= (ident+1); k++)
						this->str_value = this->str_value + "\t";
					this->str_value+="\n";
				}
			}

		}
		return this->str_value;
	}

	//virtual ~CParserVarArrayNumber(){}
	virtual ~CParserVarArrayNumber(){
	}
};

// ARRAY STRING
template<char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarArrayString: public CParserVarNamed<chr1,chr2,_T_NAME...>, public CDinamicVector<std::string>{
public:
	//_T_NAME name;
	CParserVarArrayString(){
		this->_m_iType = ARRAY_STRING_TYPE;
		this->size_data = sizeof(CParserVarArrayString<chr1,chr2, _T_NAME...>);
		this->p_data = &this->vec_data;////new vector<string>;
	}

	void add(string const & s) {
		((vector<string> *)this->p_data)->push_back(s);
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		//this->str_value ="";
		vector<string> * v = (vector<string> *)this->p_data;
		this->str_value = "";

		for(int k = 0; k <= (ident+1); k++)
				this->str_value = this->str_value + "\t";

		for(int j = 0; j < v->size(); j++) {

			if(j>0)
				this->str_value=this->str_value+",";
			
			this->str_value=this->str_value+"\""+v->at(j)+"\" ";

			if(j!=0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT)==0))
			{
				for(int k = 0; k <= (ident+1); k++)
					this->str_value = this->str_value + "\t";
				this->str_value=this->str_value+"\n";
			}

		}
		return this->str_value;
	}

	//virtual ~CParserVarArrayString(){}

};


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


template<typename _T_DATA, char chr1='a', char chr2='b',char... _T_NAME>
class CParserVarArrayPropertyGroup: public CParserVarNamed<chr1,chr2,_T_NAME...>, public CDinamicVector<CParserVarPropertyGroup<_T_DATA> * >{

public:

	CParserVarArrayPropertyGroup(){
		this->_m_iType = ARRAY_PROPERTY_GROUP_TYPE;
		this->size_data = sizeof(CParserVarArrayPropertyGroup<_T_DATA, chr1,chr2,_T_NAME...>);
		this->p_data = &this->vec_data;

		if(this->_m_pvariableName == "")
		{
			print_error("parse variable is empty, it's impossible to load any empty variable!");
		}
	}

	virtual CParserVar *newData() {
		return new CParserVarPropertyGroup<_T_DATA>;
	}

	virtual string & getStrValue(int ident, Uint32 flags=0)  {
		this->str_value ="??";
		return this->str_value;
	}

	virtual void add(CParserVar * s)	{
		CParserVarPropertyGroup< _T_DATA> *tt = (CParserVarPropertyGroup< _T_DATA> *)s;
		this->push_back(tt);
	}

	//std::string result_json;
	virtual string & cpp2json(Uint32 flags=0) {
		bool not_minimized = ((flags & PROPERTY_STR_MINIMIZED) == 0);
		this->result_json = "[";
		for(int i = 0; i < this->size(); i++){
			if(i>0){
				this->result_json += ",";
			}
			this->at(i)->cpp2jsonRecursive(this->at(i), this->result_json, 0, flags);
		}

		this->result_json += "]";
		if(not_minimized)
			this->result_json += "\n";

		return this->result_json;

	}

	virtual ~CParserVarArrayPropertyGroup() {

		for(unsigned i = 0; i < this->vec_data.size(); i++) {
			delete this->vec_data[i];
			this->vec_data[i] = NULL;
		}

		this->vec_data.clear();
	}
};

