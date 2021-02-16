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

		virtual std::string toStringFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED & properties) == 0);
			std::vector<JsonVarBoolean<>> * v = (std::vector<JsonVarBoolean<>> *)this->__zj_ptr_data_start__;
			std::string str_value = "";

			str_value+=toStringFormattedStart(ident,properties);

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					if (not_minimized) {
						ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident+1,j);
					}
					str_value += ",";
				}

				str_value += (v->at(j) == true?"true":"false");

			}

			str_value+=toStringFormattedEnd(ident,properties);

			return str_value;
		}

		virtual ~JsonVarVectorBoolean(){}

	};
}
