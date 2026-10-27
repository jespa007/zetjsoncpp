/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

#define ZJ_EXCEPTION_MAX_ERROR_MESSAGE	4096

namespace zetjsoncpp {

	class deserialize_exception: public std::exception
	{
		std::string	description;
		int line;
		std::string file;
		char what_msg[ZJ_EXCEPTION_MAX_ERROR_MESSAGE];
	public:

		deserialize_exception(const char *  _file, int _line, const std::string & _description){

			memset(what_msg,0,sizeof(what_msg));
			description=_description;
			line = _line;

			if(_file != NULL  && *_file != 0){
				file=_file;
				snprintf(what_msg,ZJ_EXCEPTION_MAX_ERROR_MESSAGE,"[file:%s line:%i] %s",_file, _line, (char *)description.c_str());
			}else{
				snprintf(what_msg,ZJ_EXCEPTION_MAX_ERROR_MESSAGE,"[line:%i] %s",_line,(char *)description.c_str());
			}
		}

	    virtual const char* what() const throw()
		{
	    	return (const char *)what_msg;
		}

	    int getLine(){
	    	return line;
	    }

	    const std::string & getDescription(){
	    	return description;
	    }
	};
}

