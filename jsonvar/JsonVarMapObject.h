namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class JsonVarMapObject : public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarObject<_T_DATA> * > {


	public:

		JsonVarMapObject() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS;
			this->__zj_size_data__ = sizeof(JsonVarMapObject<_T_DATA, _T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_map_data__;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id) {

			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(zj_strutils::format("property name \"%s\" already exists",key_id.c_str()));
			}

			JsonVarObject< _T_DATA> *tt = new JsonVarObject<_T_DATA>;
			this->__zj_map_data__[key_id]=tt;
			return (JsonVar *)tt;
		}

		virtual void 	clear() {
			destroy();
		}

		virtual std::string serializeFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toJsonFormattedStart(ident, properties);

			int j=0;
			for (auto it=this->__zj_map_data__.begin(); it != this->__zj_map_data__.end(); it++,j++) {
				if (j > 0) {
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}
					str_value += ",";
				}

				str_value+="\""+it->first +"\":";


				objectToString(it->second, str_value, ident+1, properties);

			}

			str_value += this->toJsonFormattedEnd(ident,properties);

			return str_value;
		}

		void destroy() {

			for (auto it = this->__zj_map_data__.begin(); it != this->__zj_map_data__.end(); it++) {
				delete it->second;
			}

			this->__zj_map_data__.clear();
		}

		virtual ~JsonVarMapObject() {
			destroy();
		}
	};
}
