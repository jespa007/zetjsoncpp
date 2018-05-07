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


#include "CFile.h"
#include "CLog.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

bool fileExists(const string & m_file) {

	if(endsWith(m_file,"/"))
		return false;

	if(m_file=="")
		return false;

	struct stat buffer;
	  return (stat (m_file.c_str(), &buffer) == 0);

}

bool readFile(const string & filename, char *buffer, int buffer_length){
	int  file_length, readed_elements;
	FILE  *fp;

	if((file_length = getLengthFile(filename)) != -1) {

		if((fp  =  fopen(filename.c_str(),"rb"))  !=  NULL)
		{
			if(abs(file_length) < abs(buffer_length)) {
				memset(buffer,0,buffer_length);
				readed_elements = fread(buffer, 1, file_length, fp);
			} else {
				print_error("Cannot read, file (%s) exceds of max lenght bufffer > %i",filename.c_str(),buffer_length);
				return false;
			}

			if(readed_elements != file_length) {
				print_warning("number elements doesn't match with length file (%s)",filename.c_str());
				return false;
			}

			fclose(fp);

			return true;
		}
		else  print_error("I can't open 1 \"%s\"",filename.c_str());
	}
	else  print_error("I can't open 2 \"%s\"",filename.c_str());

	return false;
}


int  getLengthFile(const  string  & file)
{
	int  ini,  end;
	FILE  *fp;

	if((fp  =  fopen(file.c_str(),"rb"))  !=  NULL)
	{

		fseek(fp,  0,SEEK_SET);
		ini  =  ftell(fp);
		fseek(fp,  0,SEEK_END);
		end  =  ftell(fp);

		fclose(fp);

		return  (end  -  ini);

	}

	return    -1;
}

  string  extractFile(const string & _filename) {
	  size_t found;
	  string ss=_filename;
	  found=_filename.find_last_of("/\\");
	  if((int)found != -1)
		  ss= _filename.substr(found+1);
	  return ss;
  }

