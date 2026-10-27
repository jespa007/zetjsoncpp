namespace zetjsoncpp{

	template<typename _T_DATA>
	class ObjectJsonVar
		: public JsonVar
		, public _T_DATA {

	public:
		explicit ObjectJsonVar(const char *_name = "")
			: JsonVar(_name, JsonVarType::JSON_VAR_TYPE_OBJECT) {
		}

		void forEachField(
			FieldCallback _callback
			,void *_context
		) override {
			this->visitFields([&](JsonVar &_field) {
				_callback(&_field, _context);
			});
		}

		void forEachField(
			ConstFieldCallback _callback
			,void *_context
		) const override {
			this->visitFields([&](const JsonVar &_field) {
				_callback(&_field, _context);
			});
		}
	};


}
