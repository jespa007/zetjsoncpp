namespace zetjsoncpp{

	template<char... _T_NAME>
	class MapBooleanJsonVar: public NamedJsonVar<_T_NAME...>, public MapJsonVar<BooleanJsonVar<>> {

	public:

		MapBooleanJsonVar() {
			init();
		}

		MapBooleanJsonVar(const std::map<std::string,bool> & _map_bools) {
			init();
			copy(_map_bools);
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(zj_strutils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->__zj_map_data__[key_id]=BooleanJsonVar<>();

			return &this->__zj_map_data__[key_id];
		}

		virtual ~MapBooleanJsonVar() {

		}
	private:
		void copy(const std::map<std::string,bool> & m){
			this->__zj_map_data__.clear();
			for(auto it=m.begin(); it != m.end();it++){
				this->__zj_map_data__[it->first]=it->second;
			}
		}

		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_BOOLEANS;
			this->__zj_size_data__ = sizeof(MapBooleanJsonVar< _T_NAME...>);
		}
	};
}
