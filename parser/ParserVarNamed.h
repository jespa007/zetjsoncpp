namespace zetjsoncpp{

	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class ParserVarNamed : public CParserVar {
	public:
		//----------------------------------------------------------------
		// DON'T js_ini AND NOT DECLARE ANY CParserVar UNDER IT !!!!

		CParserVar 	js_ini;

		//----------------------------------------------------------------

		ParserVarNamed() {

			std::vector<char> vec = { chr1, chr2,_T_NAME... };
			std::string s_aux(vec.begin(), vec.end());

			char buffer[512] = { 0 };

			strcpy(buffer, s_aux.c_str());

			if (strlen(buffer) == 0)
			{
				fprintf(stderr,"Parser variable with name! Advice: put a breakpoint here to known source of anonymous template!!!\n");
			}

			//strcpy(this->_m_pvariableName,  _T_NAME);
			this->_m_pvariableName = buffer;
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
