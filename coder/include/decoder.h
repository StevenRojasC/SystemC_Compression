/* File decoder.h */

#include <systemc.h>

static const int SIZE = 26*8;

SC_MODULE ( Decoder ) {
    sc_in< sc_int<8> > coded_input[SIZE];
    sc_in< bool > buffer_ready;

    sc_out< sc_int<8> > buffer_LPC[SIZE];
    sc_out< bool > output_ready;

    sc_event dec_t;

    void decode(void);

    void dec(void);

    SC_CTOR( Decoder ) {
        SC_METHOD( decode );
        // sensitive << buffer_ready.pos();
        dont_initialize();
    }
};