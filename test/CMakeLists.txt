#
# cmake for test directory of fastflow
#

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(. ${COMMON_INCLUDES})
set( BOOST_LIBRARYDIR "/usr/lib" )
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
find_package( Boost REQUIRED COMPONENTS filesystem system )

add_executable(test_flowpath test_flowpath.cpp)
target_link_libraries(test_flowpath flowpath ${GTEST_BOTH_LIBRARIES} pthread ${OpenCV_LIBS})
add_test(test_flowpath test_flowpath)

add_executable(test_fastflow test_fastflow.cpp)
target_link_libraries(test_fastflow fastflow flowpath ${GTEST_BOTH_LIBRARIES} pthread ${OpenCV_LIBS} ${Boost_LIBRARIES})
add_test(test_fastflow test_fastflow)