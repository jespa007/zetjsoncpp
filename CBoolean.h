#pragma once

namespace zetjsoncpp {

class CBoolean{//:public CVariable{
protected:
	bool m_boolVar;
public:

	CBoolean();
	explicit CBoolean(const CBoolean&);
	explicit CBoolean(bool b);
	static bool parse(const std::string & s);


	virtual CBoolean & operator = 	(const CBoolean & b);
	virtual CBoolean & operator = 	(bool  b);
	virtual CBoolean & operator = 	(const std::string & );



	bool operator == 		(const CBoolean & b);
	bool operator && 		(const CBoolean & b);
	bool operator || 		(const CBoolean & b);
	bool operator != 		(const CBoolean & b);

	bool operator == 		(bool b);
	bool operator && 		(bool b);
	bool operator || 		(bool b);
	bool operator != 		(bool b);


	bool operator ! 		();
	operator bool() const {
		return m_boolVar;
	}

	virtual ~CBoolean();

};

};
