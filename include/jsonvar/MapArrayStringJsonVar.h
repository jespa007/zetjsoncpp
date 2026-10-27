namespace zetjsoncpp{

	class MapArrayStringJsonVar : public JsonVar, public MapJsonVar<ArrayStringJsonVar> {
	public:

		explicit MapArrayStringJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS
		) {
		}

		MapArrayStringJsonVar(const std::map<std::string,std::vector<std::string>> & _map_string) {
				copy(_map_string);
		}


		MapArrayStringJsonVar & operator=(const  std::map<std::string,std::vector<std::string>> & _map_string){
			copy(_map_string);
			return *this;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->_map_data.count(key_id) != 0){
				throw std::runtime_error(string_utils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->_map_data[key_id]=ArrayStringJsonVar();

			return &this->_map_data[key_id];
		}

		virtual ~MapArrayStringJsonVar() {

		}
	private:
			void copy(const std::map<std::string,std::vector<std::string>> & m){
				this->_map_data.clear();
				for(auto it=m.begin(); it != m.end();it++){
					this->_map_data[it->first]=it->second;
				}
			}

	};
}
