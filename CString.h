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

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

using std::string;

enum{
	STRING_IS_INVALID_NUMBER=0,
	STRING_IS_HEXA,
	STRING_IS_INT,
	STRING_IS_DOUBLE
};

template<typename T>
static T fromString(const std::string& str){

    std::istringstream ss(str);
    T ret;
    ss >> ret;
    return ret;
}

string intToString(int number);
string floatToString(float number);
string toLower(const string & str);
bool endsWith(const string & fullString, const string & ending);
int isNumber(const string & test_str_number);

