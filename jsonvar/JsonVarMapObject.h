namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class JsonVarMapObject : public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarObject<_T_DATA> * > {


	public:

		JsonVarMapObject() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS;
			this->__js_size_data__ = sizeof(JsonVarMapObject<_T_DATA, _T_NAME...>);
			this->__js_ptr_data__ = &this->__js_map_data__;
		}

		virtual JsonVar *newJsonVar(const std::string & key) {

			if(this->__js_map_data__.count(key) != 0){
				throw std::runtime_error("key already exists");
			}

			JsonVarObject< _T_DATA> *tt = new JsonVarObject<_T_DATA>;
			this->__js_map_data__[key]=tt;
			return (JsonVar *)tt;
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toStringFormattedStart(ident, properties);


			int j=0;
			for (auto it=this->__js_map_data__.begin(); it != this->__js_map_data__.end(); it++,j++) {
				if (j > 0) {
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}
					str_value += ",";
				}

				str_value+="\""+it->first +"\":";


				objectToString(it->second, str_value, ident+1, properties);

			}

			str_value += this->toStringFormattedEnd(ident,properties);

			return str_value;
		}

		void destroy() {

			for (auto it = this->__js_map_data__.begin(); it != this->__js_map_data__.end(); it++) {
				delete it->second;
			}

			this->__js_map_data__.clear();
		}

		virtual ~JsonVarMapObject() {
			destroy();
		}
	};
}
