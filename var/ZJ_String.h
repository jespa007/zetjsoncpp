#pragma once


#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
namespace zetjsoncpp {

class ZJ_String{

	//---------------------------------------------------------------------------------------------
protected:
	std::string m_str;

public:

	ZJ_String();
	explicit ZJ_String(int );
	explicit ZJ_String(float );
	explicit ZJ_String(double );
	explicit ZJ_String(const char *);
	explicit ZJ_String(const string & );

	operator std::string(){return m_str;};

	ZJ_String operator +(const ZJ_String &) const;


	virtual ZJ_String & operator =(const ZJ_String &);
	virtual ZJ_String & operator =(const std::string &);


	bool operator ==(const ZJ_String &) const;


	virtual ~ZJ_String();
};

};
