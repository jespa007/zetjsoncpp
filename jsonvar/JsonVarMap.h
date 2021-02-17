namespace zetjsoncpp{


	template<typename _T_DATA>
	class JsonVarMap {
	protected:
		std::map<std::string,_T_DATA> __zj_map_data__;
	public:

		typedef typename std::map<std::string,_T_DATA>::iterator JsonVarIteratorMap;
		//typename JsonVarIterator std::map<std::string,_T_DATA>::iterator;

		JsonVarMap() {}

		JsonVarIteratorMap begin(){
			return __zj_map_data__.begin();
		}

		JsonVarIteratorMap end(){
			return __zj_map_data__.end();
		}

		_T_DATA & 	operator[](const std::string & key) {
			return __zj_map_data__.at(key);
		}

		_T_DATA const& 	operator[](const std::string & key) const {
			return __zj_map_data__.at(key);
		}

		_T_DATA const& 	at(const std::string & key) const {
			return __zj_map_data__.at(key);
		}

		virtual void 	insert(const std::string & key, const _T_DATA & tt) {
			__zj_map_data__.insert ( std::pair<std::string,_T_DATA>(key,tt) );
		}

		virtual void 	erase(const std::string & key) {
			if (__zj_map_data__.count(key)>0) {
				__zj_map_data__.erase(key);
			}
		}

		virtual void 	clear() {
			__zj_map_data__.clear();
		}

		size_t 			size() const {
			return __zj_map_data__.size();
		}

		std::map<std::string,_T_DATA> * getStdMap() {
			return &__zj_map_data__;
		}

		virtual ~JsonVarMap() {

		}

	protected:

		std::string toJsonFormattedStart(int ident, uint16_t properties ){
			std::string str_value ="";
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);

			/*if (not_minimized){
				ZJ_FORMAT_OUTPUT_IDENT(str_value,ident-1);
			}*/

			str_value += "{";

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident+1);
			}

			return str_value;
		}

		std::string toJsonFormattedEnd(int ident, uint16_t properties ){
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value="";

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_NEW_LINE(str_value,ident);
			}

			str_value += "}";

			return str_value;
		}
	};
}
