namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarMapString: public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarString<>> {

	public:

		JsonVarMapString() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS;
			this->__zj_size_data__ = sizeof(JsonVarMapString< _T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_map_data__;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(zj_strutils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->__zj_map_data__[key_id]=JsonVarString<>();

			return &this->__zj_map_data__[key_id];
		}

		virtual std::string serializeFormatted(int ident, uint16_t properties) {

			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toJsonFormattedStart(ident, properties);

			int j=0;
			for (auto it=__zj_map_data__.begin();it !=__zj_map_data__.end();it++,j++) {

				if (j > 0){
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}

					str_value = str_value + ",";
				}

				str_value += "\""+it->first +"\":\""+it->second+"\"";// str_value + "\"" + v->at(j) + "\" ";
			}

			str_value += this->toJsonFormattedEnd(ident,properties);

			return str_value;
		}

		virtual ~JsonVarMapString() {

		}
	};
}
