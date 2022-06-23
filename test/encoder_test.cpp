#include <systemc.h>
#include <encoder.h>

static const int input_range = int(pow(2, 8));
static const int n_max_exe = 10;

SC_MODULE (encoder_test) {
    sc_signal< sc_int<8> > buffer_LPC_input[SIZE];
    sc_signal< bool, SC_MANY_WRITERS > window_ready_input;

    sc_signal< sc_int<8> > codec_output_port[SIZE];
    sc_signal< bool, SC_MANY_WRITERS > block_ready_output;

    int exe_counter = 0;

    // Trace file
    sc_trace_file *pTraceFile;

    Encoder *uut;

    SC_CTOR(encoder_test)
    {
        // Defining and identifying signals
        int z;
        uut = new Encoder("uut"); 

        for (z = 0; z < SIZE; z++) {
            uut->buffer_LPC[z](buffer_LPC_input[z]);
            uut->codec_output[z](codec_output_port[z]);
        }
        uut->window_ready( window_ready_input );
        uut->output_ready( block_ready_output );


        // // trace file
        // pTraceFile = sc_create_vcd_trace_file( "encoder_testbench" );

        // // tracing signals to waveforms
        // sc_trace(pTraceFile, window_ready_input, "window_ready_input");
        // sc_trace(pTraceFile, block_ready_output, "output_ready");
        // sc_trace(pTraceFile, buffer_LPC_input, "buffer_LPC_input");
        // sc_trace(pTraceFile, codec_output_port, "codec_output_port");


        SC_METHOD (execution_counter);
        sensitive << block_ready_output.posedge_event();

        SC_METHOD (print_input_values);
        sensitive << buffer_LPC_input[0];
        dont_initialize();

        SC_METHOD (print_output_values);
        sensitive << block_ready_output.posedge_event();
        dont_initialize();
    }


    void write_random_inputs(void) {

        int z;
        for (z=0; z<SIZE; z++) {
            int temp = (rand() % input_range) - (input_range/2); // Random generation of inputs
            buffer_LPC_input[z].write(temp);
        }
        printf("Wrote random values at input !!!\n\n");
    }

    void print_input_values(void) {
        int z;
        printf("Current data at input: [ ");
        for (z=0; z<SIZE; z++) {
            int temp1 = buffer_LPC_input[z].read();
            printf("%d ", temp1);
        }
        printf("]\n\n");
        block_ready_output.write(0);
        window_ready_input.write(1);
    }

    void print_output_values(void) {
        int z;
        printf("Data at output: [ ");
        for (z=0; z<SIZE; z++) {
            char temp = codec_output_port[z].read();
            printf("%d ", temp);
        }
        printf("]\n\n\n\n");
        window_ready_input.write(0);
    }

    void execution_counter(void) {
        if (exe_counter >= n_max_exe) {
            delete uut;
            exit;
        } else {
            exe_counter += 1;
            printf("\nCounter: %d\n", exe_counter);
            write_random_inputs();
        }
    }

    ~encoder_test() {
        // sc_close_vcd_trace_file( pTraceFile );
    }
};




int sc_main(int argc, char* argv[]) {

    printf("\nStarting Testbench........\n\n");
    encoder_test encoder_testbench("encoder_testbench");

    sc_start();



    sc_stop();

    printf("\n\nTestbench Ended........\n\n");

    return 0;
}