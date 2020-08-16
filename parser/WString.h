namespace zetjsoncpp{

	template<char... _T_NAME>
	class WString : public ParserVarNamed<_T_NAME... >{
	public:
		std::wstring value;

		bool	m_force_string;

		WString() {
			init();
		}

		WString(std::wstring & s) {
			init();
			*((std::wstring *)this->p_data) = s;
		}

		operator std::wstring(){return value;}

		WString & operator =(const std::wstring & _value){
			this->value = _value;
			return (*this);
		}

		bool operator ==(const std::wstring & _value) const{
			return this->value == _value;

		}

		operator const char * () const{
			return (char *)value.c_str();
		}

		operator wchar_t * () const{
			return value.c_str();
		}

		virtual std::wstring & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "\"" + *((std::wstring *)this->p_data) + "\"";
			return this->str_value;
		}

		bool operator != (const std::wstring _value) const {
			return this->value != _value;

		}

		void setForceAsString(bool m_force) {
			m_force_string = m_force;
		}

		bool isForceAsString() {
			return m_force_string;
		}

		virtual ~WString(){}
	protected:
		virtual void init() {

			this->m_force_string = false;
			this->type = ParserVar::TYPE_STRING;
			this->size_data = sizeof(WString<_T_NAME...>);
			this->p_data = &this->value;


		}


	};
}
