namespace zetjsoncpp{

	template<typename _T_DATA, char... _T_NAME>
	class JsonVarVectorObject : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarObject<_T_DATA> * > {

	public:

		JsonVarVectorObject() {
			init();
		}

		virtual JsonVar *newJsonVar() {

			JsonVarObject< _T_DATA> *tt = new JsonVarObject<_T_DATA>;
			this->__zj_vector_data__.push_back(tt);
			return (JsonVar *)tt;
		}

		virtual void			 	push_back(const _T_DATA & tt) {
			throw std::runtime_error("push_back not available, please use newJsonVar in order to add JsonVarObject");
		}

		virtual  void 	erase(int idx_position) {
			JsonVar *json_object = this->__zj_vector_data__.at(idx_position);
			this->__zj_vector_data__.erase(this->__zj_vector_data__.begin()+idx_position);
			delete json_object;
		}

		virtual  void 	insert(int idx_position, const _T_DATA & tt) {
			throw std::runtime_error("insert not available, please use newJsonVar in order to add JsonVarObject");
		}

		virtual void		clear() {
			destroy();
		}

		virtual JsonVar * getJsonVarPtr(int index) {
			return (JsonVar *)this->__zj_vector_data__.at(index);
		}

		void destroy() {

			for (unsigned i = 0; i < this->__zj_vector_data__.size(); i++) {
				delete this->__zj_vector_data__[i];
				this->__zj_vector_data__[i] = NULL;
			}

			this->__zj_vector_data__.clear();
		}

		virtual ~JsonVarVectorObject() {
			destroy();
		}
	private:

		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_OBJECTS;
			this->__zj_size_data__ = sizeof(JsonVarVectorObject<_T_DATA, _T_NAME...>);
		}
	};
}
