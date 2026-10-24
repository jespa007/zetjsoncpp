namespace zetjsoncpp{

	class BooleanJsonVar : public JsonVar{

	public:

		static bool parse(const std::string & s){
			if(string_utils::toLower(s) == "true") return true;
			if(string_utils::toLower(s) == "false") return false;

			throw ("Cannot parse string to boolean.");
		}

		explicit BooleanJsonVar(const char * _name ="")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_BOOLEAN) {
		}

		//_T_NAME name;
		BooleanJsonVar(bool b) {
			this->_value = b;
		}

		// operators
		BooleanJsonVar & operator=(bool _value){
			this->_value = _value;
			return *this;
		}

		BooleanJsonVar & operator=(const BooleanJsonVar & _b){
			_value=_b._value;
			return *this;
		}

		bool getValue() const {return this->_value;}
		void setValue(bool _value ){this->_value = _value;}
		virtual void * getPtrValue(){ return &this->_value;}


		virtual ~BooleanJsonVar(){}

	private:

		bool _value = false;

	};
}
