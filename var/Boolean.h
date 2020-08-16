namespace zetjsoncpp{

	template<char... _T_NAME>
	class Boolean : public ParserVarNamed<_T_NAME ...>{

	public:
		bool value;

		static bool parse(const std::string & s){
			if(zj_strutils::to_lower(s) == "true") return true;
			if(zj_strutils::to_lower(s) == "false") return false;

			throw ("Cannot parse string to boolean.");
		}

		Boolean() {
			init();
		}

		//_T_NAME name;
		Boolean(bool b) {
			init();
			*((bool *)this->p_data) = b;
		}

		// operators
		Boolean & operator=(bool _value){ value=_value; return *this;}
		Boolean & operator=(const Boolean & _b){ value=_b.value; return *this;}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			std::string result_bool = (*((bool *)this->p_data) == false ? "false" : "true");
			this->str_value = "" + result_bool;
			return this->str_value;
		}

		virtual ~Boolean(){}

	private:
		void init() {
			value=false;
			this->type = ParserVar::TYPE_BOOLEAN;
			this->size_data = sizeof(Boolean<_T_NAME...>);
			this->p_data = &this->value;
		}

	};
}
