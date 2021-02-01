namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarNumber : public JsonVarNamed<_T_NAME ...>{
	public:

			float value;

			static float parse(const std::string & str ){
				float f=0;
				if(zj_strutils::str_to_float(&f,str)!=zj_strutils::STR_2_NUMBER_SUCCESS){
					throw std::runtime_error(std::string("cannot convert ") + str + std::string(" as float"));
				}

				return f;
			}

			JsonVarNumber() {
				init();
			}

			 JsonVarNumber(float f) {
				init();
				this->value = f;
			}

			 JsonVarNumber(const std::string & s) {
				init();
				this->value = parse(s);
			}

			// operators
			JsonVarNumber & operator=(float _value){
				value=_value;
				return *this;
			}

			JsonVarNumber & operator=(const JsonVarNumber & _n){
				value=_n.value;
				return *this;
			}

			JsonVarNumber   operator +  (const JsonVarNumber & n) const{
				JsonVarNumber n1;
				n1.value = value + n.value;
				return n1;
			}

			JsonVarNumber   operator +  (float n) const {
				JsonVarNumber n1;
				n1.value = value + n;
				return n1;

			}

			JsonVarNumber   operator -  (const JsonVarNumber & n) const{
				JsonVarNumber n1;
				n1.value = value - n.value;
				return n1;
			}

			JsonVarNumber   operator -  (){
				JsonVarNumber n1;
				n1.value = -value;
				return n1;
			}
			//--- /
			JsonVarNumber   operator /  (const JsonVarNumber & n) const{
				JsonVarNumber n1;

				if(n.m_numVar ==0)
					throw ("Error divide by 0");

				n1.value = value / n.value;
				return n1;
			}
			//--- ==
			bool 	  operator == (const JsonVarNumber & n){
				return value == n.value;
			}
			bool 	  operator == (float n){
				return value == n;
			}

			bool 	  operator != (const JsonVarNumber & n){
				return value != n.value;
			}
			bool 	  operator != (float n){
				return value != n;
			}

			bool 	  operator <  (const JsonVarNumber & n){
				return value < n.value;
			}
			bool 	  operator <  (float n){
				return value < n;
			}

			bool 	  operator <= (const JsonVarNumber & n){
				return value <= n.value;
			}

			bool 	  operator <= (float n){
				return value <= n;
			}

			bool 	  operator >  (const JsonVarNumber & n){
				return value > n.value;
			}
			bool 	  operator >  (float n){
				return value > n;
			}

			bool	operator >= (const JsonVarNumber & n){
				return value >= n.value;
			}

			bool 	  operator >= (float n){
				return value >= n;
			}

			JsonVarNumber & operator += (const JsonVarNumber & n){
				value += n.value;
				return (*this);
			}

			JsonVarNumber & operator += (float n1){
				value += n1;
				return (*this);
			}

			JsonVarNumber & operator *= (const JsonVarNumber & n){
				value *= n.value;
				return (*this);
			}

			JsonVarNumber & operator *= (float n1){
				value *= n1;
				return (*this);
			}

			JsonVarNumber & operator /= (const JsonVarNumber & n){
				if(n.value == 0)
					throw("Divide by 0!");

				value /= n.value;
				return (*this);
			}

			JsonVarNumber & operator /= (float n1){

				if(n1 == 0){
					throw("Divide by 0!");
				}

				value /= n1;
				return (*this);
			}
			//--- -=
			JsonVarNumber & operator -= (const JsonVarNumber & n){
				value -= n.m_numVar;
				return (*this);
			}

			JsonVarNumber & operator -= (float n1){
				value -= n1;
				return (*this);
			}

			JsonVarNumber & operator ++(){
				value++;
				return (*this);
			}
			JsonVarNumber  operator ++(int){
				JsonVarNumber n(value);
				operator++();
				return n;
			}

			void setForceInteger(bool force) {
				m_forceInteger = force;
			}

			virtual std::string & getStrValue(int ident, uint32_t flags = 0) {

				if (m_forceInteger){
					this->str_value = "" + zj_strutils::int_to_str(this->value);
				}
				else{
					this->str_value = "" + zj_strutils::float_to_str(this->value);
				}
				return this->str_value;
			}

			virtual ~JsonVarNumber(){}
	private:
		bool m_forceInteger;
		void init() {
			value = 0;
			this->type = JsonVar::JSON_VAR_TYPE_NUMBER;
			this->size_data = sizeof(JsonVarNumber<_T_NAME...>);
			this->p_data = &this->value;
			m_forceInteger = false;

		}


	};
}
