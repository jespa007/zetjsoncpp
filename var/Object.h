namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class Object : public ParserVarNamed< _T_NAME...>, public _T_DATA {

	public:
		//----------------------------------------------------------------
		// DON'T MOVE zj_var_end ON THIS CLASS !!!!

		ParserVar 	zj_var_end;

		//----------------------------------------------------------------

		void setup(uint32_t numParam = 0, ...) {
			// PRE: All args must be std::string. The program can parse the apropiate type var
			// with its emmbedded type.

			this->type = ParserVar::TYPE_OBJECT;
			this->size_data = sizeof(Object<_T_DATA,_T_NAME...>);

			ParserVar *ptr = ((ParserVar *)&this->zj_var_ini + 1);
			this->p_data = ptr;
			this->p_end_data = ((ParserVar *)&zj_var_end - 1);

			//-------
			// Iterate on all its elements ...
			char *aux_p = (char *)this->p_data;
			char *end_p = (char *)this->p_end_data;

			va_list arg_list;
			// inicialize all vars struct in order of pass parameters ...
			va_start(arg_list, numParam);
			for (unsigned i = 0; i < numParam && (aux_p < end_p); i++) {
				const char * variable = va_arg(arg_list, const char *);
				ParserVar * p_sv = (ParserVar *)aux_p;

				switch (p_sv->type)
				{
				case ParserVar::TYPE_STRING:
					//print_info_cr("std::string ...!\n\n");
					*(ZJ_STRING_CAST p_sv) = variable;//->assign();
					break;
				}

				aux_p += p_sv->size_data;
			}
			va_end(arg_list);
			//---------

		}

		Object(...) {
			setup();
		}

		Object(uint32_t numParam,...) {
			setup(numParam);
		}

		//std::string result_json;
		virtual std::string & toString(uint32_t flags = 0) {
			bool not_minimized = ((flags & ParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "";
			ObjectToString(this, this->result_json, 0, flags);

			if (not_minimized){
				this->result_json += "\n";
			}

			return this->result_json;

		}
		virtual ~Object(){};

	};

	void ObjectToString(ParserVar * c_data, std::string & result_s, int level, uint32_t flags);
}
