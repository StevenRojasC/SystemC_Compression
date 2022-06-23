#!/usr/bin/env bash

set -e

[ ! -d build ] && mkdir build
(
    cd build
    cmake ..
    cmake --build .
    while getopts "ed" flags; do
        case $flags in
            e) # Flag "-e" to run encoder
                printf "\n\nRunning tests...\n\n"
                ../build/test/encoder_testbench
                ;;
            d) # Flag "-d" to run decoder
                printf "\n\nRunning tests...\n\n"
                ../build/test/decoder_testbench
                ;;
        esac
    done
)