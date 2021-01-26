#include "..\zetjsoncpp.h"

namespace zetjsoncpp{

	void objectToString(JsonVar * c_data, std::string & result_s, int level, uint32_t flags) {

		bool not_minimized = ((flags & JsonVar::PROPERTY_STR_MINIMIZED) == 0);

		if (not_minimized)
			for (int i = 0; i < level; i++)
				result_s = result_s + "\t";
		result_s = result_s + "{";

		if (not_minimized)
			result_s += "\n";

		char *aux_p = (char *)c_data->p_data;
		char *end_p = (char *)c_data->p_end_data;

		for (; aux_p < end_p; ) {
			// if(chkType()) // --> get and parse ...
			JsonVar * p_sv = (JsonVar *)aux_p;
			if (p_sv != NULL) {
				if (not_minimized){
					for (int i = 0; i <= level; i++){
						result_s = result_s + "\t";
					}
				}

				result_s = result_s + "\"" + p_sv->variable_name + "\":";

				switch (p_sv->type)// == )
				{
				case JsonVar::JSON_VAR_TYPE_BOOLEAN:
				case JsonVar::JSON_VAR_TYPE_NUMBER:
				case JsonVar::JSON_VAR_TYPE_STRING:
					result_s = result_s + p_sv->getStrValue(level, flags);
					break;

				case JsonVar::JSON_VAR_TYPE_OBJECT:

					if (not_minimized)
						result_s += "\n";

					objectToString(p_sv, result_s, level + 1, flags);
					break;
					// arrays
				case JsonVar::JSON_VAR_TYPE_VECTOR_BOOLEAN:

				case JsonVar::JSON_VAR_TYPE_VECTOR_STRING:
				case JsonVar::JSON_VAR_TYPE_VECTOR_OBJECT:

					if (not_minimized) {
						result_s += "\n";

						for (int i = 0; i <= level; i++)
							result_s = result_s + "\t";
					}

					result_s = result_s + "[";

					if (not_minimized)
						result_s += "\n";

					if (p_sv->type != JsonVar::JSON_VAR_TYPE_VECTOR_OBJECT)
						result_s = result_s + p_sv->getStrValue(level, flags);
					else
					{
						std::vector <JsonVar *>  *vec = (std::vector<JsonVar *> *)(p_sv->p_data);

						for (unsigned k = 0; k < vec->size(); k++)
						{
							if (k > 0)
								result_s = result_s + ",";

							if (not_minimized)
								result_s += "\n";


							objectToString(vec->at(k), result_s, level + 2, flags);
						}
					}

					if (not_minimized) {
						result_s += "\n";

						for (int i = 0; i <= level; i++)
							result_s = result_s + "\t";
					}

					result_s = result_s + "]";
					break;
				}
			}
			aux_p += p_sv->size_data;

			if (aux_p < end_p)
				result_s = result_s + ",";

			if (not_minimized)
				result_s += "\n";

		}

		if (not_minimized)
			for (int i = 0; i < level; i++)
				result_s = result_s + "\t";

		result_s = result_s + "}";
	}
}
