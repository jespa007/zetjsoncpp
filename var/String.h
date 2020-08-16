namespace zetjsoncpp{

	template<char... _T_NAME>
	class String : public ParserVarNamed<_T_NAME... >{
	public:
		std::string value;

		bool	m_force_string;

		String() {
			init();
		}

		String(std::string & s) {
			init();
			*((std::string *)this->p_data) = s;
		}

		operator std::string(){return value;}

		String & operator =(const std::string & _value){
			this->value = _value;
			return (*this);
		}

		bool operator ==(const std::string & _value) const{
			return this->value == _value;

		}

		operator const char * () const{
			return (char *)value.c_str();
		}

		operator char * () const{
			return value.c_str();
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "\"" + *((std::string *)this->p_data) + "\"";
			return this->str_value;
		}

		bool operator != (const std::string _value) const {
			return this->value != _value;

		}

		void setForceAsString(bool m_force) {
			m_force_string = m_force;
		}

		bool isForceAsString() {
			return m_force_string;
		}

		virtual ~String(){}
	protected:
		virtual void init() {

			this->m_force_string = false;
			this->type = ParserVar::TYPE_STRING;
			this->size_data = sizeof(String<_T_NAME...>);
			this->p_data = &this->value;


		}


	};
}
