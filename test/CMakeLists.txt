#
# cmake for test directory of fastflow
#

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(. ${COMMON_INCLUDES})

add_executable(test_flowpath test_flowpath.cpp)
target_link_libraries(test_flowpath flowpath ${GTEST_BOTH_LIBRARIES} pthread ${OpenCV_LIBS})
add_test(test_flowpath test_flowpath)