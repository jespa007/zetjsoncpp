namespace zetjsoncpp{

	template<typename _T_DATA, char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarArrayPropertyGroup : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<CParserVarPropertyGroup<_T_DATA> * > {

	public:

		CParserVarArrayPropertyGroup() {
			this->_m_iType = CParserVar::TYPE_ARRAY_PROPERTY_GROUP;
			this->size_data = sizeof(CParserVarArrayPropertyGroup<_T_DATA, chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;

			if (this->_m_pvariableName == "")
			{
				fprintf(stderr,"parse variable is empty, it's impossible to load any empty variable!\n");
			}
		}

		virtual CParserVar *newData() {
			return new CParserVarPropertyGroup<_T_DATA>;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		virtual void add(CParserVar * s) {
			CParserVarPropertyGroup< _T_DATA> *tt = (CParserVarPropertyGroup< _T_DATA> *)s;
			this->push_back(tt);
		}

		//std::string result_json;
		virtual std::string & cpp2json(uint32_t flags = 0) {
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "[";
			for (unsigned i = 0; i < this->size(); i++) {
				if (i > 0) {
					this->result_json += ",";
				}
				this->at(i)->cpp2jsonRecursive(this->at(i), this->result_json, 0, flags);
			}

			this->result_json += "]";
			if (not_minimized)
				this->result_json += "\n";

			return this->result_json;

		}

		void destroy() {

			for (unsigned i = 0; i < this->vec_data.size(); i++) {
				delete this->vec_data[i];
				this->vec_data[i] = NULL;
			}

			this->vec_data.clear();
		}

		virtual ~CParserVarArrayPropertyGroup() {
			destroy();

		}
	};
}
