namespace zetjsoncpp{

	// ARRAY BOOL
	class ArrayBooleanJsonVar : public NamedJsonVar, public ArrayJsonVar<BooleanJsonVar> {
	public:
		//_T_NAME name;
		ArrayBooleanJsonVar(const char * _name = "")
		:NamedJsonVar(_name){
			init();
		}

		ArrayBooleanJsonVar(const std::vector<bool> & _vec_booleans) {
			init();
			copy(_vec_booleans);
		}


		ArrayBooleanJsonVar & operator=(const std::vector<bool> & _vec_booleans){
			copy(_vec_booleans);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vector_data__.push_back(BooleanJsonVar());

			return &this->__zj_vector_data__[this->__zj_vector_data__.size()-1];
		}

		virtual ~ArrayBooleanJsonVar(){}

	private:
		void copy(const std::vector<bool> & v){
			this->__zj_vector_data__.clear();
			for(size_t i=0;i<v.size();i++){
				bool b=v[i];
				this->__zj_vector_data__.push_back(b);
			}
		}

		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_ARRAY_OF_BOOLEANS;
			this->__zj_size_data__ = sizeof(ArrayBooleanJsonVar);
		}


	};
}
