/**
 * Copyright 2017 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
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
