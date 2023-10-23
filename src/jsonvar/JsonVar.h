/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once

#if  !defined(ZJ_MIN)
#define  ZJ_MIN(a,  b)              ((a)  <  (b)  ?  (a)  :  (b))
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

#define getChr(name, ii) ((ZJ_MIN(ii,ZJ_MAX_CONST_CHAR))<sizeof(name)/sizeof(*name)?name[ii]:0)

#define ZJ_CAST_JSON_VAR_STRING 				(zetjsoncpp::StringJsonVar<> *)
#define ZJ_CAST_JSON_VAR_BOOLEAN 				(zetjsoncpp::BooleanJsonVar<> *)
#define ZJ_CAST_JSON_VAR_NUMBER 				(zetjsoncpp::NumberJsonVar<> *)
#define ZJ_CAST_JSON_VAR_OBJECT 				(zetjsoncpp::ObjectJsonVar<> *)
#define ZJ_CAST_JSON_VAR_ARRAY_OF_BOOLEANS 	(zetjsoncpp::ArrayBooleanJsonVar<> *)
#define ZJ_CAST_JSON_VAR_ARRAY_OF_NUMBERS 		(zetjsoncpp::ArrayNumberJsonVar<> *)
#define ZJ_CAST_JSON_VAR_ARRAY_OF_STRINGS 		(zetjsoncpp::ArrayStringJsonVar<> *)
#define ZJ_CAST_JSON_VAR_ARRAY_OF_OBJECTS 		(zetjsoncpp::ArrayObjectJsonVar<> *)
#define ZJ_CAST_JSON_VAR_MAP_OF_BOOLEANS 		(zetjsoncpp::MapBooleanJsonVar<> *)
#define ZJ_CAST_JSON_VAR_MAP_OF_NUMBERS 		(zetjsoncpp::MapNumberJsonVar<> *)
#define ZJ_CAST_JSON_VAR_MAP_OF_STRINGS 		(zetjsoncpp::MapStringJsonVar<> *)
#define ZJ_CAST_JSON_VAR_MAP_OF_OBJECTS 		(zetjsoncpp::MapObjectJsonVar<> *)

#define ZJ_VAR_BOOLEAN(name) zetjsoncpp::BooleanJsonVar<ZJ_CONST_CHAR(#name)>						name
#define ZJ_VAR_NUMBER(name) zetjsoncpp::NumberJsonVar<ZJ_CONST_CHAR(#name)>							name
#define ZJ_VAR_STRING(name) zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR(#name)>							name
#define ZJ_VAR_OBJECT(type,name) zetjsoncpp::ObjectJsonVar<type,ZJ_CONST_CHAR(#name)>				name

#define ZJ_VAR_ARRAY_BOOLEAN(name) zetjsoncpp::ArrayBooleanJsonVar<ZJ_CONST_CHAR(#name)>			name
#define ZJ_VAR_ARRAY_NUMBER(name) zetjsoncpp::ArrayNumberJsonVar<ZJ_CONST_CHAR(#name)>			name
#define ZJ_VAR_ARRAY_STRING(name) zetjsoncpp::ArrayStringJsonVar<ZJ_CONST_CHAR(#name)>			name
#define ZJ_VAR_ARRAY_OBJECT(type,name) zetjsoncpp::ArrayObjectJsonVar<type,ZJ_CONST_CHAR(#name)>	name

#define ZJ_VAR_MAP_BOOLEAN(name) zetjsoncpp::MapBooleanJsonVar<ZJ_CONST_CHAR(#name)>				name
#define ZJ_VAR_MAP_NUMBER(name) zetjsoncpp::MapNumberJsonVar<ZJ_CONST_CHAR(#name)>					name
#define ZJ_VAR_MAP_STRING(name) zetjsoncpp::MapStringJsonVar<ZJ_CONST_CHAR(#name)>					name
#define ZJ_VAR_MAP_OBJECT(type,name) zetjsoncpp::MapObjectJsonVar<type,ZJ_CONST_CHAR(#name)>		name


namespace zetjsoncpp {

	typedef enum:uint16_t{
		JSON_VAR_TYPE_UNKNOWN		 =0, // 0
		JSON_VAR_TYPE_BOOLEAN		 =0x1<<1, // 0x01
		JSON_VAR_TYPE_NUMBER		 =0x1<<2, // 0x02
		JSON_VAR_TYPE_STRING		 =0x1<<3, // 0x03
		JSON_VAR_TYPE_OBJECT		 =0x1<<4, // 0x04
		JSON_VAR_TYPE_ARRAY 		= 0x100,  //
		JSON_VAR_TYPE_ARRAY_OF_BOOLEANS = JSON_VAR_TYPE_ARRAY+JSON_VAR_TYPE_BOOLEAN, // 6
		JSON_VAR_TYPE_ARRAY_OF_NUMBERS = JSON_VAR_TYPE_ARRAY+JSON_VAR_TYPE_NUMBER, // 7
		JSON_VAR_TYPE_ARRAY_OF_STRINGS =JSON_VAR_TYPE_ARRAY+JSON_VAR_TYPE_STRING, // 9
		JSON_VAR_TYPE_ARRAY_OF_OBJECTS = JSON_VAR_TYPE_ARRAY+JSON_VAR_TYPE_OBJECT, //10
		JSON_VAR_TYPE_MAP=0x200,
		JSON_VAR_TYPE_MAP_OF_BOOLEANS = JSON_VAR_TYPE_MAP+JSON_VAR_TYPE_BOOLEAN, // 12
		JSON_VAR_TYPE_MAP_OF_NUMBERS = JSON_VAR_TYPE_MAP+JSON_VAR_TYPE_NUMBER, // 13
		JSON_VAR_TYPE_MAP_OF_STRINGS = JSON_VAR_TYPE_MAP+JSON_VAR_TYPE_STRING, // 14
		JSON_VAR_TYPE_MAP_OF_OBJECTS = JSON_VAR_TYPE_MAP+JSON_VAR_TYPE_OBJECT, // 15
		JSON_VAR_TYPE_MAP_OF_ARRAY_OF_STRINGS = JSON_VAR_TYPE_MAP+JSON_VAR_TYPE_ARRAY_OF_STRINGS, // 16

	}JsonVarType;

	class JsonVar {//: public CVariable {
	public:

		static const char *idTypeToString(int index);

		static char const STR_EMPTY[];

		JsonVar();

		// It create a new json var slot for vector container.
		virtual JsonVar *newJsonVar();
		// It create a new json var slot for map container.
		virtual JsonVar *newJsonVar(const std::string & key);


		const char *getTypeStr();

		virtual ~JsonVar();

		void * getPtrDataStart(){ return __zj_ptr_data_start__;}
		virtual void * getPtrValue(){ return NULL;}


		void * getPtrDataEnd(){return __zj_ptr_data_end__;}
		size_t  getSizeData(){return __zj_size_data__;}
		JsonVarType getType(){return __zj_type__;}
		std::string getVariableName(){return __zj_variable_name__;}

		void setParsed(bool parsed);
		void setFileLineDebug(const char *__file__, int __line__);

		bool isDeserialized() const;

	protected:
		bool __zj_is_parsed__;
		JsonVarType __zj_type__;
		size_t __zj_size_data__;
		char  __zj_variable_name__[ZJ_MAX_CONST_CHAR+1];
		void 	     *__zj_ptr_data_start__; // can be int, bool, vector, prop_grp, etc ...
		JsonVar *__zj_ptr_data_end__;
	};



}

#include "NamedJsonVar.h"
#include "BooleanJsonVar.h"
#include "NumberJsonVar.h"
#include "StringJsonVar.h"
#include "ObjectJsonVar.h"
#include "ArrayJsonVar.h"
#include "ArrayBooleanJsonVar.h"
#include "ArrayNumberJsonVar.h"
#include "ArrayStringJsonVar.h"
#include "ArrayObjectJsonVar.h"
#include "MapJsonVar.h"
#include "MapBooleanJsonVar.h"
#include "MapNumberJsonVar.h"
#include "MapStringJsonVar.h"
#include "MapObjectJsonVar.h"
#include "MapArrayStringJsonVar.h"


