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


	virtual CString & operator =(const CString &);
	virtual CString & operator =(const string &);


	bool operator ==(const CString &) const;


	virtual ~CString();
};

};
