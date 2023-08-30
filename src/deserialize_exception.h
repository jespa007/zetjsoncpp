/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

namespace zetjsoncpp {

	class deserialize_exception: public std::exception
	{
		std::string	description;
		int line;
		std::string file;
		char what_msg[4096];
	public:

		deserialize_exception(const char *  _file, int _line, const std::string & _description){

			memset(what_msg,0,sizeof(what_msg));
			description=_description;
			line = _line;

			if(_file != NULL  && *_file != 0){
				file=_file;
				sprintf(what_msg,"[file:%s line:%i] %s",_file, _line, (char *)description.c_str());
			}else{
				sprintf(what_msg,"[line:%i] %s",_line,(char *)description.c_str());
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

