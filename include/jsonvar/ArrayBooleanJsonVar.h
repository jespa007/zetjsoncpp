namespace zetjsoncpp{

	// ARRAY BOOL
	class ArrayBooleanJsonVar : public JsonVar, public ArrayJsonVar<BooleanJsonVar> {
	public:
		using JsonVar::newJsonVar;
		//_T_NAME name;
		explicit ArrayBooleanJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_ARRAY_OF_BOOLEANS
		) {
		}


		ArrayBooleanJsonVar(const std::vector<bool> & _vec_booleans)
	    : JsonVar("", JsonVarType::JSON_VAR_TYPE_ARRAY_OF_BOOLEANS) {
			copy(_vec_booleans);
		}


		ArrayBooleanJsonVar & operator=(const std::vector<bool> & _vec_booleans){
			copy(_vec_booleans);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
						this->_vector_data.push_back(BooleanJsonVar());
			return &this->_vector_data[this->_vector_data.size()-1];
		}

		void forEachArrayElement(ConstFieldCallback _callback ,void *_context) const override {
		    this->visitArrayElements(
		        _callback
		        ,_context
		    );
		}

		virtual ~ArrayBooleanJsonVar(){}

	private:
		void copy(const std::vector<bool> & v){
			this->_vector_data.clear();
			for(size_t i=0;i<v.size();i++){
				bool b=v[i];
				this->_vector_data.push_back(b);
			}
		}

	};
}
