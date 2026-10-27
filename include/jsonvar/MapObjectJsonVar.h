namespace zetjsoncpp{

	template<typename _T_DATA>
	class MapObjectJsonVar : public JsonVar, public MapJsonVar<ObjectJsonVar<_T_DATA> * > {


	public:

		explicit MapObjectJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS) {
		}

		MapObjectJsonVar(const MapObjectJsonVar &) = delete;
		MapObjectJsonVar &operator=(const MapObjectJsonVar &) = delete;

		virtual JsonVar *newJsonVar(const std::string & key_id) {

			if(this->_map_data.count(key_id) != 0){
				throw std::runtime_error(string_utils::format("property name \"%s\" already exists",key_id.c_str()));
			}

			ObjectJsonVar< _T_DATA> *tt = new ObjectJsonVar<_T_DATA>;
			this->_map_data[key_id]=tt;
			return (JsonVar *)tt;
		}

		virtual void 	clear() {
			destroy();
		}

		void erase(const std::string &_key_id) {
		    auto it = this->_map_data.find(_key_id);

		    if(it == this->_map_data.end()) {
		        return;
		    }

		    delete it->second;
		    this->_map_data.erase(it);
		}

		virtual JsonVar * getJsonVarPtr(const std::string & key_id) {
			return (JsonVar *)this->_map_data.at(key_id);
		}

		void destroy() {
		    for(auto &entry : this->_map_data) {
		        delete entry.second;
		    }

		    this->_map_data.clear();
		}

		virtual ~MapObjectJsonVar() {
			destroy();
		}
	private:
	};
}
