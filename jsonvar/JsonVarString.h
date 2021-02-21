namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarString : public JsonVarNamed<_T_NAME... >{
	public:

		JsonVarString() {
			init();
		}

		JsonVarString(const std::string & s) {
			init();
			__zj_value__ = s;
		}

		virtual void * getPtrValue(){ return &__zj_value__;}

		operator std::string(){return __zj_value__;}

		const char *c_str(){
			return __zj_value__.c_str();
		}

		JsonVarString & operator =(const std::string & _value){
			this->__zj_value__ = _value;
			return (*this);
		}

		JsonVarString & operator =(const JsonVarString<> & _value){
			this->__zj_value__ = _value.__zj_value__;
			return (*this);
		}


		friend bool operator ==(const std::string & s1,const JsonVarString & s2)  {
			return s1==s2.__zj_value__;
		}

		friend bool operator ==(const JsonVarString & s1,const std::string & s2)  {
			return s1.__zj_value__==s2;
		}

		friend bool operator ==(const JsonVarString & s1,const JsonVarString & s2)  {
			return s1.__zj_value__==s2.__zj_value__;
		}

		friend bool operator !=(const std::string & s1,const JsonVarString & s2)  {
			return s1!=s2.__zj_value__;
		}

		friend bool operator !=(const JsonVarString & s1,const std::string & s2)  {
			return s1.__zj_value__!=s2;
		}

		friend bool operator !=(const JsonVarString & s1,const JsonVarString & s2)  {
			return s1.__zj_value__!=s2.__zj_value__;
		}


		friend JsonVarString operator +(const std::string & s1,const JsonVarString & s2)  {
			return JsonVarString(s1+s2.__zj_value__);
		}

		friend JsonVarString operator +(const JsonVarString & s1,const std::string & s2)  {
			return JsonVarString(s1.__zj_value__+s2);
		}

		friend JsonVarString operator +(const JsonVarString & s1,const JsonVarString & s2)  {
			return JsonVarString(s1.__zj_value__+s2.__zj_value__);
		}


		virtual ~JsonVarString(){}
	protected:

		virtual void init() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_STRING;
			this->__zj_size_data__ = sizeof(JsonVarString<_T_NAME...>);
		}

	private:

		std::string __zj_value__;


	};
}
