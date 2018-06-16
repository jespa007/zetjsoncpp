#pragma once


#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
namespace zetjsoncpp {

class CString{

	//---------------------------------------------------------------------------------------------
protected:
	string m_str;

public:

	CString();
	explicit CString(int );
	explicit CString(float );
	explicit CString(double );
	explicit CString(const char *);
	explicit CString(const string & );

	operator string(){return m_str;};

	CString operator +(const CString &) const;


	static CString   add(const CString & n1, const string & n2) {
		CString n;
		n.m_str = n1.m_str + n2;
		return n;
	}



	static CString   add(const string &  n1, const CString & n2) {
		CString n;
		n.m_str = n1 + n2.m_str;
		return n;
	}


	virtual CString & operator =(const CString &);
	virtual CString & operator =(const string &);


	bool operator ==(const CString &) const;


	virtual ~CString();
};

};
