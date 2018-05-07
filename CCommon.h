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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>


using std::string;
using std::vector;

typedef int32_t		  Sint32;
typedef uint32_t      Uint32;

#define FASTJSON_MAJOR_VERSION 0
#define FASTJSON_MINOR_VERSION 0
#define FASTJSON_PATCH_VERSION 2


#if  !defined(MAX)
#define  MAX(a,  b)              ((a)  >  (b)  ?  (a)  :  (b))
#define  MIN(a,  b)              ((a)  <  (b)  ?  (a)  :  (b))
#endif

// Util to capture args by ... 
#define CAPTURE_VARIABLE_ARGS(text_out, text_in)\
{va_list  ap;\
va_start(ap,  text_in);\
vsprintf(text_out,  text_in,  ap);\
va_end(ap);}

// Util to create vector and initialize data like c. Example (VECTOR(int, name_vector, {1,2,3,4,5})
#define VECTOR(type, name, ...) \
static const type name##_a[] = __VA_ARGS__; \
vector<type> name(name##_a, name##_a + sizeof(name##_a) / sizeof(*name##_a))






