

namespace zetjsoncpp{

	template<typename _T_DATA>
	class ArrayJsonVar {
	protected:
		std::vector<_T_DATA> _vector_data;
	public:

		typedef typename std::vector<_T_DATA>::iterator ArrayIteratorJsonVar;

		ArrayJsonVar() {}

		ArrayIteratorJsonVar begin(){
			return _vector_data.begin();
		}

		ArrayIteratorJsonVar end(){
			return _vector_data.end();
		}

		_T_DATA & 	operator[](int i) {
			return _vector_data.at(i);
		}

		_T_DATA const& 	operator[](int i) const {
			return _vector_data.at(i);
		}

		_T_DATA const& 	at(unsigned int i) const {

			return _vector_data.at(i);
		}

		void			 	push_back(const _T_DATA & tt) {
			_vector_data.push_back(tt);
		}

		virtual  void 	erase(int idx_position) {
			_vector_data.erase(_vector_data.begin()+idx_position);
		}

		void 	insert(int idx_position, const _T_DATA & tt) {
			_vector_data.insert(_vector_data.begin()+idx_position,tt);
		}

		virtual void		clear() {
			_vector_data.clear();
		}

		size_t			size() const {
			return _vector_data.size();
		}

		const std::vector<_T_DATA> & getStdVector() {
			return _vector_data;
		}

		const std::vector<_T_DATA> * getStdVectorPtr() {
			return &_vector_data;
		}

		virtual JsonVar * getJsonVarPtr(int index) {
			return (JsonVar *)&_vector_data.at(index);
		}

		void visitArrayElements( ConstFieldCallback _callback  ,void *_context ) const {
		    for(const auto &element : this->_vector_data) {
		        _callback(
		            detail::asJsonVar(element)
		            ,_context
		        );
		    }
		}

		virtual ~ArrayJsonVar() {

		}

	};
}
