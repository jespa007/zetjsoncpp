namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class JsonVarVectorObject : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarObject<_T_DATA> * > {

	public:

		JsonVarVectorObject() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS;
			this->__js_size_data__ = sizeof(JsonVarVectorObject<_T_DATA, _T_NAME...>);
			this->__js_ptr_data__ = &this->__js_vec_data__;
		}

		virtual JsonVar *newData() {

			JsonVarObject< _T_DATA> *tt = new JsonVarObject<_T_DATA>;
			this->push_back(tt);
			return (JsonVar *)tt;
		}

		//std::string result_json;
		virtual std::string toStringFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value="";
			str_value+=this->toStringFormattedStart(ident,properties);
			for (unsigned i = 0; i < this->size(); i++) {
				if (i > 0) {
					str_value += ",";
				}
				objectToString(this->at(i), str_value, ident, properties);
			}

			str_value+=this->toStringFormattedEnd(ident,properties);

			return str_value;

		}

		void destroy() {

			for (unsigned i = 0; i < this->__js_vec_data__.size(); i++) {
				delete this->__js_vec_data__[i];
				this->__js_vec_data__[i] = NULL;
			}

			this->__js_vec_data__.clear();
		}

		virtual ~JsonVarVectorObject() {
			destroy();
		}
	};
}
