#include "zetjsoncpp.h"


namespace zetjsoncpp {


//-----------------------------------------------------------------------------------------------------------------------
CString::CString(){
	m_str = "";
}

CString::CString(const string &  str){
	m_str = str;
}

CString::CString(const char * str){
	m_str = str;
}

CString::CString(int i){
	m_str = intToString(i);
}

CString::CString(float f){
	m_str = floatToString(f);
}

CString CString::operator +(const CString & param)  const {
	CString ss;
	ss.m_str = this->m_str + param.m_str;

	return ss;
}


CString & CString::operator =(const CString & str){
	this->m_str = str.m_str;

	return (*this);
}

CString & CString::operator =(const string & str){
	this->m_str = str;

	return (*this);
}

bool CString::operator ==(const CString & pp_str) const{
	return this->m_str == pp_str.m_str;

}

CString::~CString(){

}
};
