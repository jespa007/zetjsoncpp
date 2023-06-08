#pragma once

#include "string_utils.h"
#include "file_utils.h"
#include "path_utils.h"

#define ZJ_UNUSUED_PARAM(x)			((void)(x))
#define ZJ_UNUSUED_2PARAMS(x1,x2)	((void)(x1),(void)(x2))


// Util to capture args by ...
#define ZJ_CAPTURE_VARIABLE_ARGS(text_out, text_in)\
	{va_list  ap;\
	va_start(ap,  text_in);\
	vsprintf(text_out,  text_in,  ap);\
	va_end(ap);}

#define ZJ_PREVIEW_SSTRING(start, current,n) (((current)-(n))<((start))?(start):((current)-(n)))
