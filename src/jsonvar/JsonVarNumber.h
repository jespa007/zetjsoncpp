namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarNumber : public JsonVarNamed<_T_NAME ...>{
	public:

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
				this->__zj_value__ = f;
			}

			 JsonVarNumber(const std::string & s) {
				init();
				this->__zj_value__ = parse(s);
			}

			//-----
			// pre neg
			JsonVarNumber   operator -  (){
				return JsonVarNumber(-__zj_value__);
			}


			 virtual void * getPtrValue(){ return &__zj_value__;}



			// operators
			JsonVarNumber & operator=(float _value){
				__zj_value__=_value;
				return *this;
			}

			JsonVarNumber & operator=(const JsonVarNumber & _n){
				__zj_value__=_n.__zj_value__;
				return *this;
			}

			operator float(){
				return this->__zj_value__;
			}

			//-----
			// +
			JsonVarNumber   operator +  (const JsonVarNumber & n) {
				return (__zj_value__ + n.__zj_value__);
			}

			JsonVarNumber   operator +  (float n)  {
				return JsonVarNumber(__zj_value__ + n);
			}

			JsonVarNumber   operator +  (int n)  {
				return JsonVarNumber(__zj_value__ + n);
			}
			//-----
			// -
			JsonVarNumber   operator -  (const JsonVarNumber & n) {
				return (__zj_value__ - n.__zj_value__);
			}

			JsonVarNumber   operator -  (float n)  {
				return JsonVarNumber(__zj_value__ - n);
			}

			JsonVarNumber   operator -  (int n)  {
				return JsonVarNumber(__zj_value__ - n);
			}
			//-----
			// *
			JsonVarNumber   operator *  (const JsonVarNumber & n) {
				return JsonVarNumber(__zj_value__ * n.__zj_value__);
			}
			JsonVarNumber   operator *  (float  n) {
				return JsonVarNumber(__zj_value__ * n);
			}
			JsonVarNumber   operator *  (int  n) {
				return JsonVarNumber(__zj_value__ * n);
			}
			//-----
			// /
			JsonVarNumber   operator /  (const JsonVarNumber & n) {

				if(n.__zj_value__ ==0)
					throw ("Error divide by 0");

				return JsonVarNumber(__zj_value__ / n.__zj_value__);
			}

			JsonVarNumber   operator /  (float  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return JsonVarNumber(__zj_value__ / n);
			}

			JsonVarNumber   operator /  (int  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return JsonVarNumber(__zj_value__ / n);
			}
			//-----
			// %
			JsonVarNumber   operator %  (const JsonVarNumber & n) {

				if(n.m_numVar ==0)
					throw ("Error divide by 0");

				return JsonVarNumber(fmod(__zj_value__ , n.__zj_value__));
			}

			JsonVarNumber   operator %  (float  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return JsonVarNumber(fmod(__zj_value__, n));
			}

			JsonVarNumber   operator %  (int  n) {

				if(n ==0)
					throw ("Error divide by 0");

				return JsonVarNumber(fmod(__zj_value__ , n));
			}
			//-----
			// !=
			bool 	  operator == (const JsonVarNumber & n){
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
			bool 	  operator != (const JsonVarNumber & n){
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
			bool 	  operator <  (const JsonVarNumber & n){
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
			bool 	  operator <= (const JsonVarNumber & n){
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
			bool 	  operator >  (const JsonVarNumber & n){
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
			bool	operator >= (const JsonVarNumber & n){
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
			JsonVarNumber & operator += (const JsonVarNumber & n){
				__zj_value__ += n.__zj_value__;
				return (*this);
			}

			JsonVarNumber & operator += (float n1){
				__zj_value__ += n1;
				return (*this);
			}

			JsonVarNumber & operator *= (const JsonVarNumber & n){
				__zj_value__ *= n.__zj_value__;
				return (*this);
			}

			JsonVarNumber & operator *= (float n1){
				__zj_value__ *= n1;
				return (*this);
			}

			JsonVarNumber & operator /= (const JsonVarNumber & n){
				if(n.__zj_value__ == 0)
					throw("Divide by 0!");

				__zj_value__ /= n.__zj_value__;
				return (*this);
			}

			JsonVarNumber & operator /= (float n1){

				if(n1 == 0){
					throw("Divide by 0!");
				}

				__zj_value__ /= n1;
				return (*this);
			}
			//--- -=
			JsonVarNumber & operator -= (const JsonVarNumber & n){
				__zj_value__ -= n.m_numVar;
				return (*this);
			}

			JsonVarNumber & operator -= (float n1){
				__zj_value__ -= n1;
				return (*this);
			}

			JsonVarNumber & operator ++(){
				__zj_value__++;
				return (*this);
			}
			float  operator ++(int){
				JsonVarNumber n(__zj_value__);
				operator++();
				return n;
			}

			virtual ~JsonVarNumber(){}
	private:

		float __zj_value__;

		void init() {
			__zj_value__ = 0;
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_NUMBER;
			this->__zj_size_data__ = sizeof(JsonVarNumber<_T_NAME...>);
		}


	};
}
