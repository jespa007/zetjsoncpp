namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarMapNumber: public JsonVarNamed<_T_NAME...>, public JsonVarMap<JsonVarNumber<>> {

	public:

		JsonVarMapNumber() {
			init();
		}

		JsonVarMapNumber(const std::map<std::string,float> & _map_numbers) {
			init();
			copy(_map_numbers);
		}


		JsonVarVectorNumber<> & operator=(const  std::map<std::string,float> & _map_numbers){
			copy(_map_numbers);
			return *this;
		}

		virtual JsonVar *newJsonVar(const std::string & key_id){
			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(zj_strutils::format("property name \"%s\" already exists",key_id.c_str()));
			}
			this->__zj_map_data__[key_id]=JsonVarNumber<>();

			return &this->__zj_map_data__[key_id];
		}

		virtual ~JsonVarMapNumber() {

		}

	private:
		void copy(const std::map<std::string,float> & m){
			this->__zj_map_data__.clear();
			for(auto it=m.begin(); it != m.end();it++){
				this->__zj_map_data__[it->first]=it->second;
			}
		}

		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_NUMBERS;
			this->__zj_size_data__ = sizeof(JsonVarMapNumber< _T_NAME...>);
		}

	};
}
