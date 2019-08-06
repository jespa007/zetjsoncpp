namespace zetjsoncpp{

	// ARRAY BOOL
	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarArrayBool : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<bool> {
	public:
		//_T_NAME name;
		CParserVarArrayBool() {
			this->_m_iType = CParserVar::TYPE_ARRAY_BOOL;
			this->size = sizeof(CParserVarArrayBool<chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(bool s) {
			((vector<bool> *)this->p_data)->push_back(s);
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			bool not_minimized = ((CParserVar::PROPERTY_STR_MINIMIZED & flags) == 0);
			//this->str_value ="";
			vector<bool> * v = (vector<bool> *)this->p_data;
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

		virtual ~CParserVarArrayBool(){}

	};
}
