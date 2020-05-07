#pragma once
namespace zetjsoncpp {

class ZJ_Number{//:public CVariable{
protected:

public:
	float m_numVar;

	static float parse(const std::string & str ){
		float f=0;
		if(zj_string_utils::str2float(&f,str)!=zj_string_utils::STR_2_NUMBER_SUCCESS){
			throw std::runtime_error(std::string("cannot convert ") + str + std::string(" as float"));
		}

		return f;
	}


	ZJ_Number(){
		m_numVar = 0;
	}

	ZJ_Number(const ZJ_Number& n){
		m_numVar = n.m_numVar;
	}

	ZJ_Number(int i){
		m_numVar = i;
	}

	ZJ_Number(unsigned i){
		m_numVar = i;
	}


	ZJ_Number(float f){
		m_numVar = f;
	}

	operator int() const {
		return m_numVar;
	}
	operator float() const {
		return m_numVar;
	}
	//--- =
	virtual ZJ_Number & operator  = (const ZJ_Number & n){
		m_numVar = n.m_numVar;
		return (*this);
	}

	ZJ_Number & operator  = (int n){
		m_numVar = n;
		return (*this);
	}

	ZJ_Number & operator  = (float n){
		m_numVar = n;
		return (*this);
	}

	ZJ_Number & operator  = (const std::string & n){
		m_numVar = parse(n);
		return (*this);
	}

	void set(const ZJ_Number & n){
		this->m_numVar = n.m_numVar;
	}

	void set(int n){
		this->m_numVar = n;
	}

	void set(unsigned n){
		this->m_numVar = n;
	}

	void set(float n){
		this->m_numVar = n;
	}
	//--- +
	ZJ_Number   operator +  (const ZJ_Number & n) const{
		ZJ_Number n1;
		n1.m_numVar = m_numVar + n.m_numVar;
		return n1;
	}

	ZJ_Number   operator +  (float n) const {
		ZJ_Number n1;
		n1.m_numVar = m_numVar + n;
		return n1;

	}

	ZJ_Number   operator +  (int n) const{
		ZJ_Number n1;
		n1.m_numVar = m_numVar + n;
		return n1;

	}
	//--- -
	ZJ_Number   operator -  (const ZJ_Number & n) const{
		ZJ_Number n1;
		n1.m_numVar = m_numVar - n.m_numVar;
		return n1;
	}

	ZJ_Number   operator -  (){
		ZJ_Number n1;
		n1.m_numVar = -m_numVar;
		return n1;
	}
	//--- /
	ZJ_Number   operator /  (const ZJ_Number & n) const{
		ZJ_Number n1;

		if(n.m_numVar ==0)
			throw ("Error divide by 0");

		n1.m_numVar = m_numVar / n.m_numVar;
		return n1;
	}
	//--- ==
	bool 	  operator == (const ZJ_Number & n){
		return m_numVar == n.m_numVar;
	}
	bool 	  operator == (float n){
		return m_numVar == n;
	}
	bool 	  operator == (int n){
		return m_numVar == n;
	}
	//--- !=
	bool 	  operator != (const ZJ_Number & n){
		return m_numVar != n.m_numVar;
	}
	bool 	  operator != (float n){
		return m_numVar != n;
	}
	bool 	  operator != (int n){
		return m_numVar != n;
	}
	//--- <
	bool 	  operator <  (const ZJ_Number & n){
		return m_numVar < n.m_numVar;
	}
	bool 	  operator <  (float n){
		return m_numVar < n;
	}
	bool 	  operator <  (int n){
		return m_numVar < n;
	}
	//--- <=
	bool 	  operator <= (const ZJ_Number & n){
		return m_numVar <= n.m_numVar;
	}
	bool 	  operator <= (float n){
		return m_numVar <= n;
	}
	bool 	  operator <= (int n){
		return m_numVar <= n;
	}
	//--- >
	bool 	  operator >  (const ZJ_Number & n){
		return m_numVar > n.m_numVar;
	}
	bool 	  operator >  (float n){
		return m_numVar > n;
	}
	bool 	  operator >  (int n){
		return m_numVar > n;
	}
	//--- >=
	bool	operator >= (const ZJ_Number & n){
		return m_numVar >= n.m_numVar;
	}
	bool 	  operator >= (float n){
		return m_numVar >= n;
	}
	bool 	  operator >= (int n){
		return m_numVar >= n;
	}
	//--- +=
	ZJ_Number & operator += (const ZJ_Number & n){
		m_numVar += n.m_numVar;
		return (*this);
	}

	ZJ_Number & operator += (int n1){
		m_numVar += n1;
		return (*this);
	}

	ZJ_Number & operator += (float n1){
		m_numVar += n1;
		return (*this);
	}
	//--- *=
	ZJ_Number & operator *= (const ZJ_Number & n){
		m_numVar *= n.m_numVar;
		return (*this);
	}

	ZJ_Number & operator *= (int n1){
		m_numVar *= n1;
		return (*this);
	}

	ZJ_Number & operator *= (float n1){
		m_numVar *= n1;
		return (*this);
	}
	//--- /=
	ZJ_Number & operator /= (const ZJ_Number & n){
		if(n.m_numVar == 0)
			throw("Divide by 0!");

		m_numVar /= n.m_numVar;
		return (*this);
	}

	ZJ_Number & operator /= (int n1){

		if(n1 == 0)
			throw("Divide by 0!");
		m_numVar /= n1;
		return (*this);
	}

	ZJ_Number & operator /= (float n1){

		if(n1 == 0)
			throw("Divide by 0!");

		m_numVar /= n1;
		return (*this);
	}
	//--- -=
	ZJ_Number & operator -= (const ZJ_Number & n){
		m_numVar -= n.m_numVar;
		return (*this);
	}

	ZJ_Number & operator -= (int n1){
		m_numVar -= n1;
		return (*this);
	}

	ZJ_Number & operator -= (float n1){
		m_numVar -= n1;
		return (*this);
	}
	//--- ++
	ZJ_Number & operator ++(){
		m_numVar++;
		return (*this);
	}
	ZJ_Number  operator ++(int){
		ZJ_Number n(m_numVar);
		operator++();
		return n;
	}

	~ZJ_Number(){

	}

};
}

