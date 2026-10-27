namespace zetjsoncpp{

	template<typename _T_DATA>
	class ArrayObjectJsonVar : public JsonVar, public ArrayJsonVar<ObjectJsonVar<_T_DATA> * > {

	public:

		explicit ArrayObjectJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_ARRAY_OF_OBJECTS
		) {
		}

		ArrayObjectJsonVar(const ArrayObjectJsonVar &) = delete;
		ArrayObjectJsonVar &operator=(const ArrayObjectJsonVar &) = delete;


		virtual JsonVar *newJsonVar() {

			ObjectJsonVar< _T_DATA> *tt = new ObjectJsonVar<_T_DATA>;
			this->_vector_data.push_back(tt);
			return (JsonVar *)tt;
		}

		virtual void			 	push_back(const _T_DATA & tt) {
			ZJ_UNUSUED_PARAM(tt);
			throw std::runtime_error("push_back not available, please use newJsonVar in order to add ObjectJsonVar");
		}

		virtual  void 	erase(int idx_position) {
			JsonVar *json_object = this->_vector_data.at(idx_position);
			this->_vector_data.erase(this->_vector_data.begin()+idx_position);
			delete json_object;
		}

		virtual  void 	insert(int idx_position, const _T_DATA & tt) {
			ZJ_UNUSUED_2PARAMS(idx_position,tt);
			throw std::runtime_error("insert not available, please use newJsonVar in order to add ObjectJsonVar");
		}

		virtual void		clear() {
			destroy();
		}

		virtual JsonVar * getJsonVarPtr(int index) {
			return (JsonVar *)this->_vector_data.at(index);
		}

		void destroy() {

			for (unsigned i = 0; i < this->_vector_data.size(); i++) {
				delete this->_vector_data[i];
				this->_vector_data[i] = NULL;
			}

			this->_vector_data.clear();
		}

		virtual ~ArrayObjectJsonVar() {
			destroy();
		}
	private:

		void init(){
			this->type = JsonVarType::JSON_VAR_TYPE_ARRAY_OF_OBJECTS;
			this->size_bytes = sizeof(ArrayObjectJsonVar<_T_DATA>);
		}
	};
}
