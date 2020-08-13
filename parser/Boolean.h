namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class Boolean : public ParserVarNamed<chr1, chr2, _T_NAME ...>{


		void init() {
			//b_value=false;
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

		explicit Boolean() {

			init();
		}


		//_T_NAME name;
		explicit Boolean(bool b) {
			init();
			*((bool *)this->p_data) = b;

		}

		ZJ_Boolean::ZJ_Boolean(){
			value = false;
		}

		ZJ_Boolean::ZJ_Boolean(const ZJ_Boolean& b){
			this->value = b.value;
		}

		ZJ_Boolean::ZJ_Boolean(bool b ){
			value = b;
		}

		bool ZJ_Boolean::parse(const std::string & s){
			if(StrUtils::ToLower(s) == "true") return true;
			if(StrUtils::ToLower(s) == "false") return false;

			throw ("Cannot parse string to boolean.");
		}

		ZJ_Boolean &	ZJ_Boolean::operator = 	(const ZJ_Boolean & b){
			value = b.value;
			return (*this);
		}

		ZJ_Boolean &	ZJ_Boolean::operator = 	(bool b){
			value = b;
			return (*this);
		}

		ZJ_Boolean &	ZJ_Boolean::operator = 	(const std::string & b){
			value = parse(b);
			return (*this);
		}


		bool 		ZJ_Boolean::operator == (const ZJ_Boolean & b){
			return value == b.value;
		}

		bool 		ZJ_Boolean::operator && (const ZJ_Boolean & b){
			return value && b.value;
		}

		bool 		ZJ_Boolean::operator || (const ZJ_Boolean & b){
			return value || b.value;
		}

		bool 		ZJ_Boolean::operator != (const ZJ_Boolean & b){
			return value != b.value;
		}

		bool 		ZJ_Boolean::operator == (bool b){
			return value == b;
		}

		bool 		ZJ_Boolean::operator && (bool b){
			return value && b;
		}

		bool 		ZJ_Boolean::operator || (bool b){
			return value || b;
		}

		bool 		ZJ_Boolean::operator != (bool b){
			return value != b;
		}

		bool ZJ_Boolean::operator ! 	(){
			return !value;
		}





		Boolean & operator =(bool b) {

			*((bool *)this->p_data) = b;
			return *this;
		}

		Boolean & operator =(const std::string & str) {

			if (StrUtils::ToLower(str) == "true") *((bool *)this->p_data) = true;
			else if (StrUtils::ToLower(str) == "false") *((bool *)this->p_data) = false;
			else fprintf(stderr,"undefined value to assign bool value\n");
			return *this;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			std::string result_bool = (*((bool *)this->p_data) == false ? "false" : "true");
			this->str_value = "" + result_bool;
			return this->str_value;
		}

		virtual ~Boolean(){}

	};
}
