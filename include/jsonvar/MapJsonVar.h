namespace zetjsoncpp{


	template<typename _T_DATA>
	class MapJsonVar {
	protected:
		std::map<std::string,_T_DATA> _map_data;
	public:

		typedef typename std::map<std::string,_T_DATA>::iterator JsonVarIteratorMap;
		typedef typename std::map<std::string,_T_DATA>::size_type size_type;
		//typename JsonVarIterator std::map<std::string,_T_DATA>::iterator;

		MapJsonVar() {}

		JsonVarIteratorMap begin(){
			return _map_data.begin();
		}

		JsonVarIteratorMap end(){
			return _map_data.end();
		}


		_T_DATA const& 	operator[](const std::string & key) const {
			return _map_data.at(key);
		}

		_T_DATA & 	operator[](const std::string & key) {
			return _map_data.at(key);
		}


		_T_DATA const& 	at(const std::string & key) const {
			return _map_data.at(key);
		}

		MapJsonVar::size_type count(const std::string & key) const {
			return _map_data.count(key);
		}

		virtual void insert(const std::string & key, const _T_DATA & tt) {
			_map_data.insert ( std::pair<std::string,_T_DATA>(key,tt) );
		}

		virtual void 	erase(const std::string & key) {
			if (_map_data.count(key)>0) {
				_map_data.erase(key);
			}
		}

		virtual void 	clear() {
			_map_data.clear();
		}

		size_t 			size() const {
			return _map_data.size();
		}

		std::map<std::string,_T_DATA> * getStdMap() {
			return &_map_data;
		}

		virtual JsonVar * getJsonVarPtr(const std::string & key_id) {
			return (JsonVar *)&_map_data.at(key_id);
		}

		virtual ~MapJsonVar() {

		}

	};
}
