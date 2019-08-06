#pragma once
namespace zetjsoncpp {

class ZJ_Number{//:public CVariable{
protected:

public:
	double m_numVar;

	static double parse(const std::string & str );
	ZJ_Number();
	ZJ_Number(const ZJ_Number&);
	ZJ_Number(int );
	ZJ_Number(unsigned );
	ZJ_Number(float );
	ZJ_Number(double );

	//operator int();
	//operator float();
	//operator double();
	operator int() const {
		return m_numVar;
	}
	operator double() const {
		return m_numVar;
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

	void set(double n){
		this->m_numVar = n;
	}

	ZJ_Number   operator +  (const ZJ_Number & n) const;
	ZJ_Number   operator +  (double n) const;
	ZJ_Number   operator +  (int n) const;

	//----
	// friend functions ...
	//---

	// prefix operator
	ZJ_Number & operator ++ ();

	// postfix operator
	const ZJ_Number operator ++ (int);



	ZJ_Number   operator -  (const ZJ_Number & n) const;
	ZJ_Number   operator -  ();


	ZJ_Number   operator /  (const ZJ_Number & n) const;


	bool 	  operator <  (const ZJ_Number & n);
	bool 	  operator <= (const ZJ_Number & n);
	bool 	  operator >  (const ZJ_Number & n);
	bool 	  operator >= (const ZJ_Number & n);
	bool 	  operator == (const ZJ_Number & n);
	bool 	  operator != (const ZJ_Number & n);

	bool 	  operator <  (double n);
	bool 	  operator <= (double n);
	bool 	  operator >  (double n);
	bool 	  operator >= (double n);
	bool 	  operator == (double n);
	bool 	  operator != (double n);


	virtual ZJ_Number & operator  = (const ZJ_Number & n);
	ZJ_Number & operator  = (int n);
	ZJ_Number & operator  = (const std::string & n);
	ZJ_Number & operator  = (double n);
	ZJ_Number & operator  = (float n);
	ZJ_Number & operator += (const ZJ_Number & n);
	ZJ_Number & operator += (int n);
	ZJ_Number & operator += (double n);

	ZJ_Number & operator -= (const ZJ_Number & n);
	ZJ_Number & operator -= (double n);
	ZJ_Number & operator -= (int n);

	ZJ_Number & operator *= (const ZJ_Number & n);
	ZJ_Number & operator *= (int n);
	ZJ_Number & operator *= (double n);

	ZJ_Number & operator /= (const ZJ_Number & n);
	ZJ_Number & operator /= (int n);
	ZJ_Number & operator /= (double n);

	virtual ~ZJ_Number();
};

};

