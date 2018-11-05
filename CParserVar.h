/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once


namespace zetjsoncpp {


#define N_ELEMENTS_JSON_ARRAY_PRINT	10

#define JS_STRING_CAST 		(CParserVarString<> *)
#define JS_ARRAY_STRING_CAST 	(CParserVarArrayString<> *)
#define JS_BOOL_CAST 		(CParserVarBoolean<> *)
#define JS_FLOAT_CAST 		(CParserVarNumber<> *)


#if  !defined(MIN)
#define  MIN(a,  b)              ((a)  <  (b)  ?  (a)  :  (b))
#endif

#define JSON_MAX_CONST_CHAR 50

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

#define getChr(name, ii) ((MIN(ii,JSON_MAX_CONST_CHAR))<sizeof(name)/sizeof(*name)?name[ii]:0)


	class CParserVar {//: public CVariable {
	protected:
		string result_json;
		string str_value;
		bool m_isParsed;

	public:

		enum {
			TYPE_UNKNOWN = 0, // 0
			TYPE_BOOL, // 1
			TYPE_NUMBER,// 2
			TYPE_STRING, // 3
			TYPE_PROPERTY_GROUP,
			TYPE_ARRAY = 0x100,
			TYPE_ARRAY_BOOL = TYPE_BOOL + TYPE_ARRAY, // 6
			TYPE_ARRAY_NUMBER = TYPE_NUMBER + TYPE_ARRAY, // 7
			TYPE_ARRAY_STRING = TYPE_STRING + TYPE_ARRAY, // 9
			TYPE_ARRAY_PROPERTY_GROUP = TYPE_PROPERTY_GROUP + TYPE_ARRAY
		};

		enum {
			PROPERTY_STR_MINIMIZED = 0x1 << 0
		};


		static const char *idTypeToString(int index) {
			switch (index) {
			default:
			case TYPE_UNKNOWN:
				break;
			case TYPE_BOOL: return "TYPE_BOOL";
				//case INT32_TYPE: return "INT32_TYPE";
			case TYPE_NUMBER: return "TYPE_NUMBER";
			case TYPE_STRING: return "STRING TYPE";
			case TYPE_PROPERTY_GROUP: return "TYPE_PROPERTY_GROUP";

			case TYPE_ARRAY_BOOL: return "ARRAY BOOL TYPE";
				//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
			case TYPE_ARRAY_NUMBER: return "ARRAY FLOAT TYPE";
			case TYPE_ARRAY_STRING: return "ARRAY STRING TYPE";
			case TYPE_ARRAY_PROPERTY_GROUP: return "ARRAY PROPERTY GROUP TYPE";
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
			this->_m_pvariableName = "pvar_noname";
			this->p_end_data = NULL;
			this->p_data = NULL;
			this->size_data = 0;
			this->p_ini_data = NULL;
			this->_m_iType = CParserVar::TYPE_UNKNOWN;
			this->m_isParsed = false;
		}

		virtual string & cpp2json() {
			result_json = "//no data:\n{}\n";
			return result_json;
		}

		virtual CParserVar * newData() {
			return NULL;
		}

		virtual string & getStrValue(int ident, uint32_t flags) {
			this->str_value = "??";
			return str_value;
		}

		virtual void add(CParserVar * s) {}

		virtual ~CParserVar() {

		}

		void setParsed(bool parsed) {
			m_isParsed = parsed;
		}

		bool isParsed() const {
			return m_isParsed;
		}
	};

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarNamed : public CParserVar {
	public:
		//----------------------------------------------------------------
		// DON'T js_ini AND NOT DECLARE ANY CParserVar UNDER IT !!!!

		CParserVar 	js_ini;

		//----------------------------------------------------------------

		CParserVarNamed() {

			std::vector<char> vec = { chr1, chr2,_T_NAME... };
			string s_aux(vec.begin(), vec.end());

			char buffer[512] = { 0 };

			strcpy(buffer, s_aux.c_str());

			if (strlen(buffer) == 0)
			{
				fprintf(stderr,"Parser variable with name! Advice: put a breakpoint here to known source of anonymous template!!!\n");
			}

			//strcpy(this->_m_pvariableName,  _T_NAME);
			this->_m_pvariableName = buffer;
			this->size_data = sizeof(CParserVarNamed);
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0)
		{
			this->str_value = "??";
			return this->str_value;
		}

		virtual ~CParserVarNamed() {}
	};




	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarNumber : public CParserVarNamed<chr1, chr2, _T_NAME ...>,public CNumber {


		bool m_forceInteger;
		void init() {
			//number = 0;
			this->_m_iType = CParserVar::TYPE_NUMBER;
			this->size_data = sizeof(CParserVarNumber<chr1, chr2, _T_NAME...>);
			this->p_data = &this->m_numVar;
			m_forceInteger = false;
			if (this->_m_pvariableName == "") {

				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}
		}

	public:

		CParserVarNumber() {
			init();
		}

		explicit CParserVarNumber(float i) {
			init();
			this->m_numVar = i;


		}

		CParserVarNumber & operator =(float b) {

			this->m_numVar = b;
			return *this;
		}

		void setForceInteger(bool force) {
			m_forceInteger = force;
		}

		CParserVarNumber & operator =(int i) {

			this->m_numVar = (float)i;
			return *this;
		}


		operator int32_t () const {
			return (int32_t)(*((float *)this->p_data));
		}

		CParserVarNumber & operator =(const string & intStr) {

			this->m_numVar = CZetJsonCppUtils::fromString<float>(intStr);
			return *this;
		}

		operator float() {

			return this->m_numVar;
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {

			if (m_forceInteger)
				this->str_value = "" + CZetJsonCppUtils::intToString(this->m_numVar);
			else
				this->str_value = "" + CZetJsonCppUtils::floatToString(this->m_numVar);
			return this->str_value;
		}

		virtual ~CParserVarNumber(){}
	};

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarBoolean : public CParserVarNamed<chr1, chr2, _T_NAME ...>, public CBoolean {


		void init() {
			//b_value=false;
			this->_m_iType = CParserVar::TYPE_BOOL;
			this->size_data = sizeof(CParserVarBoolean<chr1, chr2, _T_NAME...>);
			this->p_data = &this->m_boolVar;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}
		}

	public:

		explicit CParserVarBoolean() {

			init();
		}


		//_T_NAME name;
		explicit CParserVarBoolean(bool b) {
			init();
			*((bool *)this->p_data) = b;

		}


		CParserVarBoolean & operator =(bool b) {

			*((bool *)this->p_data) = b;
			return *this;
		}

		CParserVarBoolean & operator =(const string & str) {

			if (CZetJsonCppUtils::toLower(str) == "true") *((bool *)this->p_data) = true;
			else if (CZetJsonCppUtils::toLower(str) == "false") *((bool *)this->p_data) = false;
			else fprintf(stderr,"undefined value to assign bool value\n");
			return *this;
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {

			string result_bool = (*((bool *)this->p_data) == false ? "false" : "true");
			this->str_value = "" + result_bool;
			return this->str_value;
		}

		virtual ~CParserVarBoolean(){}

	};

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarString : public CParserVarNamed<chr1, chr2, _T_NAME... > , public CString{
	protected:
		virtual void init() {

			this->m_force_string = false;
			this->_m_iType = CParserVar::TYPE_STRING;
			this->size_data = sizeof(CParserVarString<chr1, chr2, _T_NAME...>);
			this->p_data = &this->m_str;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}

		}

	public:
		string s_value;

		bool	m_force_string;

		//_T_NAME name;
		CParserVarString() {
			init();
		}

		explicit CParserVarString(string & s) {
			init();
			*((string *)this->p_data) = s;
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "\"" + *((string *)this->p_data) + "\"";
			return this->str_value;
		}

		CParserVarString & operator = (const string & s) {

			this->s_value = s;
			return *this;
		}

		bool operator == (const string & s) const {
			return this->s_value == s;

		}

		bool operator == (const char * s) const {
			return !strcmp(this->s_value.c_str(), s);

		}

		bool operator != (const char * s) const {
			return strcmp(this->s_value.c_str(), s);

		}

		bool operator != (const string  s) const {
			return this->s_value != s;

		}


		operator const string() const {
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

		void setForceAsString(bool m_force) {
			m_force_string = m_force;
		}

		bool isForceAsString() {
			return m_force_string;
		}

		virtual ~CParserVarString(){}
	};



	template<typename _T_DATA, char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarPropertyGroup : public CParserVarNamed<chr1, chr2, _T_NAME...>, public _T_DATA {


	public:


		//----------------------------------------------------------------
		// DON'T MOVE js_end ON THIS CLASS !!!!

		CParserVar 	js_end;

		//----------------------------------------------------------------
		void setup(uint32_t numParam = 0, ...) {
			// PRE: All args must be string. The program can parse the apropiate type var
			// with its emmbedded type.

			this->_m_iType = CParserVar::TYPE_PROPERTY_GROUP;
			this->size_data = sizeof(CParserVarPropertyGroup<_T_DATA, chr1, chr2, _T_NAME...>);

			CParserVar *ptr = ((CParserVar *)&this->js_ini + 1);
			this->p_data = ptr;
			this->p_end_data = ((CParserVar *)&js_end - 1);

			//-------
			// Iterate on all its elements ...
			char *aux_p = (char *)this->p_data;
			char *end_p = (char *)this->p_end_data;

			va_list arg_list;
			// inicialize all vars struct in order of pass parameters ...
			va_start(arg_list, numParam);
			for (unsigned i = 0; i < numParam && (aux_p < end_p); i++) {
				const char * variable = va_arg(arg_list, const char *);
				CParserVar * p_sv = (CParserVar *)aux_p;

				switch (p_sv->_m_iType)
				{
				case CParserVar::TYPE_STRING:
					//print_info_cr("string ...!\n\n");
					*(JS_STRING_CAST p_sv) = variable;//->assign();
					break;
				}

				aux_p += p_sv->size_data;
			}
			va_end(arg_list);
			//---------

		}

		CParserVarPropertyGroup(...) {
			setup();
		}

		CParserVarPropertyGroup(uint32_t numParam,...) {
			setup(numParam);
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		//std::string result_json;
		virtual string & cpp2json(uint32_t flags = 0) {
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "";
			cpp2jsonRecursive(this, this->result_json, 0, flags);

			if (not_minimized)
				this->result_json += "\n";

			return this->result_json;

		}

		void cpp2jsonRecursive(CParserVar * c_data, std::string & result_s, int level, uint32_t flags) {

			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);

			if (not_minimized)
				for (int i = 0; i < level; i++)
					result_s = result_s + "\t";
			result_s = result_s + "{";

			if (not_minimized)
				result_s += "\n";

			char *aux_p = (char *)c_data->p_data;
			char *end_p = (char *)c_data->p_end_data;

			for (; aux_p < end_p; ) {
				// if(chkType()) // --> get and parse ...
				CParserVar * p_sv = (CParserVar *)aux_p;
				if (p_sv != NULL) {
					if (not_minimized)
						for (int i = 0; i <= level; i++)
							result_s = result_s + "\t";


					result_s = result_s + "\"" + p_sv->_m_pvariableName + "\":";

					switch (p_sv->_m_iType)// == )
					{
					case CParserVar::TYPE_BOOL:

					case CParserVar::TYPE_NUMBER:
					case CParserVar::TYPE_STRING:
						result_s = result_s + p_sv->getStrValue(level, flags);
						break;

					case CParserVar::TYPE_PROPERTY_GROUP:
						//printf("Accessing property groupr %s ...\n", p_sv->_m_pvariableName);
						if (not_minimized)
							result_s += "\n";

						cpp2jsonRecursive(p_sv, result_s, level + 1, flags);
						break;
						// arrays
					case CParserVar::TYPE_ARRAY_BOOL:

					case CParserVar::TYPE_ARRAY_STRING:
					case CParserVar::TYPE_ARRAY_PROPERTY_GROUP:

						if (not_minimized) {
							result_s += "\n";

							for (int i = 0; i <= level; i++)
								result_s = result_s + "\t";
						}

						result_s = result_s + "[";

						if (not_minimized)
							result_s += "\n";

						if (p_sv->_m_iType != CParserVar::TYPE_ARRAY_PROPERTY_GROUP)
							result_s = result_s + p_sv->getStrValue(level, flags);
						else
						{
							//result_s = result_s + "\""+p_sv->name+"\": [\n";

								//first_element_array=true;
							vector <CParserVar *>  *vec = (vector<CParserVar *> *)(p_sv->p_data);

							for (unsigned k = 0; k < vec->size(); k++)
							{
								if (k > 0)
									result_s = result_s + ",";

								if (not_minimized)
									result_s += "\n";


								cpp2jsonRecursive(vec->at(k), result_s, level + 2, flags);
							}
						}

						if (not_minimized) {
							result_s += "\n";

							for (int i = 0; i <= level; i++)
								result_s = result_s + "\t";
						}

						result_s = result_s + "]";


						break;
					}
				}
				aux_p += p_sv->size_data;

				if (aux_p < end_p)
					result_s = result_s + ",";

				if (not_minimized)
					result_s += "\n";

			}

			if (not_minimized)
				for (int i = 0; i < level; i++)
					result_s = result_s + "\t";

			result_s = result_s + "}";
		}

		virtual ~CParserVarPropertyGroup(){};
	};


	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//   ARRAYS
	//

	template<typename _T_DATA, char a = 'a', char b = 'b'>
	class CDinamicVector {
	protected:
		vector<_T_DATA> vec_data;
	public:

		CDinamicVector() {}

		_T_DATA & 	operator[](int i) {
			return vec_data.at(i);
		}

		_T_DATA const& 	operator[](int i) const {
			return vec_data.at(i);
		}

		_T_DATA const& 	at(unsigned int i) const {

			return vec_data.at(i);
		}

		void			 	push_back(const _T_DATA & tt) {
			vec_data.push_back(tt);
		}

		void			 	clear() {
			vec_data.clear();
		}

		void 	erase(unsigned int i) {
			if (i < vec_data.size()) {
				vec_data.erase(vec_data.begin() + i);
			}
		}

		unsigned 			size() const {
			return vec_data.size();
		}

		const vector<_T_DATA> & getStdVector() {
			return vec_data;
		}
	};

	// ARRAY BOOL
	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarArrayBool : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<bool> {
	public:
		//_T_NAME name;
		CParserVarArrayBool() {
			this->_m_iType = CParserVar::TYPE_ARRAY_BOOL;
			this->size = sizeof(CParserVarArrayBool<chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(bool s) {
			((vector<bool> *)this->p_data)->push_back(s);
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {
			bool not_minimized = ((CParserVar::PROPERTY_STR_MINIMIZED & flags) == 0);
			//this->str_value ="";
			vector<bool> * v = (vector<bool> *)this->p_data;
			this->str_value = "";
			string m_sfValue;

			if (not_minimized)
				for (int k = 0; k <= (ident + 1); k++)
					this->str_value = this->str_value + "\t";

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0)
					this->str_value = this->str_value + ",";

				m_sfValue = "False";
				if (v->at(j) == true)
					m_sfValue = "True";


				this->str_value = this->str_value + "" + m_sfValue + " ";

				if (not_minimized) {
					if (j != 0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT) == 0)) {
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";

						this->str_value += "\n";
					}
				}

			}
			return this->str_value;
		}

		virtual ~CParserVarArrayBool(){}

	};


	// ARRAY FLOAT
	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarArrayNumber : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<float> {


	public:
		//_T_NAME name;
		CParserVarArrayNumber() {
			this->_m_iType = CParserVar::TYPE_ARRAY_NUMBER;
			this->size_data = sizeof(CParserVarArrayNumber<chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(float s) {
			((vector<float> *)this->p_data)->push_back(s);
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {
			//this->str_value ="";
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			vector<float> * v = (vector<float> *)this->p_data;
			this->str_value = "";
			string m_sfValue;
			for (int k = 0; k <= (ident + 1); k++)
				this->str_value = this->str_value + "\t";

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0)
					this->str_value = this->str_value + ",";
				m_sfValue = CZetJsonCppUtils::floatToString(v->at(j));

				this->str_value = this->str_value + "" + m_sfValue + " ";

				if (not_minimized) {
					if (j != 0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT) == 0)) {
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";
						this->str_value += "\n";
					}
				}

			}
			return this->str_value;
		}

		float *makeFloatBuffer(size_t & length) {

			short * floatBuf = new float[vec_data.size()];
			length=vec_data.size();
			for (unsigned i = 0; i < vec_data.size(); i++){
				floatBuf[i]=vec_data[i];
			}

			return floatBuf;
		}


		short *makeShortBuffer(size_t & length) {
			short * shortBuf = new short[vec_data.size()];
			length = vec_data.size();

			for (unsigned i = 0; i < vec_data.size(); i++){
				shortBuf[i]=vec_data[i];
			}

			return shortBuf;
		}


		//virtual ~CParserVarArrayNumber(){}
		virtual ~CParserVarArrayNumber() {

		}
	};

	// ARRAY STRING
	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarArrayString : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<std::string> {
	public:
		//_T_NAME name;
		CParserVarArrayString() {
			this->_m_iType = CParserVar::TYPE_ARRAY_STRING;
			this->size_data = sizeof(CParserVarArrayString<chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(string const & s) {
			((vector<string> *)this->p_data)->push_back(s);
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->str_value = "";
			vector<string> * v = (vector<string> *)this->p_data;

			if (not_minimized)
				for (int k = 0; k <= (ident + 1); k++)
					this->str_value = this->str_value + "\t";

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0)
					this->str_value = this->str_value + ",";

				this->str_value = this->str_value + "\"" + v->at(j) + "\" ";

				if (not_minimized)
					if (j != 0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT) == 0))
					{
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";
						this->str_value += "\n";
					}

			}
			return this->str_value;
		}

		virtual ~CParserVarArrayString(){}

	};


	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//   INTERPOLATORS
	//


	template<typename _T_DATA, char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarArrayPropertyGroup : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<CParserVarPropertyGroup<_T_DATA> * > {

	public:

		CParserVarArrayPropertyGroup() {
			this->_m_iType = CParserVar::TYPE_ARRAY_PROPERTY_GROUP;
			this->size_data = sizeof(CParserVarArrayPropertyGroup<_T_DATA, chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}
		}

		virtual CParserVar *newData() {
			return new CParserVarPropertyGroup<_T_DATA>;
		}

		virtual string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		virtual void add(CParserVar * s) {
			CParserVarPropertyGroup< _T_DATA> *tt = (CParserVarPropertyGroup< _T_DATA> *)s;
			this->push_back(tt);
		}

		//std::string result_json;
		virtual string & cpp2json(uint32_t flags = 0) {
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "[";
			for (unsigned i = 0; i < this->size(); i++) {
				if (i > 0) {
					this->result_json += ",";
				}
				this->at(i)->cpp2jsonRecursive(this->at(i), this->result_json, 0, flags);
			}

			this->result_json += "]";
			if (not_minimized)
				this->result_json += "\n";

			return this->result_json;

		}

		void destroy() {

			for (unsigned i = 0; i < this->vec_data.size(); i++) {
				delete this->vec_data[i];
				this->vec_data[i] = NULL;
			}

			this->vec_data.clear();
		}

		virtual ~CParserVarArrayPropertyGroup() {
			destroy();

		}
	};
};
