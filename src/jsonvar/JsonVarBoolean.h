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
			this->__zj_value__ = b;
		}

		operator bool(){return __zj_value__;}

		virtual void * getPtrValue(){ return &__zj_value__;}

		// operators
		JsonVarBoolean & operator=(bool _value){
			__zj_value__=_value;
			return *this;
		}

		JsonVarBoolean & operator=(const JsonVarBoolean & _b){
			__zj_value__=_b.__zj_value__;
			return *this;
		}
		//--------------------------------------------------------
		// ||
		friend bool operator ||(const JsonVarBoolean & b1, bool b2)  {
			return b1.__zj_value__ || b2;
		}

		friend bool operator ||(bool b1, const JsonVarBoolean & b2)  {
			return b1 || b2.__zj_value__;
		}

		friend bool operator ||(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__zj_value__ || b2.__zj_value__;
		}

		//--------------------------------------------------------
		// &&
		friend bool operator &&(const JsonVarBoolean & b1, bool b2)  {
			return b1.__zj_value__ && b2;
		}

		friend bool operator &&(bool b1, const JsonVarBoolean & b2)  {
			return b1 && b2.__zj_value__;
		}

		friend bool operator &&(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__zj_value__ && b2.__zj_value__;
		}
		//--------------------------------------------------------
		// ==
		friend bool operator ==(const JsonVarBoolean & b1, bool b2)  {
			return b1.__zj_value__ == b2;
		}

		friend bool operator ==(bool b1, const JsonVarBoolean & b2)  {
			return b1 == b2.__zj_value__;
		}

		friend bool operator ==(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__zj_value__ == b2.__zj_value__;
		}
		//--------------------------------------------------------
		// !=
		friend bool operator !=(const JsonVarBoolean & b1, bool b2)  {
			return b1.__zj_value__ != b2;
		}

		friend bool operator !=(bool b1, const JsonVarBoolean & b2)  {
			return b1 != b2.__zj_value__;
		}

		friend bool operator !=(const JsonVarBoolean & b1, const JsonVarBoolean & b2)  {
			return b1.__zj_value__ != b2.__zj_value__;
		}



		virtual ~JsonVarBoolean(){}

	private:

		bool __zj_value__;

		void init() {
			__zj_value__=false;
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_BOOLEAN;
			this->__zj_size_data__ = sizeof(JsonVarBoolean<_T_NAME...>);
		}

	};
}
