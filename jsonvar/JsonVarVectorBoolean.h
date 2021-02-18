namespace zetjsoncpp{

	// ARRAY BOOL
	template<char... _T_NAME>
	class JsonVarVectorBoolean : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarBoolean<>> {
	public:
		//_T_NAME name;
		JsonVarVectorBoolean() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS;
			this->__zj_size_data__ = sizeof(JsonVarVectorBoolean<_T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_vec_data__;
		}


		virtual JsonVar *newJsonVar(){
			this->__zj_vec_data__.push_back(JsonVarBoolean<>());

			return &this->__zj_vec_data__[this->__zj_vec_data__.size()-1];
		}

		virtual ~JsonVarVectorBoolean(){}

	};
}
