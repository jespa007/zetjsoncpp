namespace ZetJsonCpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class ParserVarString : public CParserVarNamed<chr1, chr2, _T_NAME... > , public ZJ_String{
	protected:
		virtual void init() {

			this->m_force_string = false;
			this->_m_iType = CParserVar::TYPE_STRING;
			this->size_data = sizeof(ParserVarString<chr1, chr2, _T_NAME...>);
			this->p_data = &this->m_str;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}

		}

	public:
		std::string s_value;

		bool	m_force_string;

		//_T_NAME name;
		ParserVarString() {
			init();
		}

		operator const char * () const{
			return (char *)s_value.c_str();
		}

		operator char * () const{
			return s_value.c_str();
		}

		operator std::string () const{
			return s_value;
		}

		explicit ParserVarString(std::string & s) {
			init();
			*((std::string *)this->p_data) = s;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "\"" + *((std::string *)this->p_data) + "\"";
			return this->str_value;
		}

		ParserVarString & operator = (const std::string & s) {

			this->s_value = s;
			return *this;
		}

		bool operator == (const std::string & s) const {
			return this->s_value == s;

		}

		bool operator == (const char * s) const {
			return !strcmp(this->s_value.c_str(), s);

		}

		bool operator != (const char * s) const {
			return strcmp(this->s_value.c_str(), s);

		}

		bool operator != (const std::string  s) const {
			return this->s_value != s;

		}


		operator const std::string() const {
			return this->s_value;
		}

		operator const char *() {
			return (const char *)this->s_value.c_str();
		}

		ParserVarString & operator = (const char * s) {

			this->s_value = s;
			return *this;
		}

		operator std::string() {
			return this->s_value;

		}

		void setForceAsString(bool m_force) {
			m_force_string = m_force;
		}

		bool isForceAsString() {
			return m_force_string;
		}

		virtual ~ParserVarString(){}
	};
}
