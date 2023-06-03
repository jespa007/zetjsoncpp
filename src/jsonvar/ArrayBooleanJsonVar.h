namespace zetjsoncpp{

	// ARRAY BOOL
	template<char... _T_NAME>
	class ArrayBooleanJsonVar : public NamedJsonVar<_T_NAME...>, public ArrayJsonVar<BooleanJsonVar<>> {
	public:
		//_T_NAME name;
		ArrayBooleanJsonVar() {
			init();
		}

		ArrayBooleanJsonVar(const std::vector<bool> & _vec_booleans) {
			init();
			copy(_vec_booleans);
		}


		ArrayBooleanJsonVar<> & operator=(const std::vector<bool> & _vec_booleans){
			copy(_vec_booleans);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vector_data__.push_back(BooleanJsonVar<>());

			return &this->__zj_vector_data__[this->__zj_vector_data__.size()-1];
		}

		virtual ~ArrayBooleanJsonVar(){}

	private:
		void copy(const std::vector<bool> & v){
			this->__zj_vector_data__.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->__zj_vector_data__.push_back(*it);
			}
		}

		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS;
			this->__zj_size_data__ = sizeof(ArrayBooleanJsonVar<_T_NAME...>);
		}


	};
}
