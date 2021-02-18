namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarMapBoolean: public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarBoolean<>> {

	public:

		JsonVarMapBoolean() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS;
			this->__zj_size_data__ = sizeof(JsonVarMapBoolean< _T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_map_data__;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(zj_strutils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->__zj_map_data__[key_id]=JsonVarBoolean<>();

			return &this->__zj_map_data__[key_id];
		}

		virtual ~JsonVarMapBoolean() {

		}
	};
}
