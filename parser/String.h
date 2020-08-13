namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class String : public ParserVarNamed<chr1, chr2, _T_NAME... >{
	protected:
		virtual void init() {

			this->m_force_string = false;
			this->_m_iType = CParserVar::TYPE_STRING;
			this->size_data = sizeof(String<chr1, chr2, _T_NAME...>);
			this->p_data = &this->m_str;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}

		}

	public:
		std::string m_str;
		std::string s_value;

		bool	m_force_string;

		ZJ_String::ZJ_String(){
			m_str = "";
		}

		ZJ_String::ZJ_String(const std::string &  str){
			m_str = str;
		}

		ZJ_String::ZJ_String(const char * str){
			m_str = str;
		}

		operator std::string(){return m_str;};

		ZJ_String::ZJ_String(int i){
			m_str = StrUtils::int2str(i);
		}

		ZJ_String::ZJ_String(float f){
			m_str = StrUtils::float2str(f);
		}

		ZJ_String ZJ_String::operator +(const ZJ_String & param)  const {
			ZJ_String ss;
			ss.m_str = this->m_str + param.m_str;

			return ss;
		}


		ZJ_String & ZJ_String::operator =(const ZJ_String & str){
			this->m_str = str.m_str;

			return (*this);
		}

		ZJ_String & ZJ_String::operator =(const std::string & str){
			this->m_str = str;

			return (*this);
		}

		bool ZJ_String::operator ==(const ZJ_String & pp_str) const{
			return this->m_str == pp_str.m_str;

		}


		//_T_NAME name;
		String() {
			init();
		}

		operator const char * () const{
			return (char *)s_value.c_str();
		}

		operator char * () const{
			return s_value.c_str();
		}

		operator std::string () const{
			return s_value;
		}

		explicit String(std::string & s) {
			init();
			*((std::string *)this->p_data) = s;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "\"" + *((std::string *)this->p_data) + "\"";
			return this->str_value;
		}

		String & operator = (const std::string & s) {

			this->s_value = s;
			return *this;
		}

		bool operator == (const std::string & s) const {
			return this->s_value == s;

		}

		bool operator == (const char * s) const {
			return !strcmp(this->s_value.c_str(), s);

		}

		bool operator != (const char * s) const {
			return strcmp(this->s_value.c_str(), s);

		}

		bool operator != (const std::string  s) const {
			return this->s_value != s;

		}


		operator const std::string() const {
			return this->s_value;
		}

		operator const char *() {
			return (const char *)this->s_value.c_str();
		}

		String & operator = (const char * s) {

			this->s_value = s;
			return *this;
		}

		operator std::string() {
			return this->s_value;

		}

		void setForceAsString(bool m_force) {
			m_force_string = m_force;
		}

		bool isForceAsString() {
			return m_force_string;
		}

		virtual ~String(){}
	};
}
