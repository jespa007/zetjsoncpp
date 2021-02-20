/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "zetjsoncpp.h"

namespace zetjsoncpp{

/*
		// MAP NUMBERS
		virtual std::string serializeFormatted(int ident, uint16_t properties){

			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toJsonFormattedStart(ident, properties);

			int j=0;
			for (auto it=__zj_map_data__.begin();it !=__zj_map_data__.end();it++,j++) {

				if (j > 0){
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}
					str_value += ",";
				}

				str_value += "\""+it->first +"\":"+ zj_strutils::float_to_str(it->second)+"";// this->str_value + "\"" + v->at(j) + "\" ";
			}

			str_value += this->toJsonFormattedEnd(ident,properties);

			return str_value;

		}

	// MAP BOOLEAN
		virtual std::string serializeFormatted(int ident, uint16_t properties) {

			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toJsonFormattedStart(ident, properties);

			int j=0;
			for (auto it=__zj_map_data__.begin();it !=__zj_map_data__.end();it++,j++) {

				if (j > 0){
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}
					str_value += ",";
				}

				str_value += "\""+it->first +"\":"+ (it->second==true?"true":"false")+"";// this->str_value + "\"" + v->at(j) + "\" ";

			}

			str_value += this->toJsonFormattedEnd(ident,properties);

			return str_value;

		}

	// MAP STRING
		virtual std::string serializeFormatted(int ident, uint16_t properties) {

			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toJsonFormattedStart(ident, properties);

			int j=0;
			for (auto it=__zj_map_data__.begin();it !=__zj_map_data__.end();it++,j++) {

				if (j > 0){
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}

					str_value = str_value + ",";
				}

				str_value += "\""+it->first +"\":\""+it->second+"\"";// str_value + "\"" + v->at(j) + "\" ";
			}

			str_value += this->toJsonFormattedEnd(ident,properties);

			return str_value;
		}
		 // MAP OBJECTS
		virtual std::string serializeFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toJsonFormattedStart(ident, properties);

			int j=0;
			for (auto it=this->__zj_map_data__.begin(); it != this->__zj_map_data__.end(); it++,j++) {
				if (j > 0) {
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}
					str_value += ",";
				}

				str_value+="\""+it->first +"\":";


				objectToString(it->second, str_value, ident+1, properties);

			}

			str_value += this->toJsonFormattedEnd(ident,properties);

			return str_value;
		}

// VECTOR NUMBER

		virtual std::string serializeFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::vector<JsonVarNumber<>> * v = (std::vector<JsonVarNumber<>> *)this->__zj_ptr_data_start__;
			std::string str_value = "";

			str_value+=toJsonFormattedStart(ident,properties);

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					if (not_minimized) {
						ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident+1,j);
					}
					str_value += ",";
				}

				str_value += v->at(j).serialize();

			}

			str_value+=toJsonFormattedEnd(ident,properties);

			return str_value;
		}


// VECTOR BOOLEAN

		virtual std::string serializeFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED & properties) == 0);
			std::vector<JsonVarBoolean<>> * v = (std::vector<JsonVarBoolean<>> *)this->__zj_ptr_data_start__;
			std::string str_value = "";

			str_value+=toJsonFormattedStart(ident,properties);

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					if (not_minimized) {
						ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident+1,j);
					}
					str_value += ",";
				}

				str_value += (v->at(j) == true?"true":"false");

			}

			str_value+=toJsonFormattedEnd(ident,properties);

			return str_value;
		}

// VECTOR STRING
		virtual std::string serializeFormatted(int ident, uint16_t properties = 0) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = "";
			std::vector<JsonVarString<>> * v = (std::vector<JsonVarString<>> *)this->__zj_ptr_data_start__;

			str_value+=toJsonFormattedStart(ident,properties);

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					if (not_minimized) {
						ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident+1,j);
					}
					str_value += ",";
				}

				str_value += "\"" + v->at(j) + "\"";

			}

			str_value+=toJsonFormattedEnd(ident,properties);

			return str_value;
		}

		// VECTOR OBJECTS
		virtual std::string serializeFormatted(int ident, uint16_t properties) {
			std::string str_value="[";
			for (unsigned i = 0; i < this->size(); i++) {
				if (i > 0) {
					str_value += ",";
				}
				objectToString(this->at(i), str_value, ident, properties);
			}

			str_value+="]";
			return str_value;
		}


		//
	void objectToString(JsonVar * c_data, std::string & result_s, int level, uint16_t properties);
	//std::string result_json;
	virtual std::string serializeFormatted(int level,uint16_t properties) {
		bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
		std::string result_json="";
		objectToString(this,result_json, level, properties);

		if (not_minimized){
			result_json += "\n";
		}

		return result_json;

	}
	void objectToString(JsonVar * c_data, std::string & result_s, int ident, uint16_t properties) {

		int k=0;
		bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);


		result_s += "{";

		if (not_minimized){
			result_s += "\n";
		}

		char *aux_p = (char *)c_data->getPtrData();
		char *end_p = (char *)c_data->getPtrDataEnd();

		for (; aux_p < end_p; k++) {
			// if(chkType()) // --> get and parse ...
			JsonVar * p_sv = (JsonVar *)aux_p;

			if (p_sv != NULL) {


				if (not_minimized){
					for (int i = 0; i <= ident; i++){
						result_s += "\t";
					}
				}

				result_s += "\"" + p_sv->getVariableName()+ "\":";


				switch (p_sv->getType())// == )
				{
				case JsonVarType::JSON_VAR_TYPE_BOOLEAN:
				case JsonVarType::JSON_VAR_TYPE_NUMBER:
				case JsonVarType::JSON_VAR_TYPE_STRING:
					result_s += p_sv->serialize();
					break;

				case JsonVarType::JSON_VAR_TYPE_OBJECT:
					if (not_minimized){
						result_s += "\n";
						for (int i = 0; i <= ident; i++){
							result_s += "\t";
						}
					}
					objectToString(p_sv,result_s, ident + 1, properties);
					break;
					// arrays
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS:
					if (not_minimized){
						result_s += "\n";
						for (int i = 0; i <= ident; i++){
							result_s += "\t";
						}
					}
					result_s += p_sv->serializeFormatted(ident+1, properties);
					break;
				}
			}
			aux_p += p_sv->getSizeData();

			if (aux_p < end_p){
				result_s += ",";
			}

			if (not_minimized){
				result_s += "\n";
			}

		}

		if (not_minimized){
			for (int i = 0; i < ident; i++){
				result_s += "\t";
			}
		}

		result_s += "}";

	}*/



	void serialize_json_var(std::string & result, JsonVar *json_var){
		switch(json_var->getType()){
		default:
			break;
		case JSON_VAR_TYPE_BOOLEAN:
			result+=(*((JsonVarBoolean<> *)json_var)==true)?"true":"false";
			break;
		case JSON_VAR_TYPE_NUMBER:
			result+=zj_strutils::float_to_str(*((float *)json_var->getPtrData()));
			break;
		case JSON_VAR_TYPE_STRING:
			result+=std::string("\"") + *((JsonVarString<> *)json_var) + "\"";
			break;
		case JSON_VAR_TYPE_OBJECT:
			break;
		case JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
		case JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
		case JSON_VAR_TYPE_VECTOR_OF_STRINGS:
		case JSON_VAR_TYPE_VECTOR_OF_OBJECTS:
			break;
		case JSON_VAR_TYPE_MAP_OF_BOOLEANS:
		case JSON_VAR_TYPE_MAP_OF_NUMBERS:
		case JSON_VAR_TYPE_MAP_OF_STRINGS:
		case JSON_VAR_TYPE_MAP_OF_OBJECTS:
			break;
		}
	}

	std::string serialize(JsonVar *json_var){
		std::string serialized_var="";

		serialize_json_var(serialized_var,json_var);

		return serialized_var;
	}

}
