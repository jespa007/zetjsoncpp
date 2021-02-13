namespace zetjsoncpp{


	template<typename _T_DATA>
	class JsonVarMap {
	protected:
		std::map<std::string,_T_DATA> __js_map_data__;
	public:

		typedef typename std::map<std::string,_T_DATA>::iterator JsonVarIteratorMap;
		//typename JsonVarIterator std::map<std::string,_T_DATA>::iterator;

		JsonVarMap() {}

		JsonVarIteratorMap begin(){
			return __js_map_data__.begin();
		}

		JsonVarIteratorMap end(){
			return __js_map_data__.end();
		}

		_T_DATA & 	operator[](const std::string & key) {
			return __js_map_data__.at(key);
		}

		_T_DATA const& 	operator[](const std::string & key) const {
			return __js_map_data__.at(key);
		}

		_T_DATA const& 	at(const std::string & key) const {
			return __js_map_data__.at(key);
		}

		void 	insert(const std::string & key, const _T_DATA & tt) {
			__js_map_data__.insert ( std::pair<std::string,_T_DATA>(key,tt) );
		}

		void 	clear() {
			__js_map_data__.clear();
		}

		void 	erase(const std::string & key) {
			if (__js_map_data__.count(key)>0) {
				__js_map_data__.erase(key);
			}
		}

		unsigned 			size() const {
			return __js_map_data__.size();
		}

		std::map<std::string,_T_DATA> * getStdMap() {
			return &__js_map_data__;
		}

		virtual ~JsonVarMap() {

		}

	protected:

		std::string toStringFormattedStart(int ident, uint16_t properties ){
			std::string str_value ="";
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_IDENT(str_value,ident-1);
			}

			str_value += "{";

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident);
			}

			return str_value;
		}

		std::string toStringFormattedEnd(int ident, uint16_t properties ){
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value="";

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident-1);
			}

			str_value += "}";

			return str_value;
		}
	};
}
