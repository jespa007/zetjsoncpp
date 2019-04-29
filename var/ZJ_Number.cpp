#include "zetjsoncpp.h"

namespace zetjsoncpp {

double ZJ_Number::parse(const string & str ){
	return CZetJsonCppUtils::fromString<double>(str);
}

ZJ_Number::ZJ_Number(){
	m_numVar = 0;
}

ZJ_Number::ZJ_Number(const ZJ_Number& n){
	m_numVar = n.m_numVar;
}

ZJ_Number::ZJ_Number(int i){
	m_numVar = i;
}

ZJ_Number::ZJ_Number(unsigned i){
	m_numVar = i;
}


ZJ_Number::ZJ_Number(float f){
	m_numVar = f;
}

ZJ_Number::ZJ_Number(double d){
	m_numVar = d;
}




ZJ_Number   ZJ_Number::operator +  (const ZJ_Number & n) const{
	ZJ_Number n1;
	n1.m_numVar = m_numVar + n.m_numVar;
	return n1;
}

ZJ_Number   ZJ_Number::operator +  (double n) const {
	ZJ_Number n1;
	n1.m_numVar = m_numVar + n;
	return n1;

}

ZJ_Number   ZJ_Number::operator +  (int n) const{
	ZJ_Number n1;
	n1.m_numVar = m_numVar + n;
	return n1;

}


ZJ_Number   ZJ_Number::operator -  (const ZJ_Number & n) const{
	ZJ_Number n1;
	n1.m_numVar = m_numVar - n.m_numVar;
	return n1;
}

ZJ_Number   ZJ_Number::operator -  (){
	ZJ_Number n1;
	n1.m_numVar = -m_numVar;
	return n1;
}


ZJ_Number   ZJ_Number::operator /  (const ZJ_Number & n) const{
	ZJ_Number n1;

	if(n.m_numVar ==0)
		throw ("Error divide by 0");

	n1.m_numVar = m_numVar / n.m_numVar;
	return n1;
}

ZJ_Number & ZJ_Number::operator  = (const ZJ_Number & n){
	m_numVar = n.m_numVar;
	return (*this);
}

ZJ_Number & ZJ_Number::operator  = (int n){
	m_numVar = n;
	return (*this);
}

ZJ_Number & ZJ_Number::operator  = (double n){
	m_numVar = n;
	return (*this);
}

ZJ_Number & ZJ_Number::operator  = (float n){
	m_numVar = n;
	return (*this);
}

ZJ_Number & ZJ_Number::operator  = (const string & n){
	m_numVar = ZJ_Number::parse(n);
	return (*this);
}

bool 	  ZJ_Number::operator == (const ZJ_Number & n){
	return m_numVar == n.m_numVar;
}

bool 	  ZJ_Number::operator != (const ZJ_Number & n){
	return m_numVar != n.m_numVar;
}

bool 	  ZJ_Number::operator <  (const ZJ_Number & n){
	return m_numVar < n.m_numVar;
}

bool 	  ZJ_Number::operator <= (const ZJ_Number & n){
	return m_numVar <= n.m_numVar;
}

bool 	  ZJ_Number::operator >  (const ZJ_Number & n){
	return m_numVar > n.m_numVar;
}

bool 	  ZJ_Number::operator >= (const ZJ_Number & n){
	return m_numVar >= n.m_numVar;
}

//---
bool 	  ZJ_Number::operator == (double n){
	return m_numVar == n;
}

bool 	  ZJ_Number::operator != (double n){
	return m_numVar != n;
}

bool 	  ZJ_Number::operator <  (double n){
	return m_numVar < n;
}

bool 	  ZJ_Number::operator <= (double n){
	return m_numVar <= n;
}

bool 	  ZJ_Number::operator >  (double n){
	return m_numVar > n;
}

bool 	  ZJ_Number::operator >= (double n){
	return m_numVar >= n;
}

//---

ZJ_Number & ZJ_Number::operator += (const ZJ_Number & n){
	m_numVar += n.m_numVar;
	return (*this);
}

ZJ_Number & ZJ_Number::operator += (int n1){
	m_numVar += n1;
	return (*this);
}

ZJ_Number & ZJ_Number::operator += (double n1){
	m_numVar += n1;
	return (*this);
}

ZJ_Number & ZJ_Number::operator *= (const ZJ_Number & n){
	m_numVar *= n.m_numVar;
	return (*this);
}

ZJ_Number & ZJ_Number::operator *= (int n1){
	m_numVar *= n1;
	return (*this);
}

ZJ_Number & ZJ_Number::operator *= (double n1){
	m_numVar *= n1;
	return (*this);
}


ZJ_Number & ZJ_Number::operator /= (const ZJ_Number & n){
	if(n.m_numVar == 0)
		throw("Divide by 0!");

	m_numVar /= n.m_numVar;
	return (*this);
}

ZJ_Number & ZJ_Number::operator /= (int n1){

	if(n1 == 0)
		throw("Divide by 0!");
	m_numVar /= n1;
	return (*this);
}

ZJ_Number & ZJ_Number::operator /= (double n1){

	if(n1 == 0)
		throw("Divide by 0!");

	m_numVar /= n1;
	return (*this);
}



ZJ_Number & ZJ_Number::operator -= (const ZJ_Number & n){
	m_numVar -= n.m_numVar;
	return (*this);
}

ZJ_Number & ZJ_Number::operator -= (int n1){
	m_numVar -= n1;
	return (*this);
}

ZJ_Number & ZJ_Number::operator -= (double n1){
	m_numVar -= n1;
	return (*this);
}


ZJ_Number & ZJ_Number::operator ++(){
	m_numVar++;
	return (*this);
}

const ZJ_Number  ZJ_Number::operator ++(int){
	ZJ_Number n(m_numVar);
	operator++();
	return n;
}

ZJ_Number::~ZJ_Number(){

}

};
