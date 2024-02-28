#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef cJSON__h
#include "dependencies/cJSON.h"
#undef cJSON__h
#endif
#include "io/io.h"
#include "cxpathjson/declaration.h"
#include "extra/extra.h"
#include "path_format/path_format.h"
#include "parsment/parsment.h"
#include "error.h"
#include "types.h"
#include "setters/setters.h"