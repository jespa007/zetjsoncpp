namespace zetjsoncpp{

	// ARRAY STRING
	template<char... _T_NAME>
	class JsonVarVectorString : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarString<>> {
	public:
		//_T_NAME name;
		JsonVarVectorString() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS;
			this->__zj_size_data__ = sizeof(JsonVarVectorString< _T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_vec_data__;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vec_data__.push_back(JsonVarString<>());

			return &this->__zj_vec_data__[this->__zj_vec_data__.size()-1];
		}

		virtual ~JsonVarVectorString(){}

	};
}
