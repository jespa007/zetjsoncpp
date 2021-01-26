namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class JsonVarVectorObject : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarObject<_T_DATA> * > {

	public:

		JsonVarVectorObject() {
			this->type = JsonVar::JSON_VAR_TYPE_VECTOR_OBJECT;
			this->size_data = sizeof(JsonVarVectorObject<_T_DATA, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		virtual JsonVar *newData() {
			return new JsonVarObject<_T_DATA>;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		virtual void add(JsonVar * s) {
			JsonVarObject< _T_DATA> *tt = (JsonVarObject< _T_DATA> *)s;
			this->push_back(tt);
		}

		//std::string result_json;
		virtual std::string & toString(uint32_t flags = 0) {
			bool not_minimized = ((flags & JsonVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "[";
			for (unsigned i = 0; i < this->size(); i++) {
				if (i > 0) {
					this->result_json += ",";
				}
				objectToString(this->at(i), this->result_json, 0, flags);
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

		virtual ~JsonVarVectorObject() {
			destroy();
		}
	};
}
