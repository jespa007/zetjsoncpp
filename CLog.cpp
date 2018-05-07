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



#include 	    "CCommon.h"
#include      "CLog.h"
#include      "CFile.h"

#define VAR_LOG(l) ((l) == CLog::LOG_ERROR?"ERR": (l)==CLog::LOG_WARNING?"WRN": (l) == CLog::LOG_INFO ? "INF" : "NAN" )
//      #include                  "cbingq.h"

//FILE  *fp;
CLog *CLog::singleton_log = NULL; 

//static char s_Filename[MAX_PATH];

CLog * CLog::getInstance()
{
    if(singleton_log == NULL)
      singleton_log = new CLog();
    
    return singleton_log;
}

//--------------------------------------------------------------------------------
CLog::CLog()
{
}
//--------------------------------------------------------------------------------


void  CLog::ini()
{

}
//---------------------------------------------------------------------------------------------------------
#ifndef  __GNUC__
        #pragma  managed(push,  off)
#endif  


void  CLog::print(const  char  *file,  int  line, int level, const  char  *string_text,...) {


		string filename = "";

		if(file != NULL)
			filename = extractFile(file);

//#ifdef  __DEBUG__
        char  text[500];
      


        CAPTURE_VARIABLE_ARGS(text, string_text);                                                                                                       //  Results  Are  Stored  In  Text
	
  
  	if(file == NULL)
		printf("%s",text);
	else
  		printf("[ %30s:%04i - %3s]=%s",filename.c_str(),line,VAR_LOG(level),text);
  

  printf("\n");

  fflush(stdout);
  fflush(stderr);
  
 // CColorTerm::resetColor();      
	
}

#ifndef  __GNUC__
#pragma  managed(pop)
#endif  

CLog::~CLog()
{

}


