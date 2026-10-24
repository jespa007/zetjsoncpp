namespace zetjsoncpp{

	class MapNumberJsonVar: public JsonVar, public MapJsonVar<NumberJsonVar> {

	public:

		explicit MapNumberJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS
		) {
		}

		MapNumberJsonVar(const std::map<std::string,float> & _map_numbers) {
			copy(_map_numbers);
		}


		MapNumberJsonVar & operator=(const  std::map<std::string,float> & _map_numbers){
			copy(_map_numbers);
			return *this;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(string_utils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->__zj_map_data__[key_id]=NumberJsonVar();

			return &this->__zj_map_data__[key_id];
		}

		virtual ~MapNumberJsonVar() {

		}

	private:
		void copy(const std::map<std::string,float> & m){
			this->__zj_map_data__.clear();
			for(auto it=m.begin(); it != m.end();it++){
				this->__zj_map_data__[it->first]=it->second;
			}
		}

	};
}
