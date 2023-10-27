namespace zetjsoncpp{

	template<char... _T_NAME>
	class MapArrayStringJsonVar : public NamedJsonVar<_T_NAME...>, public MapJsonVar<ArrayStringJsonVar<>> {
	public:

		MapArrayStringJsonVar() {
				init();
			}

		MapArrayStringJsonVar(const std::map<std::string,std::vector<std::string>> & _map_string) {
				init();
				copy(_map_string);
			}


		MapArrayStringJsonVar<> & operator=(const  std::map<std::string,std::vector<std::string>> & _map_string){
				copy(_map_string);
				return *this;
			}

			virtual JsonVar *newJsonVar(const std::string & key_id){
				if(this->__zj_map_data__.count(key_id) != 0){
					throw std::runtime_error(string_utils::format("property name \"%s\" already exists",key_id.c_str()));
				}
				this->__zj_map_data__[key_id]=ArrayStringJsonVar<>();

				return &this->__zj_map_data__[key_id];
			}

			virtual ~MapArrayStringJsonVar() {

			}
		private:
			void copy(const std::map<std::string,std::vector<std::string>> & m){
				this->__zj_map_data__.clear();
				for(auto it=m.begin(); it != m.end();it++){
					this->__zj_map_data__[it->first]=it->second;
				}
			}

			void init(){
				this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_ARRAY_OF_STRINGS;
				this->__zj_size_data__ = sizeof(MapArrayStringJsonVar< _T_NAME...>);
			}

	};
}
