#pragma once
namespace zetjsoncpp {

class CNumber{//:public CVariable{
protected:

public:
	double m_numVar;

	static double parse(const string & str );
	CNumber();
	CNumber(const CNumber&);
	CNumber(int );
	CNumber(unsigned );
	CNumber(float );
	CNumber(double );

	//operator int();
	//operator float();
	//operator double();
	operator int() const {
		return m_numVar;
	}
	operator double() const {
		return m_numVar;
	}

	void set(const CNumber & n){
		this->m_numVar = n.m_numVar;
	}

	void set(int n){
		this->m_numVar = n;
	}

	void set(unsigned n){
		this->m_numVar = n;
	}

	void set(double n){
		this->m_numVar = n;
	}

	CNumber   operator +  (const CNumber & n) const;
	CNumber   operator +  (double n) const;
	CNumber   operator +  (int n) const;

	//----
	// friend functions ...

	static CNumber   add(const CNumber &   n1, const CNumber & n2) {
		CNumber n;
		n.m_numVar = n1.m_numVar + n2.m_numVar;
		return n;
	}

	static CNumber   add(const CNumber & n1, double n2) {
		CNumber n;
		n.m_numVar = n1.m_numVar + n2;
		return n;
	}

	static CNumber   add(double n1, const CNumber & n2) {
		CNumber n;
		n.m_numVar = n1 + n2.m_numVar;
		return n;
	}

	static CNumber   add(const CNumber & n1, int n2) {
		CNumber n;
		n.m_numVar = n1.m_numVar + n2;
		return n;
	}

	static CNumber   add(int n1, const CNumber & n2) {
		CNumber n;
		n.m_numVar = n1 + n2.m_numVar;
		return n;
	}

	//----
	// less

	static bool   less(const CNumber &   n1, const CNumber & n2) {

		return n1.m_numVar < n2.m_numVar;
	}

	static bool   less(const CNumber & n1, double n2) {

		return n1.m_numVar < n2;
	}

	static bool   less(double n1, const CNumber & n2) {

		return n1 < n2.m_numVar;

	}

	static bool   less(const CNumber & n1, int n2) {

		return n1.m_numVar < n2;
	}

	static bool   less(int n1, const CNumber & n2) {

		return n1 < n2.m_numVar;

	}
	//----
	// less_equal

	static bool   less_equal(const CNumber &   n1, const CNumber & n2) {
		return n1.m_numVar <= n2.m_numVar;
	}

	static bool   less_equal(const CNumber & n1, double n2) {
		return n1.m_numVar <= n2;
	}

	static bool   less_equal(double n1, const CNumber & n2) {
		return n1 <= n2.m_numVar;
	}

	static bool   less_equal(const CNumber & n1, int n2) {
		return n1.m_numVar <= n2;
	}

	static bool   less_equal(int n1, const CNumber & n2) {
		return n1 <= n2.m_numVar;
	}

	//----
	// greather

	static bool   greather(const CNumber &   n1, const CNumber & n2) {
		return n1.m_numVar > n2.m_numVar;
	}

	static bool   greather(const CNumber & n1, double n2) {
		return n1.m_numVar > n2;
	}

	static bool   greather(double n1, const CNumber & n2) {

		return n1 > n2.m_numVar;
	}

	static bool   greather(const CNumber & n1, int n2) {
		return n1.m_numVar > n2;
	}

	static bool   greather(int n1, const CNumber & n2) {

		return n1 > n2.m_numVar;
	}

	//----
	// greather_equal

	static bool   greather_equal(const CNumber &   n1, const CNumber & n2) {
		return n1.m_numVar >= n2.m_numVar;
	}

	static bool   greather_equal(const CNumber & n1, double n2) {
		return n1.m_numVar >= n2;
	}

	static bool   greather_equal(double n1, const CNumber & n2) {
		return n1 >= n2.m_numVar;
	}

	static bool   greather_equal(const CNumber & n1, int n2) {
		return n1.m_numVar >= n2;
	}

	static bool   greather_equal(int n1, const CNumber & n2) {
		return n1 >= n2.m_numVar;
	}

	//----
	// equal

	static bool   equal(const CNumber &   n1, const CNumber & n2) {
		return n1.m_numVar == n2.m_numVar;
	}

	static bool   equal(const CNumber & n1, double n2) {
		return n1.m_numVar == n2;
	}

	static bool   equal(double n1, const CNumber & n2) {
		return n1 == n2.m_numVar;
	}

	static bool   equal(const CNumber & n1, int n2) {
		return n1.m_numVar == n2;
	}

	static bool   equal(int n1, const CNumber & n2) {
		return n1 == n2.m_numVar;
	}

	//----
	// not_equal

	static bool   not_equal(const CNumber &   n1, const CNumber & n2) {
		return n1.m_numVar != n2.m_numVar;
	}

	static bool   not_equal(const CNumber & n1, double n2) {
		return n1.m_numVar != n2;
	}

	static bool   not_equal(double n1, const CNumber & n2) {

		return n1 != n2.m_numVar;

	}


	static bool   not_equal(const CNumber & n1, int n2) {
		return n1.m_numVar != n2;
	}

	static bool   not_equal(int n1, const CNumber & n2) {

		return n1 != n2.m_numVar;

	}

	//---

	// prefix operator
	CNumber & operator ++ ();

	// postfix operator
	const CNumber operator ++ (int);



	CNumber   operator -  (const CNumber & n) const;
	CNumber   operator -  ();
	//CNumber   operator *  (const CNumber & n) const;

	static CNumber   mul(CNumber  n1, const CNumber & n2) {
		CNumber n;
		n.m_numVar = n1.m_numVar * n2.m_numVar;
		return n;
	}

	friend CNumber   operator *  (CNumber  n1, const CNumber & n2){
		return mul(n1,n2);
	}

		;/* {
		CNumber n;
		n.m_numVar = n1.m_numVar * n2.m_numVar;
		return n;
	}*/

	CNumber   operator /  (const CNumber & n) const;
	//CNumber   operator %  (const CNumber & n) const;
	//CNumber   operator &  (const CNumber & n) const;
	//CNumber   operator |  (const CNumber & n) const;
	//CNumber   operator ^  (const CNumber & n) const;
	//bool      operator !  ();

	bool 	  operator <  (const CNumber & n);
	bool 	  operator <= (const CNumber & n);
	bool 	  operator >  (const CNumber & n);
	bool 	  operator >= (const CNumber & n);
	bool 	  operator == (const CNumber & n);
	bool 	  operator != (const CNumber & n);

	bool 	  operator <  (double n);
	bool 	  operator <= (double n);
	bool 	  operator >  (double n);
	bool 	  operator >= (double n);
	bool 	  operator == (double n);
	bool 	  operator != (double n);


	virtual CNumber & operator  = (const CNumber & n);
	CNumber & operator  = (int n);
	CNumber & operator  = (const string & n);
	CNumber & operator  = (double n);
	CNumber & operator  = (float n);
	CNumber & operator += (const CNumber & n);
	CNumber & operator += (int n);
	CNumber & operator += (double n);

	CNumber & operator -= (const CNumber & n);
	CNumber & operator -= (double n);
	CNumber & operator -= (int n);

	CNumber & operator *= (const CNumber & n);
	CNumber & operator *= (int n);
	CNumber & operator *= (double n);

	CNumber & operator /= (const CNumber & n);
	CNumber & operator /= (int n);
	CNumber & operator /= (double n);
/*
	CNumber & operator %= (const CNumber & n);
	CNumber & operator %= (int n);
	CNumber & operator %= (double n);*/
	//CNumber & operator %= (const CNumber & n);
	//CNumber & operator ^= (const CNumber & n);
	//CNumber & operator |= (const CNumber & n);
	//CNumber & operator &= (const CNumber & n);

	virtual ~CNumber();
};

};

