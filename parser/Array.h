namespace zetjsoncpp{

	template<typename _T_DATA, char a = 'a', char b = 'b'>
	class Array {
	protected:
		std::vector<_T_DATA> vec_data;
	public:

		Array() {}

		_T_DATA & 	operator[](int i) {
			return vec_data.at(i);
		}

		_T_DATA const& 	operator[](int i) const {
			return vec_data.at(i);
		}

		_T_DATA const& 	at(unsigned int i) const {

			return vec_data.at(i);
		}

		void			 	push_back(const _T_DATA & tt) {
			vec_data.push_back(tt);
		}

		void			 	clear() {
			vec_data.clear();
		}

		void 	erase(unsigned int i) {
			if (i < vec_data.size()) {
				vec_data.erase(vec_data.begin() + i);
			}
		}

		unsigned 			size() const {
			return vec_data.size();
		}

		const std::vector<_T_DATA> & getStdVector() {
			return vec_data;
		}
	};
}
