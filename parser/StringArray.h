namespace zetjsoncpp{

	// ARRAY STRING
	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class StringArray : public ParserVarNamed<chr1, chr2, _T_NAME...>, public Array<std::string> {
	public:
		//_T_NAME name;
		StringArray() {
			this->_m_iType = CParserVar::TYPE_ARRAY_STRING;
			this->size_data = sizeof(StringArray<chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		void add(std::string const & s) {
			((std::vector<std::string> *)this->p_data)->push_back(s);
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->str_value = "";
			std::vector<std::string> * v = (std::vector<std::string> *)this->p_data;

			if (not_minimized)
				for (int k = 0; k <= (ident + 1); k++)
					this->str_value = this->str_value + "\t";

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0)
					this->str_value = this->str_value + ",";

				this->str_value = this->str_value + "\"" + v->at(j) + "\" ";

				if (not_minimized)
					if (j != 0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT) == 0))
					{
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";
						this->str_value += "\n";
					}

			}
			return this->str_value;
		}

		virtual ~StringArray(){}

	};
}
