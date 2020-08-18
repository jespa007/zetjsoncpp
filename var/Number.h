namespace zetjsoncpp{

	template<char... _T_NAME>
	class Number : public ParserVarNamed<_T_NAME ...>{
	public:

			float value;

			static float parse(const std::string & str ){
				float f=0;
				if(zj_strutils::str_to_float(&f,str)!=zj_strutils::STR_2_NUMBER_SUCCESS){
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

			// operators
			Number & operator=(float _value){
				value=_value;
				return *this;
			}

			Number & operator=(const Number & _n){
				value=_n.value;
				return *this;
			}

			Number   operator +  (const Number & n) const{
				Number n1;
				n1.value = value + n.value;
				return n1;
			}

			Number   operator +  (float n) const {
				Number n1;
				n1.value = value + n;
				return n1;

			}

			Number   operator -  (const Number & n) const{
				Number n1;
				n1.value = value - n.value;
				return n1;
			}

			Number   operator -  (){
				Number n1;
				n1.value = -value;
				return n1;
			}
			//--- /
			Number   operator /  (const Number & n) const{
				Number n1;

				if(n.m_numVar ==0)
					throw ("Error divide by 0");

				n1.value = value / n.value;
				return n1;
			}
			//--- ==
			bool 	  operator == (const Number & n){
				return value == n.value;
			}
			bool 	  operator == (float n){
				return value == n;
			}

			bool 	  operator != (const Number & n){
				return value != n.value;
			}
			bool 	  operator != (float n){
				return value != n;
			}

			bool 	  operator <  (const Number & n){
				return value < n.value;
			}
			bool 	  operator <  (float n){
				return value < n;
			}

			bool 	  operator <= (const Number & n){
				return value <= n.value;
			}

			bool 	  operator <= (float n){
				return value <= n;
			}

			bool 	  operator >  (const Number & n){
				return value > n.value;
			}
			bool 	  operator >  (float n){
				return value > n;
			}

			bool	operator >= (const Number & n){
				return value >= n.value;
			}

			bool 	  operator >= (float n){
				return value >= n;
			}

			Number & operator += (const Number & n){
				value += n.value;
				return (*this);
			}

			Number & operator += (float n1){
				value += n1;
				return (*this);
			}

			Number & operator *= (const Number & n){
				value *= n.value;
				return (*this);
			}

			Number & operator *= (float n1){
				value *= n1;
				return (*this);
			}

			Number & operator /= (const Number & n){
				if(n.value == 0)
					throw("Divide by 0!");

				value /= n.value;
				return (*this);
			}

			Number & operator /= (float n1){

				if(n1 == 0){
					throw("Divide by 0!");
				}

				value /= n1;
				return (*this);
			}
			//--- -=
			Number & operator -= (const Number & n){
				value -= n.m_numVar;
				return (*this);
			}

			Number & operator -= (float n1){
				value -= n1;
				return (*this);
			}

			Number & operator ++(){
				value++;
				return (*this);
			}
			Number  operator ++(int){
				Number n(value);
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

			virtual ~Number(){}
	private:
		bool m_forceInteger;
		void init() {
			value = 0;
			this->type = ParserVar::TYPE_NUMBER;
			this->size_data = sizeof(Number<_T_NAME...>);
			this->p_data = &this->value;
			m_forceInteger = false;

		}


	};
}
