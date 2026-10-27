namespace zetjsoncpp{

	class MapStringJsonVar: public JsonVar, public MapJsonVar<StringJsonVar> {

	public:

		explicit MapStringJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_MAP_OF_STRINGS) {
		}

		MapStringJsonVar(const std::map<std::string,std::string> & _map_string){
			copy(_map_string);
		}

		MapStringJsonVar & operator=(const  std::map<std::string,std::string> & _map_string){

			copy(_map_string);
			return *this;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->_map_data.count(key_id) != 0){
				throw std::runtime_error(string_utils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->_map_data[key_id] = StringJsonVar();

			return &this->_map_data[key_id];
		}

		virtual ~MapStringJsonVar() {

		}
	private:
		void copy(const std::map<std::string,std::string> & m){
			this->_map_data.clear();
			for(auto it=m.begin(); it != m.end();it++){
				this->_map_data[it->first]=it->second;
			}
		}

	};
}
