/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#ifndef __ZJ_EXCEPTION_H__
#define __ZJ_EXCEPTION_H__

namespace zetjsoncpp {

	class deserialize_exception: public std::exception
	{
		std::string	error_description;

		char what_msg[4096];
	public:

		deserialize_exception(const char *  _file, int _line, const std::string & _error_description){

			memset(what_msg,0,sizeof(what_msg));
			error_description=_error_description;

			if(_file != NULL  && *_file != 0){
				sprintf(what_msg,"[file:%s line:%i] %s",_file, _line, (char *)error_description.c_str());
			}else{
				sprintf(what_msg,"[line:%i] %s",_line,(char *)error_description.c_str());
			}
		}

	    virtual const char* what() const throw()
		{
	    	return (const char *)what_msg;
		}
	};


}

#endif
