namespace zetjsoncpp{

	template<typename _T_DATA>
	class MapObjectJsonVar : public JsonVar, public MapJsonVar<ObjectJsonVar<_T_DATA> * > {

	public:

		using JsonVar::newJsonVar;

		explicit MapObjectJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_MAP_OF_OBJECTS) {
		}

		MapObjectJsonVar(const MapObjectJsonVar &) = delete;
		MapObjectJsonVar &operator=(const MapObjectJsonVar &) = delete;

		virtual JsonVar *newJsonVar(
		    const std::string &key_id
		) override {

		    std::unique_ptr<ObjectJsonVar<_T_DATA>> tt(
		        new ObjectJsonVar<_T_DATA>
		    );

		    auto result = this->_map_data.emplace(
		        key_id
		        ,tt.get()
		    );

		    if(!result.second) {
		        throw std::runtime_error( string_utils::format("property name \"%s\" already exists" ,key_id.c_str()));
		    }

		    return tt.release();
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

		void forEachMapEntry(ConstMapEntryCallback _callback ,void *_context) const override {

		    this->visitMapEntries(
		        _callback
		        ,_context
		    );
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
