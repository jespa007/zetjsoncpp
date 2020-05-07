namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarBoolean : public CParserVarNamed<chr1, chr2, _T_NAME ...>, public ZJ_Boolean {


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

		CParserVarBoolean & operator =(const std::string & str) {

			if (zj_string_utils::to_lower(str) == "true") *((bool *)this->p_data) = true;
			else if (zj_string_utils::to_lower(str) == "false") *((bool *)this->p_data) = false;
			else fprintf(stderr,"undefined value to assign bool value\n");
			return *this;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			std::string result_bool = (*((bool *)this->p_data) == false ? "false" : "true");
			this->str_value = "" + result_bool;
			return this->str_value;
		}

		virtual ~CParserVarBoolean(){}

	};
}
