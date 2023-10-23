namespace zetjsoncpp{

	template<char... _T_NAME>
	class StringJsonVar : public NamedJsonVar<_T_NAME... >{
	public:

		StringJsonVar() {
			init();
		}

		StringJsonVar(const std::string & s) {
			init();
			__zj_value__ = s;
		}

		virtual void * getPtrValue(){ return &__zj_value__;}

		operator std::string(){return __zj_value__;}

		const char *c_str(){
			return __zj_value__.c_str();
		}

		StringJsonVar & operator =(const std::string & _value){
			this->__zj_value__ = _value;
			return (*this);
		}

		StringJsonVar & operator =(const StringJsonVar<> & _value){
			this->__zj_value__ = _value.__zj_value__;
			return (*this);
		}

		friend bool operator ==(const std::string & s1,const StringJsonVar & s2)  {
			return s1==s2.__zj_value__;
		}

		friend bool operator ==(const StringJsonVar & s1,const std::string & s2)  {
			return s1.__zj_value__==s2;
		}

		friend bool operator ==(const StringJsonVar & s1,const StringJsonVar & s2)  {
			return s1.__zj_value__==s2.__zj_value__;
		}

		friend bool operator !=(const std::string & s1,const StringJsonVar & s2)  {
			return s1!=s2.__zj_value__;
		}

		friend bool operator !=(const StringJsonVar & s1,const std::string & s2)  {
			return s1.__zj_value__!=s2;
		}

		friend bool operator !=(const StringJsonVar & s1,const StringJsonVar & s2)  {
			return s1.__zj_value__!=s2.__zj_value__;
		}


		friend StringJsonVar operator +(const std::string & s1,const StringJsonVar & s2)  {
			return StringJsonVar(s1+s2.__zj_value__);
		}

		friend StringJsonVar operator +(const StringJsonVar & s1,const std::string & s2)  {
			return StringJsonVar(s1.__zj_value__+s2);
		}

		friend StringJsonVar operator +(const StringJsonVar & s1,const StringJsonVar & s2)  {
			return StringJsonVar(s1.__zj_value__+s2.__zj_value__);
		}

		virtual ~StringJsonVar(){}
	protected:

		virtual void init() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_STRING;
			this->__zj_size_data__ = sizeof(StringJsonVar<_T_NAME...>);
		}

	private:

		std::string __zj_value__;


	};
}
