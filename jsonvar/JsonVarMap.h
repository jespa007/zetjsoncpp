namespace zetjsoncpp{

	template<typename _T_DATA>
	class JsonVarMap {
	protected:
		std::map<std::string,_T_DATA> map_data;
	public:

		JsonVarMap() {}

		_T_DATA & 	operator[](const std::string & key) {
			return map_data.at(key);
		}

		_T_DATA const& 	operator[](const std::string & key) const {
			return map_data.at(key);
		}

		_T_DATA const& 	at(const std::string & key) const {
			return map_data.at(key);
		}

		void 	insert(const std::string & key, const _T_DATA & tt) {
			map_data.insert ( std::pair<std::string,_T_DATA>(key,tt) );
		}

		void 	clear() {
			map_data.clear();
		}

		void 	erase(const std::string & key) {
			if (map_data.count(key)>0) {
				map_data.erase(key);
			}
		}

		unsigned 			size() const {
			return map_data.size();
		}

		std::map<std::string,_T_DATA> * getStdMap() {
			return &map_data;
		}
	};
}
