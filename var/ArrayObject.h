namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class ArrayObject : public ParserVarNamed<_T_NAME...>, public Array<Object<_T_DATA> * > {

	public:

		ArrayObject() {
			this->type = ParserVar::TYPE_OBJECT_ARRAY;
			this->size_data = sizeof(ArrayObject<_T_DATA, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		virtual ParserVar *newData() {
			return new Object<_T_DATA>;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		virtual void add(ParserVar * s) {
			Object< _T_DATA> *tt = (Object< _T_DATA> *)s;
			this->push_back(tt);
		}

		//std::string result_json;
		virtual std::string & toString(uint32_t flags = 0) {
			bool not_minimized = ((flags & ParserVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "[";
			for (unsigned i = 0; i < this->size(); i++) {
				if (i > 0) {
					this->result_json += ",";
				}
				ObjectToString(this->at(i), this->result_json, 0, flags);
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

		virtual ~ArrayObject() {
			destroy();
		}
	};
}
