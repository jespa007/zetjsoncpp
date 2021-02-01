namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class JsonVarMapObject : public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarObject<_T_DATA> * > {

	public:

		JsonVarMapObject() {
			this->type = JsonVar::JSON_VAR_TYPE_MAP_OBJECT;
			this->size_data = sizeof(JsonVarMapObject<_T_DATA, _T_NAME...>);
			this->p_data = &this->vec_data;
		}

		virtual JsonVar *newData() {
			return new JsonVarObject<_T_DATA>;
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}

		virtual void add(const std::string & key,JsonVar * s) {
			JsonVarObject< _T_DATA> *tt = (JsonVarObject< _T_DATA> *)s;
			this->map_data[key]=s;

		}

		//std::string result_json;
		virtual std::string & toString(uint32_t flags = 0) {
			bool not_minimized = ((flags & JsonVar::PROPERTY_STR_MINIMIZED) == 0);
			this->result_json = "{";
			for (auto it=map_data->begin(); it != this->map_data.end(); it++) {
				if (i > 0) {
					this->result_json += ",";
				}
				this->result_json +=ti->first":"+objectToString(it->second, this->result_json, 0, flags);
			}

			this->result_json += "}";
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
