namespace zetjsoncpp{

	class StringJsonVar : public JsonVar{
	public:

		explicit StringJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_STRING) {
		}

		StringJsonVar(const std::string & _value){
			this->_value = _value;
		}

		StringJsonVar(const StringJsonVar & _value)
		:JsonVar(_value.getVariableNameCStr(), JsonVarType::JSON_VAR_TYPE_STRING){
			copy(_value);
		}

		StringJsonVar &operator=(const StringJsonVar &_value) {
		    if(this != &_value) {
		        copy(_value);
		    }
		    return *this;
		}

		StringJsonVar & operator =(const std::string & _value){
			this->_value = _value;
			return (*this);
		}

		const char *toConstChar(){
			return _value.c_str();
		}

		const std::string& getValue() const{
			return _value;
		}

		void setValue(const std::string& _value){
			this->_value = _value;
		}



		virtual void * getPtrValue(){ return &this->_value;}

		virtual ~StringJsonVar(){}
	protected:

		void copy(const StringJsonVar & _string_json_var){
			this->_value = _string_json_var._value;
			this->_is_deserialized = _string_json_var._is_deserialized;
		}

	private:

		std::string _value;


	};
}
