#include "..\zetjsoncpp.h"

namespace zetjsoncpp{

	void ObjectToString(ParserVar * c_data, std::string & result_s, int level, uint32_t flags) {

		bool not_minimized = ((flags & ParserVar::PROPERTY_STR_MINIMIZED) == 0);

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
			ParserVar * p_sv = (ParserVar *)aux_p;
			if (p_sv != NULL) {
				if (not_minimized){
					for (int i = 0; i <= level; i++){
						result_s = result_s + "\t";
					}
				}

				result_s = result_s + "\"" + p_sv->variable_name + "\":";

				switch (p_sv->type)// == )
				{
				case ParserVar::TYPE_BOOLEAN:
				case ParserVar::TYPE_NUMBER:
				case ParserVar::TYPE_STRING:
					result_s = result_s + p_sv->getStrValue(level, flags);
					break;

				case ParserVar::TYPE_OBJECT:

					if (not_minimized)
						result_s += "\n";

					ObjectToString(p_sv, result_s, level + 1, flags);
					break;
					// arrays
				case ParserVar::TYPE_ARRAY_BOOLEAN:

				case ParserVar::TYPE_ARRAY_STRING:
				case ParserVar::TYPE_OBJECT_ARRAY:

					if (not_minimized) {
						result_s += "\n";

						for (int i = 0; i <= level; i++)
							result_s = result_s + "\t";
					}

					result_s = result_s + "[";

					if (not_minimized)
						result_s += "\n";

					if (p_sv->type != ParserVar::TYPE_OBJECT_ARRAY)
						result_s = result_s + p_sv->getStrValue(level, flags);
					else
					{
						std::vector <ParserVar *>  *vec = (std::vector<ParserVar *> *)(p_sv->p_data);

						for (unsigned k = 0; k < vec->size(); k++)
						{
							if (k > 0)
								result_s = result_s + ",";

							if (not_minimized)
								result_s += "\n";


							ObjectToString(vec->at(k), result_s, level + 2, flags);
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
