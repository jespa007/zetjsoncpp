namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarNamed : public JsonVar {
	protected:
		//----------------------------------------------------------------
		// DON'T MOVE zj_var_ini AND NOT DECLARE ANY VAR UNDER __zj_var_ini__!!!!
		JsonVar 	__zj_var_ini__;
		//
		//----------------------------------------------------------------
	public:

		//----------------------------------------------------------------

		JsonVarNamed() {
			std::vector<char> vec = {_T_NAME... };
			std::string s_aux(vec.begin(), vec.end());
			/*if(s_aux.size()>=ZJ_MAX_CONST_CHAR){
				throw new std::runtime_error(
						"zetjsoncpp::JsonVarNamed: '"+s_aux+"' exceeds character size (max "+zj_strutils::int_to_str(ZJ_MAX_CONST_CHAR)+")"
				);
			}*/
			strcpy(this->__zj_variable_name__,s_aux.c_str());
			this->__zj_size_data__ = sizeof(JsonVarNamed);
		}

		virtual ~JsonVarNamed() {}


	};
}
