set(PROJECT_NAME testbench)

set(CODER_INCLUDE_DIRS ../coder/include)
include_directories(CODER ${CODER_INCLUDE_DIRS})

add_executable(encoder_testbench encoder_test.cpp)
target_link_libraries(encoder_testbench systemc lz4xx coder)

add_executable(decoder_testbench decoder_test.cpp)
target_link_libraries(decoder_testbench systemc lz4xx coder)