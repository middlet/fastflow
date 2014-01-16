#
# cmake file for fastflow
#

project( FFLOW )
cmake_minimum_required( VERSION 2.8 )
add_definitions( -Wall -pthread -g )

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)