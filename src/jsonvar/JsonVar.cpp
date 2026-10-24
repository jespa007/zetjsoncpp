/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp {

	char const	JsonVar::STR_EMPTY[] = "empty";

	const char *JsonVar::idTypeToString(int index) {
		switch (index) {
		default:
		case JSON_VAR_TYPE_UNKNOWN:
			break;
		case JSON_VAR_TYPE_BOOLEAN: return "BooleanJsonVar";
			//case INT32_TYPE: return "INT32_TYPE";
		case JSON_VAR_TYPE_NUMBER: return "NumberJsonVar";
		case JSON_VAR_TYPE_STRING: return "StringJsonVar";
		case JSON_VAR_TYPE_OBJECT: return "ObjectJsonVar";

		case JSON_VAR_TYPE_ARRAY_OF_BOOLEANS: return "ArrayBooleanJsonVar";
			//case ARRAY_INT32_TYPE: return "ARRAY INT32 TYPE";
		case JSON_VAR_TYPE_ARRAY_OF_NUMBERS: return "ArrayNumberJsonVar";
		case JSON_VAR_TYPE_ARRAY_OF_STRINGS: return "ArrayStringJsonVar";
		case JSON_VAR_TYPE_ARRAY_OF_OBJECTS: return "ArrayObjectJsonVar";

		case JSON_VAR_TYPE_MAP_OF_BOOLEANS: return "MapBooleanJsonVar";
		case JSON_VAR_TYPE_MAP_OF_NUMBERS: return "MapNumberJsonVar";
		case JSON_VAR_TYPE_MAP_OF_STRINGS: return "MapStringJsonVar";
		case JSON_VAR_TYPE_MAP_OF_OBJECTS: return "MapObjectJsonVar";
		}

		return "UNKNOWN";
	}

	JsonVar::JsonVar(
	   const char *_name
	   ,JsonVarType _type
	){

		this->_name = _name;
		this->_type = _type;
		this->_is_deserialized = false;
	}


	JsonVar *JsonVar::newJsonVar(){
		throw std::runtime_error("internal error: newJsonVar not implemented");
		return NULL;
	}

	JsonVar *JsonVar::newJsonVar(const std::string & key){
		ZJ_UNUSUED_PARAM(key);
		throw std::runtime_error("internal error: newJsonVar not implemented");
	}

	const char *JsonVar::getTypeStr(){
		return idTypeToString(this->_type);
	}

	void JsonVar::setParsed(bool parsed) {
		this->_is_deserialized = parsed;
	}

	bool JsonVar::isDeserialized() const {
		return this->_is_deserialized;
	}

	void JsonVar::forEachField(
	    FieldCallback _callback
	    ,void *_context
	) {
	    // Primitive types have no fields
	}

	void JsonVar::forEachField(
	    ConstFieldCallback _callback
	    ,void *_context
	) const {
	    // Primitive types have no fields
	}

	JsonVar::~JsonVar(){

	}

}

