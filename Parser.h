/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

namespace zetjsoncpp {

	template<typename _T>
	class Parser : public ParserBase {

	protected:

		_T * root_struct_field;
		const char *filename;
		int line;

	public:

		Parser() {
			filename = NULL;
			line = 0;
			root_struct_field=NULL;

		}

		virtual _T * eval(const std::string & m_expression) = 0;

		virtual _T * evalFile(const std::string & _filename) {

			//_T * json_element;
			filename = _filename.c_str();

			char *buf = zj_file::read(filename);
			if (buf != NULL) {
				try{
					eval(buf);
				}
				catch(parse_error_exception & err){
					free(buf);
					throw err;
				}
				catch(parse_warning_exception & wrn){
					delete buf;
					throw wrn;

				}
				free(buf);
			}

			return root_struct_field;
		}

		/*_T *getData() {
			return root_struct_field;
		}*/

		virtual ~Parser() {
			if (root_struct_field != NULL) {
				delete root_struct_field;
			}
			root_struct_field = NULL;
		}

	};

};
