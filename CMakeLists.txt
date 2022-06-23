cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project (SampleProject CXX C)

set(SYSTEMC_PATH submodules/systemc)
# set(SYSTEMC_INCLUDE_DIRS ${SYSTEMC_PATH}/src)
add_subdirectory(${SYSTEMC_PATH})
# include_directories(SYSTEM ${SYSTEMC_INCLUDE_DIRS})

set(LZ4XX_PATH submodules/lz4xx)
set(LZ4XX_INCLUDE_DIRS ${LZ4XX_PATH}/include)
add_subdirectory(${LZ4XX_PATH})
include_directories(LZ4XX ${LZ4XX_INCLUDE_DIRS})

add_subdirectory(test)
add_subdirectory(coder)