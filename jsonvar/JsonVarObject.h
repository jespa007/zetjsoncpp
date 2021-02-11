namespace zetjsoncpp{

	//----------------------------------------------------------------
	// DON'T DEFINE ANY VARIABLE ON JsonVarObject CLASS !!!!
	template<typename _T_DATA, char... _T_NAME>
	class JsonVarObject : public JsonVarNamed< _T_NAME...>, public _T_DATA {
	protected:
		//----------------------------------------------------------------
		// DON'T DEFINE ANY VARIABLE UP __zj_var_end__ !!!!
		JsonVar 	__zj_var_end__;
		//
		//----------------------------------------------------------------
	public:
		//----------------------------------------------------------------

		void setup(uint32_t numParam = 0, ...) {
			// PRE: All arguments must be std::string. The program can parse the appropiate type variable
			// with its emmbedded type.

			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_OBJECT;
			this->__js_size_data__ = sizeof(JsonVarObject<_T_DATA,_T_NAME...>);

			JsonVar *ptr = ((JsonVar *)&this->__zj_var_ini__ + 1);
			this->__js_ptr_data_start__ = ptr;
			this->__js_ptr_data_end__ = ((JsonVar *)&__zj_var_end__ - 1);

			//-------
			// Iterate on all its elements ...
			char *aux_p = (char *)this->__js_ptr_data_start__;
			char *end_p = (char *)this->__js_ptr_data_end__;

			va_list arg_list;

			// inicialize all vars struct in order of pass parameters ...
			va_start(arg_list, numParam);
			for (unsigned i = 0; i < numParam && (aux_p < end_p); i++) {
				const char * variable = va_arg(arg_list, const char *);
				JsonVar * p_sv = (JsonVar *)aux_p;

				switch (p_sv->getType())
				{
				case JsonVarType::JSON_VAR_TYPE_STRING:
					//print_info_cr("std::string ...!\n\n");
					*(ZJ_CAST_JSON_VAR_STRING p_sv) = variable;//->assign();
					break;
				}

				aux_p += p_sv->getSizeData();
			}
			va_end(arg_list);
			//---------

		}

		JsonVarObject(...) {
			setup();
		}

		JsonVarObject(uint32_t numParam,...) {
			setup(numParam);
		}

		//std::string result_json;
		virtual std::string toStringFormatted(int level,uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string result_json="";
			objectToString(this,result_json, level, properties);

			if (not_minimized){
				result_json += "\n";
			}

			return result_json;

		}
		virtual ~JsonVarObject(){};

	};

	void objectToString(JsonVar * c_data, std::string & result_s, int level, uint16_t properties);
}
