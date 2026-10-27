/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once

#if  !defined(ZJ_MIN)
#define  ZJ_MIN(a,  b)              ((a)  <  (b)  ?  (a)  :  (b))
#endif


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

	class JsonVar;

    typedef void (*FieldCallback)(
        JsonVar *
        ,void *
    );

    typedef void (*ConstFieldCallback)(
        const JsonVar *
        ,void *
    );

	class JsonVar {//: public CVariable {
	public:

		static const char *idTypeToString(int index);

		static char const STR_EMPTY[];

		explicit JsonVar(
			const char *_name = ""
			,JsonVarType _type = JsonVarType::JSON_VAR_TYPE_UNKNOWN
		);

		JsonVar(const JsonVar &_other) = default;
		JsonVar &operator=(const JsonVar &_other) = default;

		// It create a new json var slot for vector container.
		virtual JsonVar *newJsonVar();
		// It create a new json var slot for map container.
		virtual JsonVar *newJsonVar(const std::string & key);


		const char *getTypeStr();

		virtual void * getPtrValue(){ return NULL;}
		JsonVarType getType(){return this->_type;}
		std::string getVariableName() const {return this->_name;}
		const char * getVariableNameCStr() const {return this->_name;}
		void setVariableName(const char * _name){ this->_name = _name;}

		void setParsed(bool parsed);
		void setFileLineDebug(const char *__file__, int __line__);

		bool isDeserialized() const;

	    // Mutable field visitation
	    virtual void forEachField(
	        FieldCallback _callback
	        ,void *_context
	    );

	    // Read-only field visitation
	    virtual void forEachField(
	        ConstFieldCallback _callback
	        ,void *_context
	    ) const;

		virtual ~JsonVar();

	protected:
		bool _is_deserialized;
		JsonVarType _type;
		const char *_name;



	};



}

#include "JsonSchema.h"
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


