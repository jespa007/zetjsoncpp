namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarString : public JsonVarNamed<_T_NAME... >{
	public:

		JsonVarString() {
			init();
		}

		JsonVarString(std::string s) {
			init();
			__js_value__ = s;
		}

		operator std::string(){return __js_value__;}

		operator std::string *(){return &__js_value__;}

		JsonVarString & operator =(const std::string & _value){
			this->__js_value__ = _value;
			return (*this);
		}

		bool operator ==(const std::string & _value) const{
			return this->__js_value__ == _value;
		}

		bool operator ==(const JsonVarString & s) const{
			return this->__js_value__ == s.value;

		}

		bool operator != (const std::string _value) const {
			return this->__js_value__ != _value;

		}

		bool operator !=(const JsonVarString & s) const{
			return this->__js_value__ != s.value;

		}

		JsonVarString operator +(const std::string & s)  const {
			return JsonVarString(this->__js_value__ + s);
		}

		JsonVarString operator +(const JsonVarString & s)  const {
			return JsonVarString(this->__js_value__ + s.__js_value__);
		}

		operator const char * () const{
			return (char *)__js_value__.c_str();
		}

		operator char * () const{
			return __js_value__.c_str();
		}

		virtual std::string toString() {
			return std::string("\"") + *((std::string *)this->__js_ptr_data__) + "\"";
		}

		virtual ~JsonVarString(){}
	protected:

		virtual void init() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_STRING;
			this->__js_size_data__ = sizeof(JsonVarString<_T_NAME...>);
			this->__js_ptr_data__ = &this->__js_value__;
		}

	private:

		std::string __js_value__;


	};
}
