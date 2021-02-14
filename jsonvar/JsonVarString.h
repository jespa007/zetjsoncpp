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

		virtual void * getPtrValue(){ return &__js_value__;}

		operator std::string(){return __js_value__;}

		const char *c_str(){
			return __js_value__.c_str();
		}

		JsonVarString & operator =(const std::string & _value){
			this->__js_value__ = _value;
			return (*this);
		}

		JsonVarString & operator =(const JsonVarString<> & _value){
			this->__js_value__ = _value.__js_value__;
			return (*this);
		}


		bool operator ==(const std::string & _value) const{
			return this->__js_value__ == _value;
		}

		bool operator ==(const JsonVarString & s) const{
			return this->__js_value__ == s.__js_value__;

		}

		bool operator != (const std::string _value) const {
			return this->__js_value__ != _value;

		}

		bool operator !=(const JsonVarString & s) const{
			return this->__js_value__ != s.__js_value__;

		}

		friend JsonVarString operator +(const std::string & s1,const JsonVarString & s2)  {
			return JsonVarString(s1+s2.__js_value__);
		}

		friend JsonVarString operator +(const JsonVarString & s1,const std::string & s2)  {
			return JsonVarString(s1.__js_value__+s2);
		}

		friend JsonVarString operator +(const JsonVarString & s1,const JsonVarString & s2)  {
			return JsonVarString(s1.__js_value__+s2.__js_value__);
		}

		virtual std::string toString() {
			return std::string("\"") + this->__js_value__ + "\"";
		}

		virtual ~JsonVarString(){}
	protected:

		virtual void init() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_STRING;
			this->__js_size_data__ = sizeof(JsonVarString<_T_NAME...>);
		}

	private:

		std::string __js_value__;


	};
}
