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
			*((bool *)this->__js_ptr_data_start__) = b;
		}

		virtual void * getPtrValue(){ return &__js_value__;}

		// operators
		JsonVarBoolean & operator=(bool _value){
			__js_value__=_value;
			return *this;
		}

		JsonVarBoolean & operator=(const JsonVarBoolean & _b){
			__js_value__=_b.__js_value__;
			return *this;
		}
		//--------------------------------------------------------
		// ||
		friend bool operator ||(const JsonVarBoolean & b1, bool b2)  {
			return b1.__js_value__ || b2;
		}

		friend bool operator ||(bool b1, const JsonVarBoolean & b2)  {
			return b1 || b2.__js_value__;
		}

		friend bool operator ||(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__js_value__ || b2.__js_value__;
		}

		//--------------------------------------------------------
		// &&
		friend bool operator &&(const JsonVarBoolean & b1, bool b2)  {
			return b1.__js_value__ && b2;
		}

		friend bool operator &&(bool b1, const JsonVarBoolean & b2)  {
			return b1 && b2.__js_value__;
		}

		friend bool operator &&(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__js_value__ && b2.__js_value__;
		}
		//--------------------------------------------------------
		// ==
		friend bool operator ==(const JsonVarBoolean & b1, bool b2)  {
			return b1.__js_value__ == b2;
		}

		friend bool operator ==(bool b1, const JsonVarBoolean & b2)  {
			return b1 == b2.__js_value__;
		}

		friend bool operator ==(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__js_value__ == b2.__js_value__;
		}
		//--------------------------------------------------------
		// !=
		friend bool operator !=(const JsonVarBoolean & b1, bool b2)  {
			return b1.__js_value__ != b2;
		}

		friend bool operator !=(bool b1, const JsonVarBoolean & b2)  {
			return b1 != b2.__js_value__;
		}

		friend bool operator !=(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__js_value__ != b2.__js_value__;
		}

		virtual std::string toString() {
			return this->__js_value__ == false ? "false" : "true";
		}

		virtual ~JsonVarBoolean(){}

	private:

		bool __js_value__;

		void init() {
			__js_value__=false;
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_BOOLEAN;
			this->__js_size_data__ = sizeof(JsonVarBoolean<_T_NAME...>);
		}

	};
}
