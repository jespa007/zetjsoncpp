namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarMapString: public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarString<>> {

	public:

		JsonVarMapString() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS;
			this->__js_size_data__ = sizeof(JsonVarMapString< _T_NAME...>);
			this->__js_ptr_data__ = &this->__js_map_data__;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__js_map_data__.count(key_id) != 0){
				throw std::runtime_error("key already exists");
			}
			this->__js_map_data__[key_id]=JsonVarString<>();

			return &this->__js_map_data__[key_id];
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties) {

			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toStringFormattedStart(ident, properties);

			int j=0;
			for (auto it=__js_map_data__.begin();it !=__js_map_data__.end();it++,j++) {

				if (j > 0){
					str_value = str_value + ",";
				}

				/*str_value += "\""+it->first +*/"\":\""+(it->second+"\"");// str_value + "\"" + v->at(j) + "\" ";

				if (not_minimized){
					ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident);
				}
			}

			str_value += this->toStringFormattedEnd(ident,properties);

			return str_value;
		}

		virtual ~JsonVarMapString() {

		}
	};
}
