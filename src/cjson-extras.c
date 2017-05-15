
/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/* cJSON */
/* JSON parser in C. */

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
#include "cjson-extras.h"

/* define our own boolean type */
#define true ((cJSON_bool)1)
#define false ((cJSON_bool)0)


static unsigned long get_file_size(const char *file_name); 

/* Wrapper to be used when using a file for cJSON_Parse */
cJSON * cJSON_Parse_File(const char *file_name, int *err)
{
    FILE *fin;
    char *data;
    cJSON *json = NULL;
    unsigned long len;
    
    errno = 0;
    len = get_file_size(file_name);
    
    if ( (len <= 0) || (NULL == file_name) || (NULL == (fin = fopen(file_name, "rb"))) ) 
    {
        if (NULL != err) {
            *err = errno;
        } 
        return NULL; 
    }
    
    data = (char *) malloc(len + + sizeof(""));
    if (data) 
    {
     if (fread(data, sizeof(unsigned char), len, fin) == len) 
     {
         data[len] = '\0';
         json = cJSON_Parse(data);
     }
     free(data);
    }
    
    fclose(fin);
    return json;
}

/* Wrapper for cJSON_Print() to be used when JSON is needed to be written to a file */
int cJSON_Print_To_File(const cJSON *item, const char *file_name)
{
    int ret_value = -1;
    char *cp;
    size_t str_len;
    FILE *fout;
    
    fout = fopen(file_name, "w");
    if (NULL == fout) 
    {
        return ret_value;
    }
    
    cp = cJSON_Print(item);
    
    if (NULL != cp) 
    {
        str_len = strlen(cp);
        if (fwrite(cp, sizeof(unsigned char), str_len, fout) == str_len)
        {
            ret_value = 0;
        }
	free(cp);
	// we don't have access to global_hooks()
	// Caller must assure that malloc/free are used, otherwise we will crash! 
        //global_hooks.deallocate(cp);
    }
       
    fclose(fout);
    
    return ret_value;
}




unsigned long get_file_size(const char *file_name)
{
    unsigned long file_size = 0;
    FILE *f;
    f = fopen(file_name, "r");
    if (NULL != f) {
        fseek(f, 0, SEEK_END);
        file_size = (unsigned long ) ftell(f);
        fclose(f);
    }
    return file_size;
}



