#   Copyright 2017 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

set(PROJ_CJSON_EXTRAS cjson_extras) 

file(GLOB HEADERS cjson-extras.h)
set(SOURCES cjson-extras.c)

add_library(${PROJ_CJSON_EXTRAS} STATIC ${HEADERS} ${SOURCES})
add_library(${PROJ_CJSON_EXTRAS}.shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(${PROJ_CJSON_EXTRAS}.shared PROPERTIES OUTPUT_NAME ${PROJ_CJSON_EXTRAS})
set_property(TARGET ${PROJ_CJSON_EXTRAS} PROPERTY C_STANDARD 99)
set_property(TARGET ${PROJ_CJSON_EXTRAS}.shared PROPERTY C_STANDARD 99)

install (TARGETS ${PROJ_CJSON_EXTRAS} DESTINATION lib${LIB_SUFFIX})
install (TARGETS ${PROJ_CJSON_EXTRAS}.shared DESTINATION lib${LIB_SUFFIX})
install (FILES cjson-extras.h DESTINATION include/${PROJ_CJSON_EXTRAS})
