

#define ZJ_FORMAT_OUTPUT_VECTOR_N_ELEMENTS			10
#define ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_out,ident,n_element) \
	if (n_element != 0 && ((n_element%ZJ_FORMAT_OUTPUT_VECTOR_N_ELEMENTS) == 0)){\
		str_out += "\n";\
		for (int k = 0; k < (ident); k++){\
			str_out += "\t";\
		}\
	}\


namespace zetjsoncpp{

	template<typename _T_DATA>
	class JsonVarVector {
	protected:
		std::vector<_T_DATA> __zj_vec_data__;
	public:

		typedef typename std::vector<_T_DATA>::iterator JsonVarIteratorVector;

		JsonVarVector() {}

		JsonVarIteratorVector begin(){
			return __zj_vec_data__.begin();
		}

		JsonVarIteratorVector end(){
			return __zj_vec_data__.end();
		}

		_T_DATA & 	operator[](int i) {
			return __zj_vec_data__.at(i);
		}

		_T_DATA const& 	operator[](int i) const {
			return __zj_vec_data__.at(i);
		}

		_T_DATA const& 	at(unsigned int i) const {

			return __zj_vec_data__.at(i);
		}

		virtual void			 	push_back(const _T_DATA & tt) {
			__zj_vec_data__.push_back(tt);
		}

		virtual  void 	erase(int idx_position) {
			__zj_vec_data__.erase(__zj_vec_data__.begin()+idx_position);
		}

		virtual  void 	insert(int idx_position, const _T_DATA & tt) {
			__zj_vec_data__.insert(__zj_vec_data__.begin()+idx_position,tt);
		}

		virtual void		clear() {
			__zj_vec_data__.clear();
		}

		size_t			size() const {
			return __zj_vec_data__.size();
		}

		const std::vector<_T_DATA> & getStdVector() {
			return __zj_vec_data__;
		}

		virtual ~JsonVarVector() {

		}

	protected:

		std::string toJsonFormattedStart(int ident, uint16_t properties ){
			std::string str_value ="";
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);

			/*if (not_minimized){
				ZJ_FORMAT_OUTPUT_IDENT(str_value,ident);
			}*/

			str_value += "[";

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

			str_value += "]";

			return str_value;
		}
	};
}
