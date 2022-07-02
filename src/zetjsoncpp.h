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
#include <map>
#include <locale>
#include <codecvt>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>
#include <stdexcept>
#include <float.h>
#include <limits.h>
#include <math.h>

#define ZETJSONCPP_VERSION_MAJOR 2
#define ZETJSONCPP_VERSION_MINOR 0
#define ZETJSONCPP_VERSION_PATCH 4

#ifdef __MEMMANAGER__
#include "memmgr.h"
#endif



#include "util/zj_util.h"




#include "exception.h"
#include "jsonvar/JsonVar.h"


// static zetjsoncpp

namespace zetjsoncpp {


		template <typename _T>
		_T * deserialize(const std::string & expression);

		template <typename _T>
		_T * deserialize_file(const std::string & _filename);

		std::string serialize(JsonVar *json_var, bool minimized=false);

}

#include "zetjsoncpp.tcc"


