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
	//---

	// prefix operator
	CNumber & operator ++ ();

	// postfix operator
	const CNumber operator ++ (int);



	CNumber   operator -  (const CNumber & n) const;
	CNumber   operator -  ();


	CNumber   operator /  (const CNumber & n) const;


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

	virtual ~CNumber();
};

};

