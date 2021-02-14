/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#ifndef __ZJ_EXCEPTION_H__
#define __ZJ_EXCEPTION_H__

namespace zetjsoncpp {

	class parse_exception: public std::exception
	{
		const char *error_type;

		//std::string file;
		//int	   line;
		std::string	error_description;

		char what_msg[4096];
	public:


		parse_exception(const char *  _file, int _line, const std::string & _error_description, const char *_error_type){

			error_type=_error_type;
			/*if(file != NULL){
				file=_file;
				line=_line;
			}*/
			error_description=_error_description;

			if(_file != NULL){
				sprintf(what_msg,"[%s %s:%i] %s",error_type,_file, _line, (char *)error_description.c_str());
			}else{
				sprintf(what_msg,"[%s] %s",error_type, (char *)error_description.c_str());
			}
		}

	    virtual const char* what() const throw()
		{
	    	return (const char *)what_msg;
		}
	};

	class parse_error_exception: public parse_exception{
	public:

		parse_error_exception(const char *  _file, int _line, const std::string & _error):parse_exception(_file,  _line, _error,"ERR"){}

	};

};

#endif
