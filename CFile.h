//    This file is part of json2cpp.
//
//    json2cpp is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    json2cpp is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with json2cpp.  If not, see <http://www.gnu.org/licenses/>.


#pragma once


namespace json2cpp{

	bool fileExists(const string & m_file) ;
	ByteBuffer * readFile(const string & filename, bool end_string_char=true);
	int  getLengthFile(const  string  & file);
	string extractFile(const string & _filename);

};




