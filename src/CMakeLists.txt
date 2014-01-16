#
# cmake for src directory of fastflow
#


find_package( OpenCV REQUIRED )
set( BOOST_LIBRARYDIR "/usr/lib" )
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
find_package( Boost REQUIRED COMPONENTS filesystem system )

include_directories(. ${COMMON_INCLUDES} )

# include opencv

add_executable(fflow fastflow.cpp flowpath.cpp main.cpp)
target_link_libraries( fflow ${OpenCV_LIBS} ${Boost_LIBRARIES} )

# build static library for testing
add_library(flowpath STATIC "flowpath.cpp")

