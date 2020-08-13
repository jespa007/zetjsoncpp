namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class Boolean : public ParserVarNamed<chr1, chr2, _T_NAME ...>{


		void init() {
			value=false;
			this->_m_iType = CParserVar::TYPE_BOOL;
			this->size_data = sizeof(Boolean<chr1, chr2, _T_NAME...>);
			this->p_data = &this->value;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}
		}

	public:
		bool value;

		operator bool() const {
			return value;
		}

		Boolean() {

			init();
		}

		//_T_NAME name;
		Boolean(bool b) {
			init();
			*((bool *)this->p_data) = b;

		}


		static bool parse(const std::string & s){
			if(StrUtils::ToLower(s) == "true") return true;
			if(StrUtils::ToLower(s) == "false") return false;

			throw ("Cannot parse string to boolean.");
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			std::string result_bool = (*((bool *)this->p_data) == false ? "false" : "true");
			this->str_value = "" + result_bool;
			return this->str_value;
		}

		virtual ~Boolean(){}

	};
}
