

#define ZJ_FORMAT_OUTPUT_VECTOR_N_ELEMENTS			10
#define ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_out,ident,n_element) \
	if (n_element != 0 && ((n_element%ZJ_FORMAT_OUTPUT_VECTOR_N_ELEMENTS) == 0)){\
		for (int k = 0; k <= (ident + 1); k++){\
			str_out += "\t";\
		}\
		str_out += "\n";\
	}\


namespace zetjsoncpp{

	template<typename _T_DATA>
	class JsonVarVector {
	protected:
		std::vector<_T_DATA> __js_vec_data__;
	public:

		typedef typename std::vector<_T_DATA>::iterator JsonVarIteratorVector;

		JsonVarVector() {}

		JsonVarIteratorVector begin(){
			return __js_vec_data__.begin();
		}

		JsonVarIteratorVector end(){
			return __js_vec_data__.end();
		}


		_T_DATA & 	operator[](int i) {
			return __js_vec_data__.at(i);
		}

		_T_DATA const& 	operator[](int i) const {
			return __js_vec_data__.at(i);
		}

		_T_DATA const& 	at(unsigned int i) const {

			return __js_vec_data__.at(i);
		}

		void			 	push_back(const _T_DATA & tt) {
			__js_vec_data__.push_back(tt);
		}

		void			 	clear() {
			__js_vec_data__.clear();
		}

		void 	erase(unsigned int i) {
			if (i < __js_vec_data__.size()) {
				__js_vec_data__.erase(__js_vec_data__.begin() + i);
			}
		}

		unsigned 			size() const {
			return __js_vec_data__.size();
		}

		const std::vector<_T_DATA> & getStdVector() {
			return __js_vec_data__;
		}

	};
}
