namespace zetjsoncpp{

	// ARRAY BOOL
	template<char... _T_NAME>
	class JsonVarVectorBoolean : public JsonVarNamed<_T_NAME...>, public JsonVarVector<bool> {
	public:
		//_T_NAME name;
		JsonVarVectorBoolean() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_BOOLEANS;
			this->__js_size_data__ = sizeof(JsonVarVectorBoolean<_T_NAME...>);
			this->__js_ptr_data__ = &this->__js_vec_data__;
		}

		void add(bool s) {
			((std::vector<bool> *)this->__js_ptr_data__)->push_back(s);
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED & properties) == 0);
			std::vector<bool> * v = (std::vector<bool> *)this->__js_ptr_data__;
			std::string str_value = "";

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_IDENT(str_value,ident);
			}

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					str_value += ",";
				}

				str_value += (v->at(j) == true?"True":"False");

				if (not_minimized) {
					ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident,j);
				}

			}
			return str_value;
		}

		virtual ~JsonVarVectorBoolean(){}

	};
}
