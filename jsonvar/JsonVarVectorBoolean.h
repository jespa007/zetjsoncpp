namespace zetjsoncpp{

	// ARRAY BOOL
	template<char... _T_NAME>
	class JsonVarVectorBoolean : public JsonVarNamed<_T_NAME...>, public JsonVarVector<bool> {
	public:
		//_T_NAME name;
		JsonVarVectorBoolean() {
			this->type = JsonVar::JSON_VAR_TYPE_VECTOR_BOOLEAN;
			this->size = sizeof(JsonVarVectorBoolean<_T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(bool s) {
			((std::vector<bool> *)this->p_data)->push_back(s);
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			bool not_minimized = ((JsonVar::PROPERTY_STR_MINIMIZED & flags) == 0);
			//this->str_value ="";
			std::vector<bool> * v = (std::vector<bool> *)this->p_data;
			this->str_value = "";
			std::string m_sfValue;

			if (not_minimized)
				for (int k = 0; k <= (ident + 1); k++)
					this->str_value = this->str_value + "\t";

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0)
					this->str_value = this->str_value + ",";

				m_sfValue = "False";
				if (v->at(j) == true)
					m_sfValue = "True";


				this->str_value = this->str_value + "" + m_sfValue + " ";

				if (not_minimized) {
					if (j != 0 && ((j%N_ELEMENTS_JSON_VECTOR_PRINT) == 0)) {
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";

						this->str_value += "\n";
					}
				}

			}
			return this->str_value;
		}

		virtual ~JsonVarVectorBoolean(){}

	};
}
