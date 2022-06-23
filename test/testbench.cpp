#include <systemc.h>
#include <coder.h>

// static const int SIZE = 20;

int sc_main(int argc, char* argv[]) {
    
    sc_signal< sc_int<8> > buffer_LPC_input[SIZE];
    sc_signal< bool > window_ready_input;

    sc_signal< sc_int<8> > codec_output[SIZE];
    sc_signal< bool > output_ready;

    int z;
    
    /* This section initializes the coder module and 
        it's inputs and outputs */
    Coder coder("coder_module");
    printf("\nData at input: [ ");
    for (z=0; z<SIZE; z++) {
        coder.buffer_LPC[z](buffer_LPC_input[z]);
        coder.codec_output[z](codec_output[z]);

        buffer_LPC_input[z] = rand(); // Random generation of inputs
        char* temp = buffer_LPC_input[z];
        printf("%d ", *temp);
    }
    coder.window_ready(window_ready_input);
    coder.output_ready(output_ready);

    // window_ready_input = true;

    sc_start();

    // window_ready_input = true;

    /* This section prints the result at the output */
    printf("\n\nData at output: [ ");
    for (z=0; z<SIZE; z++) {
        char temp = codec_output[z].read();
        printf("%d ", temp);
    }
    printf("]\n\n");

    return 0;
}