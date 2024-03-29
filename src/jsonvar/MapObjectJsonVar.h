namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class MapObjectJsonVar : public NamedJsonVar<_T_NAME...>, public MapJsonVar<ObjectJsonVar<_T_DATA> * > {


	public:

		MapObjectJsonVar() {
			init();
		}

		virtual JsonVar *newJsonVar(const std::string & key_id) {

			if(this->__zj_map_data__.count(key_id) != 0){
				throw std::runtime_error(string_utils::format("property name \"%s\" already exists",key_id.c_str()));
			}

			ObjectJsonVar< _T_DATA> *tt = new ObjectJsonVar<_T_DATA>;
			this->__zj_map_data__[key_id]=tt;
			return (JsonVar *)tt;
		}

		virtual void 	clear() {
			destroy();
		}

		virtual JsonVar * getJsonVarPtr(const std::string & key_id) {
			return (JsonVar *)this->__zj_map_data__.at(key_id);
		}
		void destroy() {

			for (auto it = this->__zj_map_data__.begin(); it != this->__zj_map_data__.end(); it++) {
				delete it->second;
			}

			this->__zj_map_data__.clear();
		}

		virtual ~MapObjectJsonVar() {
			destroy();
		}
	private:
		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS;
			this->__zj_size_data__ = sizeof(MapObjectJsonVar<_T_DATA, _T_NAME...>);
		}
	};
}
