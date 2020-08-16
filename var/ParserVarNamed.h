namespace zetjsoncpp{

	template<char... _T_NAME>
	class ParserVarNamed : public ParserVar {
	public:
		//----------------------------------------------------------------
		// DON'T zj_var_ini AND NOT DECLARE ANY ParserVar UNDER IT !!!!

		ParserVar 	zj_var_ini;

		//----------------------------------------------------------------

		ParserVarNamed() {

			std::vector<char> vec = {_T_NAME... };
			std::string s_aux(vec.begin(), vec.end());

			char buffer[512] = { 0 };

			strcpy(buffer, s_aux.c_str());
			this->variable_name = buffer;
			this->size_data = sizeof(ParserVarNamed);

		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0)
		{
			this->str_value = "??";
			return this->str_value;
		}

		virtual ~ParserVarNamed() {}
	};
}
