namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarBoolean : public JsonVarNamed<_T_NAME ...>{

	public:

		static bool parse(const std::string & s){
			if(zj_strutils::to_lower(s) == "true") return true;
			if(zj_strutils::to_lower(s) == "false") return false;

			throw ("Cannot parse string to boolean.");
		}

		JsonVarBoolean() {
			init();
		}

		//_T_NAME name;
		JsonVarBoolean(bool b) {
			init();
			*((bool *)this->__js_ptr_data__) = b;
		}

		// operators
		JsonVarBoolean & operator=(bool _value){
			__js_value__=_value;
			return *this;
		}

		JsonVarBoolean & operator=(const JsonVarBoolean & _b){
			__js_value__=_b.value;
			return *this;
		}

		bool operator ||(bool  b)  const {
			return this->__js_value__ || b;
		}

		bool operator ||(const JsonVarBoolean & b)  const {
			return this->__js_value__ || b.__js_value__;
		}

		bool operator &&(bool  b)  const {
			return this->__js_value__ && b;
		}

		bool operator &&(const JsonVarBoolean & b)  const {
			return this->__js_value__ && b.__js_value__;
		}

		bool operator ==(const JsonVarBoolean & b)  const {
			return this->__js_value__ == b.__js_value__;
		}

		bool operator ==(bool  b)  const {
			return this->__js_value__ == b;
		}

		bool operator !=(const JsonVarBoolean & b)  const {
			return  this->__js_value__ != b.__js_value__;
		}

		bool operator !=(bool  b)  const {
			return this->__js_value__ == b;
		}

		virtual std::string toString() {
			return std::string("") + (*((bool *)this->__js_ptr_data__) == false ? "false" : "true");
		}

		virtual ~JsonVarBoolean(){}

	private:

		bool __js_value__;

		void init() {
			__js_value__=false;
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_BOOLEAN;
			this->__js_size_data__ = sizeof(JsonVarBoolean<_T_NAME...>);
			this->__js_ptr_data__ = &this->__js_value__;
		}

	};
}
