namespace zetjsoncpp{

	class BooleanJsonVar : public NamedJsonVar{

	public:

		static bool parse(const std::string & s){
			if(string_utils::toLower(s) == "true") return true;
			if(string_utils::toLower(s) == "false") return false;

			throw ("Cannot parse string to boolean.");
		}

		BooleanJsonVar(const char * _name ="")
		:NamedJsonVar(_name){
			init();
		}

		//_T_NAME name;
		BooleanJsonVar(bool b) {
			init();
			this->__zj_value__ = b;
		}

		operator bool(){return __zj_value__;}

		virtual void * getPtrValue(){ return &__zj_value__;}

		// operators
		BooleanJsonVar & operator=(bool _value){
			__zj_value__=_value;
			return *this;
		}

		BooleanJsonVar & operator=(const BooleanJsonVar & _b){
			__zj_value__=_b.__zj_value__;
			return *this;
		}
		//--------------------------------------------------------
		// ||
		friend bool operator ||(const BooleanJsonVar & b1, bool b2)  {
			return b1.__zj_value__ || b2;
		}

		friend bool operator ||(bool b1, const BooleanJsonVar & b2)  {
			return b1 || b2.__zj_value__;
		}

		friend bool operator ||(const BooleanJsonVar & b1, const BooleanJsonVar & b2)  {
			return b1.__zj_value__ || b2.__zj_value__;
		}

		//--------------------------------------------------------
		// &&
		friend bool operator &&(const BooleanJsonVar & b1, bool b2)  {
			return b1.__zj_value__ && b2;
		}

		friend bool operator &&(bool b1, const BooleanJsonVar & b2)  {
			return b1 && b2.__zj_value__;
		}

		friend bool operator &&(const BooleanJsonVar & b1, const BooleanJsonVar & b2)  {
			return b1.__zj_value__ && b2.__zj_value__;
		}
		//--------------------------------------------------------
		// ==
		friend bool operator ==(const BooleanJsonVar & b1, bool b2)  {
			return b1.__zj_value__ == b2;
		}

		friend bool operator ==(bool b1, const BooleanJsonVar & b2)  {
			return b1 == b2.__zj_value__;
		}

		friend bool operator ==(const BooleanJsonVar & b1, const BooleanJsonVar & b2)  {
			return b1.__zj_value__ == b2.__zj_value__;
		}
		//--------------------------------------------------------
		// !=
		friend bool operator !=(const BooleanJsonVar & b1, bool b2)  {
			return b1.__zj_value__ != b2;
		}

		friend bool operator !=(bool b1, const BooleanJsonVar & b2)  {
			return b1 != b2.__zj_value__;
		}

		friend bool operator !=(const BooleanJsonVar & b1, const BooleanJsonVar & b2)  {
			return b1.__zj_value__ != b2.__zj_value__;
		}


		virtual ~BooleanJsonVar(){}

	private:

		bool __zj_value__;

		void init() {
			__zj_value__=false;
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_BOOLEAN;
			this->__zj_size_data__ = sizeof(BooleanJsonVar);
		}

	};
}
