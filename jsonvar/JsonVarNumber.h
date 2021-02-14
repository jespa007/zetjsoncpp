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
				this->__js_value__ = f;
			}

			 virtual void * getPtrValue(){ return &__js_value__;}

			 JsonVarNumber(const std::string & s) {
				init();
				this->__js_value__ = parse(s);
			}

			// operators
			JsonVarNumber & operator=(float _value){
				__js_value__=_value;
				return *this;
			}

			JsonVarNumber & operator=(const JsonVarNumber & _n){
				__js_value__=_n.__js_value__;
				return *this;
			}

			operator float(){
				return this->__js_value__;
			}

			//--------------------------
			// +
			friend JsonVarNumber operator +(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1+s2.__js_value__);
			}

			friend JsonVarNumber operator +(const JsonVarNumber & s1,float s2)  {
				return JsonVarNumber(s1.__js_value__+s2);
			}

			friend JsonVarNumber operator +(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__+s2.__js_value__);
			}
			//--------------------------
			// -
			friend JsonVarNumber operator -(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1-s2.__js_value__);
			}

			friend JsonVarNumber operator -(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__-s2);
			}

			friend JsonVarNumber operator -(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__-s2.__js_value__);
			}
			//--------------------------
			// *
			friend JsonVarNumber operator *(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1*s2.__js_value__);
			}

			friend JsonVarNumber operator *(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__*s2);
			}

			friend JsonVarNumber operator *(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__*s2.__js_value__);
			}
			//--------------------------
			// /
			friend JsonVarNumber operator /(float s1,const JsonVarNumber & s2)  {
				if(s2.__js_value__ ==0){
					throw ("Error divide by 0");
				}

				return JsonVarNumber(s1/s2.__js_value__);
			}

			friend JsonVarNumber operator /(const JsonVarNumber & s1,float & s2)  {

				if(s2 ==0){
					throw ("Error divide by 0");
				}
				return JsonVarNumber(s1.__js_value__/s2);
			}

			friend JsonVarNumber operator /(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				if(s2.__js_value__ ==0){
					throw ("Error divide by 0");
				}
				return JsonVarNumber(s1.__js_value__/s2.__js_value__);
			}
			//--------------------------
			// %
			friend JsonVarNumber operator %(float s1,const JsonVarNumber & s2)  {
				if(s2.__js_value__ ==0){
					throw ("Error divide by 0");
				}

				return JsonVarNumber(s1%s2.__js_value__);
			}

			friend JsonVarNumber operator %(const JsonVarNumber & s1,float & s2)  {

				if(s2 ==0){
					throw ("Error divide by 0");
				}
				return JsonVarNumber(s1.__js_value__%s2);
			}

			friend JsonVarNumber operator %(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				if(s2.__js_value__ ==0){
					throw ("Error divide by 0");
				}
				return JsonVarNumber(s1.__js_value__%s2.__js_value__);
			}
			//--------------------------
			// ==
			friend bool operator ==(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1==s2.__js_value__);
			}

			friend bool operator ==(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__==s2);
			}

			friend bool operator ==(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__==s2.__js_value__);
			}
			//--------------------------
			// !=
			friend bool operator !=(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1!=s2.__js_value__);
			}

			friend bool operator !=(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__!=s2);
			}

			friend bool operator !=(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__!=s2.__js_value__);
			}
			//--------------------------
			// <
			friend bool operator <(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1<s2.__js_value__);
			}

			friend bool operator <(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__<s2);
			}

			friend bool operator <(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__<s2.__js_value__);
			}
			//--------------------------
			// <=
			friend bool operator <=(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1<=s2.__js_value__);
			}

			friend bool operator <=(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__<=s2);
			}

			friend bool operator <=(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__<=s2.__js_value__);
			}
			//--------------------------
			// >
			friend bool operator >(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1>s2.__js_value__);
			}

			friend bool operator >(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__>s2);
			}

			friend bool operator >(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__>s2.__js_value__);
			}
			//--------------------------
			// >=
			friend bool operator >=(float s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1>=s2.__js_value__);
			}

			friend bool operator >=(const JsonVarNumber & s1,float & s2)  {
				return JsonVarNumber(s1.__js_value__>=s2);
			}

			friend bool operator >=(const JsonVarNumber & s1,const JsonVarNumber & s2)  {
				return JsonVarNumber(s1.__js_value__>=s2.__js_value__);
			}
			//--------------------------
			// +=
			JsonVarNumber & operator += (const JsonVarNumber & n){
				__js_value__ += n.__js_value__;
				return (*this);
			}

			JsonVarNumber & operator += (float n1){
				__js_value__ += n1;
				return (*this);
			}
			//--------------------------
			// *=
			JsonVarNumber & operator *= (const JsonVarNumber & n){
				__js_value__ *= n.__js_value__;
				return (*this);
			}

			JsonVarNumber & operator *= (float n1){
				__js_value__ *= n1;
				return (*this);
			}
			//--------------------------
			// /=
			JsonVarNumber & operator /= (const JsonVarNumber & n){
				if(n.__js_value__ == 0)
					throw("Divide by 0!");

				__js_value__ /= n.__js_value__;
				return (*this);
			}
			JsonVarNumber & operator /= (float n1){

				if(n1 == 0){
					throw("Divide by 0!");
				}

				__js_value__ /= n1;
				return (*this);
			}
			//--------------------------
			// -=
			JsonVarNumber & operator -= (const JsonVarNumber & n){
				__js_value__ -= n.m_numVar;
				return (*this);
			}

			JsonVarNumber & operator -= (float n1){
				__js_value__ -= n1;
				return (*this);
			}
			//--------------------------
			// ++
			JsonVarNumber & operator ++(){
				__js_value__++;
				return (*this);
			}
			float  operator ++(int){
				JsonVarNumber n(__js_value__);
				operator++();
				return n;
			}

			virtual std::string toString() {
				return  zj_strutils::float_to_str(__js_value__);
			}

			virtual ~JsonVarNumber(){}
	private:

		float __js_value__;

		void init() {
			__js_value__ = 0;
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_NUMBER;
			this->__js_size_data__ = sizeof(JsonVarNumber<_T_NAME...>);
		}


	};
}
