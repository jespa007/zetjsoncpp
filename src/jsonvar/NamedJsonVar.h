namespace zetjsoncpp{

	class NamedJsonVar : public JsonVar {
	protected:
		//----------------------------------------------------------------
		// DON'T MOVE zj_var_ini AND NOT DECLARE ANY VAR UNDER __zj_var_ini__!!!!
		JsonVar 	__zj_var_ini__;
		//
		//----------------------------------------------------------------
	public:

		//----------------------------------------------------------------


		NamedJsonVar(const char *_name = "")
		    : JsonVar() {
		    this->variable_name = _name;
		    this->size_bytes = sizeof(NamedJsonVar);
		}

		virtual ~NamedJsonVar() {}


	};
}
