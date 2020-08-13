namespace zetjsoncpp{

	template<typename _T_DATA, char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class PropertyGroup : public ParserVarNamed<chr1, chr2, _T_NAME...>, public _T_DATA {


	public:


		//----------------------------------------------------------------
		// DON'T MOVE js_end ON THIS CLASS !!!!

		CParserVar 	js_end;

		//----------------------------------------------------------------
		void setup(uint32_t numParam = 0, ...) {
			// PRE: All args must be std::string. The program can parse the apropiate type var
			// with its emmbedded type.

			this->_m_iType = CParserVar::TYPE_PROPERTY_GROUP;
			this->size_data = sizeof(PropertyGroup<_T_DATA, chr1, chr2, _T_NAME...>);

			CParserVar *ptr = ((CParserVar *)&this->js_ini + 1);
			this->p_data = ptr;
			this->p_end_data = ((CParserVar *)&js_end - 1);

			//-------
			// Iterate on all its elements ...
			char *aux_p = (char *)this->p_data;
			char *end_p = (char *)this->p_end_data;

			va_list arg_list;
			// inicialize all vars struct in order of pass parameters ...
			va_start(arg_list, numParam);
			for (unsigned i = 0; i < numParam && (aux_p < end_p); i++) {
				const char * variable = va_arg(arg_list, const char *);
				CParserVar * p_sv = (CParserVar *)aux_p;

				switch (p_sv->_m_iType)
				{
				case CParserVar::TYPE_STRING:
					//print_info_cr("std::string ...!\n\n");
					*(JS_STRING_CAST p_sv) = variable;//->assign();
					break;
				}

				aux_p += p_sv->size_data;
			}
			va_end(arg_list);
			//---------

		}

		PropertyGroup(...) {
			setup();
		}

		PropertyGroup(uint32_t numParam,...) {
			setup(numParam);
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		//std::string result_json;
		virtual std::string & cpp2json(uint32_t flags = 0) {
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "";
			cpp2jsonRecursive(this, this->result_json, 0, flags);

			if (not_minimized)
				this->result_json += "\n";

			return this->result_json;

		}

		void cpp2jsonRecursive(CParserVar * c_data, std::string & result_s, int level, uint32_t flags) {

			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);

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
				CParserVar * p_sv = (CParserVar *)aux_p;
				if (p_sv != NULL) {
					if (not_minimized)
						for (int i = 0; i <= level; i++)
							result_s = result_s + "\t";


					result_s = result_s + "\"" + p_sv->_m_pvariableName + "\":";

					switch (p_sv->_m_iType)// == )
					{
					case CParserVar::TYPE_BOOL:

					case CParserVar::TYPE_NUMBER:
					case CParserVar::TYPE_STRING:
						result_s = result_s + p_sv->getStrValue(level, flags);
						break;

					case CParserVar::TYPE_PROPERTY_GROUP:
						//printf("Accessing property groupr %s ...\n", p_sv->_m_pvariableName);
						if (not_minimized)
							result_s += "\n";

						cpp2jsonRecursive(p_sv, result_s, level + 1, flags);
						break;
						// arrays
					case CParserVar::TYPE_ARRAY_BOOL:

					case CParserVar::TYPE_ARRAY_STRING:
					case CParserVar::TYPE_ARRAY_PROPERTY_GROUP:

						if (not_minimized) {
							result_s += "\n";

							for (int i = 0; i <= level; i++)
								result_s = result_s + "\t";
						}

						result_s = result_s + "[";

						if (not_minimized)
							result_s += "\n";

						if (p_sv->_m_iType != CParserVar::TYPE_ARRAY_PROPERTY_GROUP)
							result_s = result_s + p_sv->getStrValue(level, flags);
						else
						{
							//result_s = result_s + "\""+p_sv->name+"\": [\n";

								//first_element_array=true;
							std::vector <CParserVar *>  *vec = (std::vector<CParserVar *> *)(p_sv->p_data);

							for (unsigned k = 0; k < vec->size(); k++)
							{
								if (k > 0)
									result_s = result_s + ",";

								if (not_minimized)
									result_s += "\n";


								cpp2jsonRecursive(vec->at(k), result_s, level + 2, flags);
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

		virtual ~PropertyGroup(){};
	};
}
