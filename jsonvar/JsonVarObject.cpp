#include "..\zetjsoncpp.h"

namespace zetjsoncpp{

	void objectToString(JsonVar * c_data, std::string & result_s, int level, uint16_t properties) {


		bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);

		if (not_minimized){
			for (int i = 0; i < level; i++){
				result_s += "\t";
			}
		}
		result_s = result_s + "{";

		if (not_minimized){
			result_s += "\n";
		}

		char *aux_p = (char *)c_data->getPtrData();
		char *end_p = (char *)c_data->getPtrDataEnd();

		for (; aux_p < end_p; ) {
			// if(chkType()) // --> get and parse ...
			JsonVar * p_sv = (JsonVar *)aux_p;
			if (p_sv != NULL) {
				if (not_minimized){
					for (int i = 0; i <= level; i++){
						result_s += "\t";
					}
				}

				result_s += "\"" + p_sv->getVariableName()+ "\":";

				switch (p_sv->getType())// == )
				{
				case JsonVarType::JSON_VAR_TYPE_BOOLEAN:
				case JsonVarType::JSON_VAR_TYPE_NUMBER:
				case JsonVarType::JSON_VAR_TYPE_STRING:
					result_s += p_sv->toString();
					break;

				case JsonVarType::JSON_VAR_TYPE_OBJECT:

					if (not_minimized){
						result_s += "\n";
					}

					objectToString(p_sv,result_s, level + 1, properties);
					break;
					// arrays
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS:
				case JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS:

					if (not_minimized) {
						result_s += "\n";

						for (int i = 0; i <= level; i++){
							result_s += "\t";
						}
					}

					result_s += "[";

					if (not_minimized){
						result_s += "\n";
					}

					if (p_sv->getType() != JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS){
						result_s += p_sv->toStringFormatted(level, properties);
					}else{
						std::vector <JsonVar *>  *vec = (std::vector<JsonVar *> *)(p_sv->getPtrData());

						for (unsigned k = 0; k < vec->size(); k++)
						{
							if (k > 0){
								result_s = result_s + ",";
							}

							if (not_minimized)
								result_s += "\n";

							objectToString(vec->at(k),result_s, level + 2, properties);
						}
					}

					if (not_minimized) {
						result_s += "\n";

						for (int i = 0; i <= level; i++){
							result_s += "\t";
						}
					}

					result_s += "]";
					break;
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS:
				case JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS:
					if (not_minimized) {
						result_s += "\n";
						/*for (int i = 0; i < level; i++){
							result_s += "\t";
						}*/
					}

					//result_s += "{";

					/*if (not_minimized){
						result_s += "\n";
					}*/

					//if (p_sv->getType() != JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS){*/
						result_s += p_sv->toStringFormatted(level, properties);
					/*}else{ // map object
						int k=0;
						std::map <std::string,JsonVar *>  *map_data = (std::map<std::string,JsonVar *> *)(p_sv->getPtrData());


						for (auto it=map_data->begin();it !=map_data->end();it++,k++) {
							if (k > 0){
								result_s += ",";
							}

							if (not_minimized){
								result_s += "\n";
							}

							result_s += "\""+it->first +"\":\"";
							objectToString(it->second,result_s, level + 2, properties);
							result_s +="\"";// this->str_value + "\"" + v->at(j) + "\" ";
						}
					}*/

					/*if (not_minimized) {
						result_s += "\n";

						for (int i = 0; i <= level; i++){
							result_s += "\t";
						}
					}

					result_s += "}";*/
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
			for (int i = 0; i < level; i++){
				result_s += "\t";
			}
		}

		result_s += "}";

	}
}
