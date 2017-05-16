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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <cJSON.h>
#include "../src/cjson-extras.h"
#include <CUnit/Basic.h>

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
#define VALID_JSON_FILE "../../tests/valid.json"
#define INVALID_JSON_FILE "../../tests/invalid.json"
#define NONEXISTENT_FILE "./not_there.json"
#define PRINTED_TEST_FILE "./printed_valid_json.txt"

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/

/* from cJSON (https://github.com/DaveGamble/cJSON.git) test directory */
char* read_file(const char *filename)
{
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read binary mode */
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        goto cleanup;
    }

    /* get the length */
    if (fseek(file, 0, SEEK_END) != 0)
    {
        goto cleanup;
    }
    length = ftell(file);
    if (length < 0)
    {
        goto cleanup;
    }
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        goto cleanup;
    }

    /* allocate content buffer */
    content = (char*)malloc((size_t)length + sizeof(""));
    if (content == NULL)
    {
        goto cleanup;
    }

    /* read the file into memory */
    read_chars = fread(content, sizeof(char), (size_t)length, file);
    if ((long)read_chars != length)
    {
        free(content);
        content = NULL;
        goto cleanup;
    }
    content[read_chars] = '\0';


cleanup:
    if (file != NULL)
    {
        fclose(file);
    }
    
    /* printf("file_read(%s) content is %s\n", filename, content ? "VALID" : "NULL"); */

    return content;
}

static cJSON *parse_file(const char *filename)
{
    cJSON *parsed = NULL;
    char *content = read_file(filename);

    parsed = cJSON_Parse(content);

    if (content != NULL)
    {
        free(content);
    }

    return parsed;
}


void test_all( void )
{
  cJSON *parsed;

  parsed = parse_file(VALID_JSON_FILE);

  CU_ASSERT(NULL != parsed);

  if (parsed) {
	  CU_ASSERT (0 == cJSON_Print_To_File(parsed, PRINTED_TEST_FILE));
	  cJSON_Delete(parsed);
  }

  parsed = parse_file(INVALID_JSON_FILE);

  CU_ASSERT(NULL == parsed);

  if (parsed) {
	  cJSON_Delete(parsed);
  }

  parsed = parse_file(NONEXISTENT_FILE);

  CU_ASSERT(NULL == parsed);

  if (parsed) {
	  cJSON_Delete(parsed);
  }
}


void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "cjson-extras tests", NULL, NULL );
    CU_add_test( *suite, "Test all", test_all );
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main()
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;
    

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) {
     /*   return 1; not yet! */
    }


    return 0;
}
