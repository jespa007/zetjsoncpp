namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarBoolean : public JsonVarNamed<_T_NAME ...>{

	public:
		bool value;

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
			*((bool *)this->p_data) = b;
		}

		// operators
		JsonVarBoolean & operator=(bool _value){ value=_value; return *this;}
		JsonVarBoolean & operator=(const JsonVarBoolean & _b){ value=_b.value; return *this;}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			std::string result_bool = (*((bool *)this->p_data) == false ? "false" : "true");
			this->str_value = "" + result_bool;
			return this->str_value;
		}

		virtual ~JsonVarBoolean(){}

	private:
		void init() {
			value=false;
			this->type = JsonVar::JSON_VAR_TYPE_BOOLEAN;
			this->size_data = sizeof(JsonVarBoolean<_T_NAME...>);
			this->p_data = &this->value;
		}

	};
}
