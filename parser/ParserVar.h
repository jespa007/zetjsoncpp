/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once

#define N_ELEMENTS_JSON_ARRAY_PRINT	10

#define JS_STRING_CAST 		(String<> *)
#define JS_ARRAY_STRING_CAST 	(StringArray<> *)
#define JS_BOOL_CAST 		(Boolean<> *)
#define JS_FLOAT_CAST 		(Number<> *)


#if  !defined(MIN)
#define  MIN(a,  b)              ((a)  <  (b)  ?  (a)  :  (b))
#endif

#define JS_MAX_CONST_CHAR 50

#define ZJ_CONST_CHAR(s)\
	getChr(s,0),\
	getChr(s,1),\
	getChr(s,2),\
	getChr(s,3),\
	getChr(s,4),\
	getChr(s,5),\
	getChr(s,6),\
	getChr(s,7),\
	getChr(s,8),\
	getChr(s,9),\
	getChr(s,10),\
	getChr(s,11),\
	getChr(s,12),\
	getChr(s,13),\
	getChr(s,14),\
	getChr(s,15),\
	getChr(s,16),\
	getChr(s,17),\
	getChr(s,18),\
	getChr(s,19),\
	getChr(s,20),\
	getChr(s,21),\
	getChr(s,22),\
	getChr(s,23),\
	getChr(s,24),\
	getChr(s,25),\
	getChr(s,26),\
	getChr(s,27),\
	getChr(s,28),\
	getChr(s,29),\
	getChr(s,30),\
	getChr(s,31),\
	getChr(s,32),\
	getChr(s,33),\
	getChr(s,34),\
	getChr(s,35),\
	getChr(s,36),\
	getChr(s,37),\
	getChr(s,38),\
	getChr(s,39),\
	getChr(s,40),\
	getChr(s,41),\
	getChr(s,42),\
	getChr(s,43),\
	getChr(s,44),\
	getChr(s,45),\
	getChr(s,46),\
	getChr(s,47),\
	getChr(s,48),\
	getChr(s,49),\
	getChr(s,50)

#define getChr(name, ii) ((MIN(ii,JS_MAX_CONST_CHAR))<sizeof(name)/sizeof(*name)?name[ii]:0)


namespace zetjsoncpp {

	class CParserVar {//: public CVariable {
	protected:
		std::string result_json;
		std::string str_value;
		bool m_isParsed;

	public:

		enum {
			TYPE_UNKNOWN = 0, // 0
			TYPE_BOOL, // 1
			TYPE_NUMBER,// 2
			TYPE_STRING, // 3
			TYPE_PROPERTY_GROUP,
			TYPE_ARRAY = 0x100,
			TYPE_ARRAY_BOOL = TYPE_BOOL + TYPE_ARRAY, // 6
			TYPE_ARRAY_NUMBER = TYPE_NUMBER + TYPE_ARRAY, // 7
			TYPE_ARRAY_STRING = TYPE_STRING + TYPE_ARRAY, // 9
			TYPE_ARRAY_PROPERTY_GROUP = TYPE_PROPERTY_GROUP + TYPE_ARRAY
		};

		enum {
			PROPERTY_STR_MINIMIZED = 0x1 << 0
		};


		static const char *idTypeToString(int index);

		static char const STR_EMPTY[];
		int _m_iType;
		int size_data;
		std::string  _m_pvariableName;
		CParserVar *p_ini_data;
		void 	     *p_data; // can be int, bool, vector, prop_grp, etc ...
		CParserVar *p_end_data;
		//_T_NAME name;

		CParserVar();

		virtual std::string & cpp2json();

		virtual CParserVar * newData();

		virtual std::string & getStrValue(int ident, uint32_t flags);

		virtual void add(CParserVar * s);

		virtual ~CParserVar();

		void setParsed(bool parsed);

		bool isParsed() const;
	};



};

#include "ParserVarNamed.h"
#include "Boolean.h"
#include "Number.h"
#include "String.h"
#include "PropertyGroup.h"
#include "Array.h"
#include "CParserVarBoolArray.h"
#include "NumberArray.h"
#include "StringArray.h"
#include "ParserVarPropertyGroupArray.h"
