namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarNumber : public CParserVarNamed<chr1, chr2, _T_NAME ...>,public ZJ_Number {


		bool m_forceInteger;
		void init() {
			//number = 0;
			this->_m_iType = CParserVar::TYPE_NUMBER;
			this->size_data = sizeof(CParserVarNumber<chr1, chr2, _T_NAME...>);
			this->p_data = &this->m_numVar;
			m_forceInteger = false;
			if (this->_m_pvariableName == "") {

				throw std::runtime_error("parse variable is empty, it's impossible to load any empty variable!");
			}
		}

	public:

		CParserVarNumber() {
			init();
		}

		explicit CParserVarNumber(float i) {
			init();
			this->m_numVar = i;


		}

		CParserVarNumber & operator =(float b) {

			this->m_numVar = b;
			return *this;
		}

		void setForceInteger(bool force) {
			m_forceInteger = force;
		}

		CParserVarNumber & operator =(int i) {

			this->m_numVar = (float)i;
			return *this;
		}


		operator int32_t () const {
			return (int32_t)(*((float *)this->p_data));
		}

		CParserVarNumber & operator =(const std::string & intStr) {

			float f=0;
			if(zj_string::str2float(&f,intStr) != zj_string::STR_2_NUMBER_SUCCESS){
				throw std::runtime_error("Cannot parse "+ intStr + " as number");
			}

			this->m_numVar=f;
			return *this;
		}

		operator float() {

			return this->m_numVar;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

			if (m_forceInteger)
				this->str_value = "" + zj_string::int2str(this->m_numVar);
			else
				this->str_value = "" + zj_string::float2str(this->m_numVar);
			return this->str_value;
		}

		virtual ~CParserVarNumber(){}
	};
}
