namespace zetjsoncpp{

	//----------------------------------------------------------------
	// DON'T DEFINE ANY VARIABLE ON ObjectJsonVar CLASS !!!!
	template<typename _T_DATA, char... _T_NAME>
	class ObjectJsonVar : public NamedJsonVar< _T_NAME...>, public _T_DATA {
	protected:
		//----------------------------------------------------------------
		// DON'T DEFINE ANY VARIABLE UP __zj_var_end__ !!!!
		JsonVar 	__zj_var_end__;
		//
		//----------------------------------------------------------------
	public:
		//----------------------------------------------------------------
		ObjectJsonVar(...) {
			init();
		}

		ObjectJsonVar(uint32_t numParam,...) {
			init(numParam);
		}


		virtual ~ObjectJsonVar(){};

	private:
		void init(...) {
			// PRE: All arguments must be std::string. The program can parse the appropiate type variable
			// with its emmbedded type.
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_OBJECT;
			this->__zj_size_data__ = sizeof(ObjectJsonVar<_T_DATA,_T_NAME...>);

			JsonVar *ptr = ((JsonVar *)&this->__zj_var_ini__ + 1);
			this->__zj_ptr_data_start__ = ptr;
			this->__zj_ptr_data_end__ = ((JsonVar *)&__zj_var_end__ - 1);

		}

	};


}
