/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

namespace zetjsoncpp {

	template<typename _T>
	class Parser : public ParserBase {

	protected:

		ArrayObject<_T> * root_struct_field;
		const char *filename;
		int line;

	public:

		Parser() {
			filename = NULL;
			line = 0;
			root_struct_field = new ArrayObject<_T>;
		}

		virtual void eval(const std::string & m_expression) = 0;

		virtual void evalFile(const std::string & _filename) {

			filename = _filename.c_str();

			char *buf = zj_file::read(filename);
			if (buf != NULL) {
				try{
					eval(buf);
				}
				catch(parse_error_exception & err){
					delete buf;
					throw err;
				}
				catch(parse_warning_exception & wrn){
					delete buf;
					throw wrn;

				}
				free(buf);
			}
		}

		ArrayObject<_T> *getData() {
			return root_struct_field;
		}

		virtual ~Parser() {
			if (root_struct_field != NULL) {
				delete root_struct_field;
			}
			root_struct_field = NULL;
		}

	};

};
