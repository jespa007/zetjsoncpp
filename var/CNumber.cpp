#include "zetjsoncpp.h"

namespace zetjsoncpp {

double CNumber::parse(const string & str ){
	return CZetJsonCppUtils::fromString<double>(str);
}

CNumber::CNumber(){
	m_numVar = 0;
}

CNumber::CNumber(const CNumber& n){
	m_numVar = n.m_numVar;
}

CNumber::CNumber(int i){
	m_numVar = i;
}

CNumber::CNumber(unsigned i){
	m_numVar = i;
}


CNumber::CNumber(float f){
	m_numVar = f;
}

CNumber::CNumber(double d){
	m_numVar = d;
}




CNumber   CNumber::operator +  (const CNumber & n) const{
	CNumber n1;
	n1.m_numVar = m_numVar + n.m_numVar;
	return n1;
}

CNumber   CNumber::operator +  (double n) const {
	CNumber n1;
	n1.m_numVar = m_numVar + n;
	return n1;

}

CNumber   CNumber::operator +  (int n) const{
	CNumber n1;
	n1.m_numVar = m_numVar + n;
	return n1;

}


CNumber   CNumber::operator -  (const CNumber & n) const{
	CNumber n1;
	n1.m_numVar = m_numVar - n.m_numVar;
	return n1;
}

CNumber   CNumber::operator -  (){
	CNumber n1;
	n1.m_numVar = -m_numVar;
	return n1;
}


CNumber   CNumber::operator /  (const CNumber & n) const{
	CNumber n1;

	if(n.m_numVar ==0)
		throw ("Error divide by 0");

	n1.m_numVar = m_numVar / n.m_numVar;
	return n1;
}

CNumber & CNumber::operator  = (const CNumber & n){
	m_numVar = n.m_numVar;
	return (*this);
}

CNumber & CNumber::operator  = (int n){
	m_numVar = n;
	return (*this);
}

CNumber & CNumber::operator  = (double n){
	m_numVar = n;
	return (*this);
}

CNumber & CNumber::operator  = (float n){
	m_numVar = n;
	return (*this);
}

CNumber & CNumber::operator  = (const string & n){
	m_numVar = CNumber::parse(n);
	return (*this);
}

bool 	  CNumber::operator == (const CNumber & n){
	return m_numVar == n.m_numVar;
}

bool 	  CNumber::operator != (const CNumber & n){
	return m_numVar != n.m_numVar;
}

bool 	  CNumber::operator <  (const CNumber & n){
	return m_numVar < n.m_numVar;
}

bool 	  CNumber::operator <= (const CNumber & n){
	return m_numVar <= n.m_numVar;
}

bool 	  CNumber::operator >  (const CNumber & n){
	return m_numVar > n.m_numVar;
}

bool 	  CNumber::operator >= (const CNumber & n){
	return m_numVar >= n.m_numVar;
}

//---
bool 	  CNumber::operator == (double n){
	return m_numVar == n;
}

bool 	  CNumber::operator != (double n){
	return m_numVar != n;
}

bool 	  CNumber::operator <  (double n){
	return m_numVar < n;
}

bool 	  CNumber::operator <= (double n){
	return m_numVar <= n;
}

bool 	  CNumber::operator >  (double n){
	return m_numVar > n;
}

bool 	  CNumber::operator >= (double n){
	return m_numVar >= n;
}

//---

CNumber & CNumber::operator += (const CNumber & n){
	m_numVar += n.m_numVar;
	return (*this);
}

CNumber & CNumber::operator += (int n1){
	m_numVar += n1;
	return (*this);
}

CNumber & CNumber::operator += (double n1){
	m_numVar += n1;
	return (*this);
}

CNumber & CNumber::operator *= (const CNumber & n){
	m_numVar *= n.m_numVar;
	return (*this);
}

CNumber & CNumber::operator *= (int n1){
	m_numVar *= n1;
	return (*this);
}

CNumber & CNumber::operator *= (double n1){
	m_numVar *= n1;
	return (*this);
}


CNumber & CNumber::operator /= (const CNumber & n){
	if(n.m_numVar == 0)
		throw("Divide by 0!");

	m_numVar /= n.m_numVar;
	return (*this);
}

CNumber & CNumber::operator /= (int n1){

	if(n1 == 0)
		throw("Divide by 0!");
	m_numVar /= n1;
	return (*this);
}

CNumber & CNumber::operator /= (double n1){

	if(n1 == 0)
		throw("Divide by 0!");

	m_numVar /= n1;
	return (*this);
}



CNumber & CNumber::operator -= (const CNumber & n){
	m_numVar -= n.m_numVar;
	return (*this);
}

CNumber & CNumber::operator -= (int n1){
	m_numVar -= n1;
	return (*this);
}

CNumber & CNumber::operator -= (double n1){
	m_numVar -= n1;
	return (*this);
}


CNumber & CNumber::operator ++(){
	m_numVar++;
	return (*this);
}

const CNumber  CNumber::operator ++(int){
	CNumber n(m_numVar);
	operator++();
	return n;
}

CNumber::~CNumber(){

}

};
