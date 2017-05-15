#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include <locale.h>
#include <errno.h>

#ifdef __GNUC__
#pragma GCC visibility pop
#endif

#include <cJSON.h>


/* Wrapper to be used when using a file for cJSON_Parse */
/* returns NULL on failure */
extern cJSON * cJSON_Parse_File(const char *file_name, int *err);


/* Wrapper for cJSON_Print() to be used when JSON is needed to be written to a file */
/* returns 0 on success */
/* Warning: MUST be used only when the client is using malloc/free for cJSON_InitHooks()
 */
extern int cJSON_Print_To_File(const cJSON *item, const char *file_name);
