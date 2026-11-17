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


		JsonVar *newJsonVar() override {
		    std::unique_ptr<ObjectJsonVar<_T_DATA>> tt(
		        new ObjectJsonVar<_T_DATA>
		    );

		    this->_vector_data.push_back(tt.get());
		    return tt.release();
		}

		virtual void			 	push_back(const _T_DATA & tt) = delete;

		virtual  void 	erase(int idx_position) {
			JsonVar *json_object = this->_vector_data.at(idx_position);
			this->_vector_data.erase(this->_vector_data.begin()+idx_position);
			delete json_object;
		}

		virtual  void 	insert(int idx_position, const _T_DATA & tt) = delete;

		virtual void		clear() {
			destroy();
		}

		virtual JsonVar * getJsonVarPtr(int index) {
			return (JsonVar *)this->_vector_data.at(index);
		}

		void forEachArrayElement( ConstFieldCallback _callback  ,void *_context ) const override {

		    this->visitArrayElements(
		        _callback
		        ,_context
		    );
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
