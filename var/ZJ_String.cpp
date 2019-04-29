#include "zetjsoncpp.h"


namespace zetjsoncpp {


//-----------------------------------------------------------------------------------------------------------------------
ZJ_String::ZJ_String(){
	m_str = "";
}

ZJ_String::ZJ_String(const string &  str){
	m_str = str;
}

ZJ_String::ZJ_String(const char * str){
	m_str = str;
}

ZJ_String::ZJ_String(int i){
	m_str = CZetJsonCppUtils::intToString(i);
}

ZJ_String::ZJ_String(float f){
	m_str = CZetJsonCppUtils::floatToString(f);
}

ZJ_String ZJ_String::operator +(const ZJ_String & param)  const {
	ZJ_String ss;
	ss.m_str = this->m_str + param.m_str;

	return ss;
}


ZJ_String & ZJ_String::operator =(const ZJ_String & str){
	this->m_str = str.m_str;

	return (*this);
}

ZJ_String & ZJ_String::operator =(const string & str){
	this->m_str = str;

	return (*this);
}

bool ZJ_String::operator ==(const ZJ_String & pp_str) const{
	return this->m_str == pp_str.m_str;

}

ZJ_String::~ZJ_String(){

}
};
