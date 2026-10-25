namespace zetjsoncpp{

	class StringJsonVar : public JsonVar{
	public:

		explicit StringJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_STRING) {
		}

		StringJsonVar(const std::string & _value)
		:JsonVar("", JsonVarType::JSON_VAR_TYPE_STRING){
			this->_value = _value;
		}

		StringJsonVar(const StringJsonVar & _other)
		:JsonVar(_other){
			this->_value = _other._value;
		}

		StringJsonVar &operator=(const StringJsonVar & _other) {
		    if(this != &_other) {
		        _value = _other._value;
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

		std::string _value;


	};
}
