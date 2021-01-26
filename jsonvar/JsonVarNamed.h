namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarNamed : public JsonVar {
	public:
		//----------------------------------------------------------------
		// DON'T zj_var_ini AND NOT DECLARE ANY JsonVar UNDER IT !!!!

		JsonVar 	zj_var_ini;

		//----------------------------------------------------------------

		JsonVarNamed() {

			std::vector<char> vec = {_T_NAME... };
			std::string s_aux(vec.begin(), vec.end());

			char buffer[512] = { 0 };

			strcpy(buffer, s_aux.c_str());
			this->variable_name = buffer;
			this->size_data = sizeof(JsonVarNamed);

		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0)
		{
			this->str_value = "??";
			return this->str_value;
		}

		virtual ~JsonVarNamed() {}
	};
}
