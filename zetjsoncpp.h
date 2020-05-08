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
#include <string>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>
#include <stdexcept>
#include <float.h>
#include <limits.h>


#define ZETJSONCPP_MAJOR_VERSION 1
#define ZETJSONCPP_MINOR_VERSION 3
#define ZETJSONCPP_PATCH_VERSION 0

#ifdef __MEMMANAGER__
#include "memmgr.h"
#endif

#include "util/zj_string.h"
#include "util/zj_io.h"
#include "util/zj_path.h"


#include "var/ZJ_Boolean.h"
#include "var/ZJ_Number.h"
#include "var/ZJ_String.h"


#include "exception.h"
#include "parser_var/CParserVar.h"
#include "CParserBase.h"
#include "CParser.h"
#include "CParserJson.h"


