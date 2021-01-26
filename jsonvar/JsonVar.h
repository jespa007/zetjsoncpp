/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once

#define N_ELEMENTS_JSON_VECTOR_PRINT	10


#if  !defined(MIN)
#define  MIN(a,  b)              ((a)  <  (b)  ?  (a)  :  (b))
#endif

#define ZJ_MAX_CONST_CHAR 50

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

#define getChr(name, ii) ((MIN(ii,ZJ_MAX_CONST_CHAR))<sizeof(name)/sizeof(*name)?name[ii]:0)

#define JSON_VAR_STRING_CAST 			(zetjsoncpp::JsonVarString<> *)
#define JSON_VAR_BOOLEAN_CAST 			(zetjsoncpp::JsonVarBoolean<> *)
#define JSON_VAR_NUMBER_CAST 			(zetjsoncpp::JsonVarNumber<> *)
#define JSON_VAR_VECTOR_BOOLEAN_CAST 	(zetjsoncpp::JsonVarVectorBoolean<> *)
#define JSON_VAR_VECTOR_NUMBER_CAST 	(zetjsoncpp::ArrayNumber<> *)
#define JSON_VAR_VECTOR_STRING_CAST 	(zetjsoncpp::JsonVarVectorString<> *)
#define JSON_VAR_MAP_STRING_CAST 		(zetjsoncpp::JsonVarMapString<> *)

namespace zetjsoncpp {

	class JsonVar {//: public CVariable {
	protected:
		std::string result_json;
		std::string str_value;
		bool is_parsed;

	public:

		typedef enum {
			JSON_VAR_TYPE_UNKNOWN = 0, // 0
			JSON_VAR_TYPE_BOOLEAN, // 1
			JSON_VAR_TYPE_NUMBER,// 2
			JSON_VAR_TYPE_STRING, // 3
			JSON_VAR_TYPE_OBJECT, // 4
			JSON_VAR_TYPE_VECTOR = 0x100,
			JSON_VAR_TYPE_VECTOR_BOOLEAN = JSON_VAR_TYPE_BOOLEAN + JSON_VAR_TYPE_VECTOR, // 6
			JSON_VAR_TYPE_VECTOR_NUMBER = JSON_VAR_TYPE_NUMBER + JSON_VAR_TYPE_VECTOR, // 7
			JSON_VAR_TYPE_VECTOR_STRING =JSON_VAR_TYPE_STRING + JSON_VAR_TYPE_VECTOR, // 9
			JSON_VAR_TYPE_VECTOR_OBJECT = JSON_VAR_TYPE_OBJECT + JSON_VAR_TYPE_VECTOR, //10
			JSON_VAR_TYPE_MAP=0x200,
			JSON_VAR_TYPE_MAP_STRING = JSON_VAR_TYPE_STRING + JSON_VAR_TYPE_MAP // 12

		}JsonVarType;

		enum {
			PROPERTY_STR_MINIMIZED = 0x1 << 0
		};


		static const char *idTypeToString(int index);

		static char const STR_EMPTY[];
		JsonVarType type;
		int size_data;
		std::string  variable_name;
		JsonVar *p_ini_data;
		void 	     *p_data; // can be int, bool, vector, prop_grp, etc ...
		JsonVar *p_end_data;
		//_T_NAME name;

		JsonVar();

		virtual std::string & toString();

		virtual JsonVar * newData();

		virtual std::string & getStrValue(int ident, uint32_t flags);

		virtual void add(JsonVar * s);

		virtual ~JsonVar();

		void setParsed(bool parsed);

		bool isParsed() const;
	};



};

#include "JsonVarNamed.h"
#include "JsonVarBoolean.h"
#include "JsonVarNumber.h"
#include "JsonVarString.h"
#include "JsonVarObject.h"
#include "JsonVarVector.h"
#include "JsonVarVectorBoolean.h"
#include "JsonVarVectorNumber.h"
#include "JsonVarVectorString.h"
#include "JsonVarVectorObject.h"
#include "JsonVarMap.h"
#include "JsonVarMapString.h"

