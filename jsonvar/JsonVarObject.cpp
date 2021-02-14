#include "..\zetjsoncpp.h"

namespace zetjsoncpp{

	void objectToString(JsonVar * c_data, std::string & result_s, int ident, uint16_t properties) {

		int k=0;
		bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);

		/*if (not_minimized){
			for (int i = 0; i <= ident; i++){
				result_s += "\t";
			}
		}*/
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
					result_s += p_sv->toString();
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
					result_s += p_sv->toStringFormatted(ident+1, properties);
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

	}
}
