#include "../include/encoder.h"
#include <lz4.h>

void Encoder::encode( void ) {

    printf("********** Running Encoder!!!! **********\n\n");

    output_ready.write(0);
    int i;

    char szSource[SIZE];
    for (i=0; i<SIZE; i++) {
        szSource[i] = buffer_LPC[i].read();
    }

    char* pchCompressed = new char[SIZE];

    int result = LZ4_compress_default((const char *)(&szSource), pchCompressed, SIZE, SIZE);

    if (result == 0) {
        printf("Compression failed! Data can't be compressed any further!\n");
        printf("Sending data just as received...\n\n");
        pchCompressed = szSource;

        for (i=0; i<SIZE; i++) {
            codec_output[i].write(*(pchCompressed+i));
        }        
    } else {
        printf("Compression success!\nCompressed file: %d bytes out of %d bytes\n", result, SIZE);
        printf("Sending compressed data!\n\n");

        for (i=0; i<SIZE; i++) {
            if (result < i) {
                codec_output[i].write(*(pchCompressed+i));
                if (*(pchCompressed+i) == 0) {
                    codec_output[i].write(-1);
                }
            } else {
                codec_output[i].write(0);
            }
        }
    }

    printf("********** Encoder finished execution!!!! **********\n\n");
    output_ready.write(1);
}