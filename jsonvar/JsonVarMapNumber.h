namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarMapNumber: public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarNumber<>> {

	public:

		JsonVarMapNumber() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS;
			this->__zj_size_data__ = sizeof(JsonVarMapNumber< _T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_map_data__;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error("key already exists");
			}
			this->__zj_map_data__[key_id]=JsonVarNumber<>();

			return &this->__zj_map_data__[key_id];
		}

		//std::string result_json;
		virtual std::string toStringFormatted(int ident, uint16_t properties){

			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = this->toStringFormattedStart(ident, properties);

			int j=0;
			for (auto it=__zj_map_data__.begin();it !=__zj_map_data__.end();it++,j++) {

				if (j > 0){
					if (not_minimized){
						ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
					}
					str_value += ",";
				}

				str_value += "\""+it->first +"\":"+ zj_strutils::float_to_str(it->second)+"";// this->str_value + "\"" + v->at(j) + "\" ";
			}

			str_value += this->toStringFormattedEnd(ident,properties);

			return str_value;

		}

		virtual ~JsonVarMapNumber() {

		}

	protected:

	};
}
