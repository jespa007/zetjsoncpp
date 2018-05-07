//    This file is part of FastJson2Cpp.
//
//    FastJson2Cpp is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    FastJson2Cpp is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with FastJson2Cpp.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "CCommon.h"


class  CLog{

  CLog();
  
  
public:


  enum{
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO
  };
  
  static CLog *singleton_log;
  FILE  *fp;	
  

	void  ini();
	
	static CLog * getInstance();

	//void  print_with_file_line(const  char  *file,  int  line,  const  char  *string_text,...);
	//void  print(const  char  *string_text,...);
	static void  print(const  char  *file,  int  line, int level, const  char  *string_text,...);

	~CLog();
	
	static void destroy();
};


#define print_error(s, ...) 		CLog::print(__FILE__,__LINE__,CLog::LOG_ERROR	, s, ##__VA_ARGS__)
#define print_warning(s, ...)   	CLog::print(__FILE__,__LINE__,CLog::LOG_WARNING	, s, ##__VA_ARGS__)
#define print_info(s, ...)   		CLog::print(__FILE__,__LINE__,CLog::LOG_INFO	, s, ##__VA_ARGS__)





