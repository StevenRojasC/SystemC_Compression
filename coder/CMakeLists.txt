add_library(coder   src/encoder.cpp
                    src/decoder.cpp
                    include/encoder.h
                    include/decoder.h)

target_link_libraries(coder systemc lz4xx)