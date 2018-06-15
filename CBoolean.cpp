
#include "zetjsoncpp.h"

namespace zetjsoncpp {

CBoolean::CBoolean(){
	m_boolVar = false;
}

CBoolean::CBoolean(const CBoolean& b){
	this->m_boolVar = b.m_boolVar;
}

CBoolean::CBoolean(bool b ){
	m_boolVar = b;
}

bool CBoolean::parse(const std::string & s){
	if(toLower(s) == "true") return true;
	if(toLower(s) == "false") return false;

	throw ("Cannot parse string to boolean.");
}

CBoolean &	CBoolean::operator = 	(const CBoolean & b){
	m_boolVar = b.m_boolVar;
	return (*this);
}

CBoolean &	CBoolean::operator = 	(bool b){
	m_boolVar = b;
	return (*this);
}

CBoolean &	CBoolean::operator = 	(const std::string & b){
	m_boolVar = parse(b);
	return (*this);
}


bool 		CBoolean::operator == (const CBoolean & b){
	return m_boolVar == b.m_boolVar;
}

bool 		CBoolean::operator && (const CBoolean & b){
	return m_boolVar && b.m_boolVar;
}

bool 		CBoolean::operator || (const CBoolean & b){
	return m_boolVar || b.m_boolVar;
}

bool 		CBoolean::operator != (const CBoolean & b){
	return m_boolVar != b.m_boolVar;
}

bool 		CBoolean::operator == (bool b){
	return m_boolVar == b;
}

bool 		CBoolean::operator && (bool b){
	return m_boolVar && b;
}

bool 		CBoolean::operator || (bool b){
	return m_boolVar || b;
}

bool 		CBoolean::operator != (bool b){
	return m_boolVar != b;
}

bool CBoolean::operator ! 	(){
	return !m_boolVar;
}



CBoolean::~CBoolean(){

}
};
