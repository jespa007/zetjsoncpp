namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class Number : public ParserVarNamed<chr1, chr2, _T_NAME ...>{


		bool m_forceInteger;
		void init() {
			value = 0;
			this->_m_iType = CParserVar::TYPE_NUMBER;
			this->size_data = sizeof(Number<chr1, chr2, _T_NAME...>);
			this->p_data = &this->value;
			m_forceInteger = false;
			if (this->_m_pvariableName == "") {

				throw std::runtime_error("parse variable is empty, it's impossible to load any empty variable!");
			}
		}

	public:


		float value;

		static float parse(const std::string & str ){
			float f=0;
			if(StrUtils::str2float(&f,str)!=StrUtils::STR_2_NUMBER_SUCCESS){
				throw std::runtime_error(std::string("cannot convert ") + str + std::string(" as float"));
			}

			return f;
		}


		Number() {
			init();
		}

		 Number(float f) {
			init();
			this->value = f;
		}

		operator int() const {
			return value;
		}
		operator float() const {
			return value;
		}

		void setForceInteger(bool force) {
			m_forceInteger = force;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			if (m_forceInteger)
				this->str_value = "" + StrUtils::int2str(this->value);
			else
				this->str_value = "" + StrUtils::float2str(this->value);
			return this->str_value;
		}

		virtual ~Number(){}
	};
}
