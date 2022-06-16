cmake_minimum_required (VERSION 3.1)

project (SampleProject CXX C)

set(SYSTEMC_PATH submodules/systemc)
# set(SYSTEMC_INCLUDE_DIRS ${SYSTEMC_PATH}/src)
add_subdirectory(${SYSTEMC_PATH})
# include_directories(SYSTEM ${SYSTEMC_INCLUDE_DIRS})

set(LZ4XX_PATH submodules/lz4xx)
add_subdirectory(${LZ4XX_PATH})

add_subdirectory(test)