namespace zetjsoncpp{

	// ARRAY BOOL
	template<char... _T_NAME>
	class ArrayBoolean : public ParserVarNamed<_T_NAME...>, public Array<bool> {
	public:
		//_T_NAME name;
		ArrayBoolean() {
			this->type = ParserVar::TYPE_ARRAY_BOOLEAN;
			this->size = sizeof(ArrayBoolean<_T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(bool s) {
			((std::vector<bool> *)this->p_data)->push_back(s);
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			bool not_minimized = ((ParserVar::PROPERTY_STR_MINIMIZED & flags) == 0);
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
					if (j != 0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT) == 0)) {
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";

						this->str_value += "\n";
					}
				}

			}
			return this->str_value;
		}

		virtual ~ArrayBoolean(){}

	};
}
