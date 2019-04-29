/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */



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
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>

using std::string;
using std::vector;

#define ZETJSONCPP_MAJOR_VERSION 1
#define ZETJSONCPP_MINOR_VERSION 3
#define ZETJSONCPP_PATCH_VERSION 0


#ifdef  ZETJSONCPP_EXPORTS
	#define ZETJSONCPP_MODULE_EXPORT __declspec(dllexport)
#else
	#define ZETJSONCPP_MODULE_EXPORT
#endif


#ifdef __MEMMANAGER__
#include "MEM_ram.h"
#endif

#include "zetjsoncpp_utils.h"


#include "var/ZJ_Boolean.h"
#include "var/ZJ_Number.h"
#include "var/ZJ_String.h"


#include "zetjsoncpp_exception.h"
#include "CParserVar.h"
#include "CParserBase.h"
#include "CParser.h"
#include "CParserJson.h"


