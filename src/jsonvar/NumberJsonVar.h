namespace zetjsoncpp{

	template<char... _T_NAME>
	class NumberJsonVar : public NamedJsonVar<_T_NAME ...>{
	public:

			static float parse(const std::string & str ){
				float f=0;
				if(zj_strutils::str_to_float(&f,str)!=zj_strutils::STR_2_NUMBER_SUCCESS){
					throw std::runtime_error(std::string("cannot convert ") + str + std::string(" as float"));
				}

				return f;
			}

			NumberJsonVar() {
				init();
			}

			 NumberJsonVar(float f) {
				init();
				this->__zj_value__ = f;
			}

			 NumberJsonVar(const std::string & s) {
				init();
				this->__zj_value__ = parse(s);
			}

			//-----
			// pre neg
			NumberJsonVar   operator -  (){
				return NumberJsonVar(-__zj_value__);
			}


			 virtual void * getPtrValue(){ return &__zj_value__;}



			// operators
			NumberJsonVar & operator=(float _value){
				__zj_value__=_value;
				return *this;
			}

			NumberJsonVar & operator=(const NumberJsonVar & _n){
				__zj_value__=_n.__zj_value__;
				return *this;
			}

			operator float(){
				return this->__zj_value__;
			}

			//-----
			// +
			NumberJsonVar   operator +  (const NumberJsonVar & n) {
				return (__zj_value__ + n.__zj_value__);
			}

			NumberJsonVar   operator +  (float n)  {
				return NumberJsonVar(__zj_value__ + n);
			}

			NumberJsonVar   operator +  (int n)  {
				return NumberJsonVar(__zj_value__ + n);
			}
			//-----
			// -
			NumberJsonVar   operator -  (const NumberJsonVar & n) {
				return (__zj_value__ - n.__zj_value__);
			}

			NumberJsonVar   operator -  (float n)  {
				return NumberJsonVar(__zj_value__ - n);
			}

			NumberJsonVar   operator -  (int n)  {
				return NumberJsonVar(__zj_value__ - n);
			}
			//-----
			// *
			NumberJsonVar   operator *  (const NumberJsonVar & n) {
				return NumberJsonVar(__zj_value__ * n.__zj_value__);
			}
			NumberJsonVar   operator *  (float  n) {
				return NumberJsonVar(__zj_value__ * n);
			}
			NumberJsonVar   operator *  (int  n) {
				return NumberJsonVar(__zj_value__ * n);
			}
			//-----
			// /
			NumberJsonVar   operator /  (const NumberJsonVar & n) {

				if(n.__zj_value__ ==0)
					throw ("Error divide by 0");

				return NumberJsonVar(__zj_value__ / n.__zj_value__);
			}

			NumberJsonVar   operator /  (float  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return NumberJsonVar(__zj_value__ / n);
			}

			NumberJsonVar   operator /  (int  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return NumberJsonVar(__zj_value__ / n);
			}
			//-----
			// %
			NumberJsonVar   operator %  (const NumberJsonVar & n) {

				if(n.m_numVar ==0)
					throw ("Error divide by 0");

				return NumberJsonVar(fmod(__zj_value__ , n.__zj_value__));
			}

			NumberJsonVar   operator %  (float  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return NumberJsonVar(fmod(__zj_value__, n));
			}

			NumberJsonVar   operator %  (int  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return NumberJsonVar(fmod(__zj_value__ , n));
			}
			//-----
			// !=
			bool 	  operator == (const NumberJsonVar & n){
				return __zj_value__ == n.__zj_value__;
			}
			bool 	  operator == (float n){
				return __zj_value__ == n;
			}
			bool 	  operator == (int n){
				return __zj_value__ == n;
			}
			//-----
			// !=
			bool 	  operator != (const NumberJsonVar & n){
				return __zj_value__ != n.__zj_value__;
			}
			bool 	  operator != (float n){
				return __zj_value__ != n;
			}
			bool 	  operator != (int n){
				return __zj_value__ != n;
			}
			//-----
			// !=
			bool 	  operator <  (const NumberJsonVar & n){
				return __zj_value__ < n.__zj_value__;
			}
			bool 	  operator <  (float n){
				return __zj_value__ < n;
			}
			bool 	  operator <  (int n){
				return __zj_value__ < n;
			}
			//-----
			// <=
			bool 	  operator <= (const NumberJsonVar & n){
				return __zj_value__ <= n.__zj_value__;
			}
			bool 	  operator <= (float n){
				return __zj_value__ <= n;
			}
			bool 	  operator <= (int n){
				return __zj_value__ <= n;
			}

			//-----
			// >
			bool 	  operator >  (const NumberJsonVar & n){
				return __zj_value__ > n.__zj_value__;
			}
			bool 	  operator >  (float n){
				return __zj_value__ > n;
			}
			bool 	  operator >  (int n){
				return __zj_value__ > n;
			}
			//-----
			// >=
			bool	operator >= (const NumberJsonVar & n){
				return __zj_value__ >= n.__zj_value__;
			}
			bool 	  operator >= (float n){
				return __zj_value__ >= n;
			}
			bool 	  operator >= (int n){
				return __zj_value__ >= n;
			}
			//-----
			// +=
			NumberJsonVar & operator += (const NumberJsonVar & n){
				__zj_value__ += n.__zj_value__;
				return (*this);
			}

			NumberJsonVar & operator += (float n1){
				__zj_value__ += n1;
				return (*this);
			}

			NumberJsonVar & operator *= (const NumberJsonVar & n){
				__zj_value__ *= n.__zj_value__;
				return (*this);
			}

			NumberJsonVar & operator *= (float n1){
				__zj_value__ *= n1;
				return (*this);
			}

			NumberJsonVar & operator /= (const NumberJsonVar & n){
				if(n.__zj_value__ == 0)
					throw("Divide by 0!");

				__zj_value__ /= n.__zj_value__;
				return (*this);
			}

			NumberJsonVar & operator /= (float n1){

				if(n1 == 0){
					throw("Divide by 0!");
				}

				__zj_value__ /= n1;
				return (*this);
			}
			//--- -=
			NumberJsonVar & operator -= (const NumberJsonVar & n){
				__zj_value__ -= n.m_numVar;
				return (*this);
			}

			NumberJsonVar & operator -= (float n1){
				__zj_value__ -= n1;
				return (*this);
			}

			NumberJsonVar & operator ++(){
				__zj_value__++;
				return (*this);
			}
			float  operator ++(int){
				NumberJsonVar n(__zj_value__);
				operator++();
				return n;
			}

			virtual ~NumberJsonVar(){}
	private:

		float __zj_value__;

		void init() {
			__zj_value__ = 0;
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_NUMBER;
			this->__zj_size_data__ = sizeof(NumberJsonVar<_T_NAME...>);
		}


	};
}
