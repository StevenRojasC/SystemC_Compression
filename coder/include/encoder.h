/* File encoder.h */

#include <systemc.h>

static const int SIZE = 26*8;

SC_MODULE ( Encoder ) {
    sc_in< sc_int<8> > buffer_LPC[SIZE];
    sc_in< bool > window_ready;

    sc_out< sc_int<8> > codec_output[SIZE];
    sc_out< bool > output_ready;

    void encode(void);

    SC_CTOR( Encoder ) {
        SC_METHOD( encode );
        sensitive << window_ready.pos();
        dont_initialize();
    }
};