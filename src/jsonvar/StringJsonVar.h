namespace zetjsoncpp{

	class StringJsonVar : public NamedJsonVar{
	public:

		StringJsonVar(const char * _name = "") {
			init();
			this->setVariableName(_name);
		}

		StringJsonVar(const std::string & _value){
			init();
			__zj_value__ = _value;
		}

		StringJsonVar(const StringJsonVar & _value)
		:NamedJsonVar(_value.getVariableNameCStr()){
			init();
			copy(_value);
		}

		virtual void * getPtrValue(){ return &__zj_value__;}

		operator std::string(){return __zj_value__;}

		const char *toConstChar(){
			return __zj_value__.c_str();
		}

		const std::string& getValue() const{
			return __zj_value__;
		}

		void setValue(const std::string& _value){
			this->__zj_value__ = _value;
		}

		StringJsonVar & operator =(const std::string & _value){
			this->__zj_value__ = _value;
			return (*this);
		}

		StringJsonVar & operator =(const StringJsonVar & _value){
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
			this->__zj_size_data__ = sizeof(StringJsonVar);
		}

		void copy(const StringJsonVar & _value){
			this->__zj_value__ = _value.__zj_value__;
			this->__zj_is_parsed__ = _value.__zj_is_parsed__;
		}

	private:

		std::string __zj_value__;


	};
}
