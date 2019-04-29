#pragma once

namespace zetjsoncpp {

class ZJ_Boolean{//:public CVariable{
protected:
	bool m_boolVar;
public:

	ZJ_Boolean();
	explicit ZJ_Boolean(const ZJ_Boolean&);
	explicit ZJ_Boolean(bool b);
	static bool parse(const std::string & s);


	virtual ZJ_Boolean & operator = 	(const ZJ_Boolean & b);
	virtual ZJ_Boolean & operator = 	(bool  b);
	virtual ZJ_Boolean & operator = 	(const std::string & );



	bool operator == 		(const ZJ_Boolean & b);
	bool operator && 		(const ZJ_Boolean & b);
	bool operator || 		(const ZJ_Boolean & b);
	bool operator != 		(const ZJ_Boolean & b);

	bool operator == 		(bool b);
	bool operator && 		(bool b);
	bool operator || 		(bool b);
	bool operator != 		(bool b);


	bool operator ! 		();
	operator bool() const {
		return m_boolVar;
	}

	virtual ~ZJ_Boolean();

};

};
