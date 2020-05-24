
#include "zetjsoncpp.h"

namespace zetjsoncpp {

ZJ_Boolean::ZJ_Boolean(){
	m_boolVar = false;
}

ZJ_Boolean::ZJ_Boolean(const ZJ_Boolean& b){
	this->m_boolVar = b.m_boolVar;
}

ZJ_Boolean::ZJ_Boolean(bool b ){
	m_boolVar = b;
}

bool ZJ_Boolean::parse(const std::string & s){
	if(zj_string::toLower(s) == "true") return true;
	if(zj_string::toLower(s) == "false") return false;

	throw ("Cannot parse string to boolean.");
}

ZJ_Boolean &	ZJ_Boolean::operator = 	(const ZJ_Boolean & b){
	m_boolVar = b.m_boolVar;
	return (*this);
}

ZJ_Boolean &	ZJ_Boolean::operator = 	(bool b){
	m_boolVar = b;
	return (*this);
}

ZJ_Boolean &	ZJ_Boolean::operator = 	(const std::string & b){
	m_boolVar = parse(b);
	return (*this);
}


bool 		ZJ_Boolean::operator == (const ZJ_Boolean & b){
	return m_boolVar == b.m_boolVar;
}

bool 		ZJ_Boolean::operator && (const ZJ_Boolean & b){
	return m_boolVar && b.m_boolVar;
}

bool 		ZJ_Boolean::operator || (const ZJ_Boolean & b){
	return m_boolVar || b.m_boolVar;
}

bool 		ZJ_Boolean::operator != (const ZJ_Boolean & b){
	return m_boolVar != b.m_boolVar;
}

bool 		ZJ_Boolean::operator == (bool b){
	return m_boolVar == b;
}

bool 		ZJ_Boolean::operator && (bool b){
	return m_boolVar && b;
}

bool 		ZJ_Boolean::operator || (bool b){
	return m_boolVar || b;
}

bool 		ZJ_Boolean::operator != (bool b){
	return m_boolVar != b;
}

bool ZJ_Boolean::operator ! 	(){
	return !m_boolVar;
}



ZJ_Boolean::~ZJ_Boolean(){

}
};
