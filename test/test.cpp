#include <systemc.h>
#include <lz4.h>

SC_MODULE ( coder ) {
    static const int SIZE = 20;

    // typedef sc_uint<16> DataType;
    // typedef sc_in<DataType> PortType;
    // typedef sc_vector<PortType> PortVectorType;

    // PortVectorType port_vec{"my_port", SIZE};

    // sc_in< int >* buffer_LPC[SIZE];
    sc_in< sc_int<8> > buffer_LPC[SIZE];
    
    // sc_in< int > buffer_LPC[SIZE];
    // sc_vector< sc_in< sc_int<8> > > buffer_LPC{"buffer_LPC", 25};
    // sc_in< sc_int<8> > buffer_LPC[SIZE];
    sc_in< bool > window_ready;
    // sc_out< char* > codec_output; // This are the one that work(?)
    // sc_out< ofstream > codec_output; //char* or ofstream???
    // sc_out< bool > output_ready;
    sc_out< sc_int<8> > codec_output[SIZE];
    sc_out< bool > output_ready;

    void encode(void) {
        char szSource[SIZE]; // Probably need to chang this to int
        int i;
        for (i=0; i<SIZE; i++) {
            szSource[i] = buffer_LPC[i].read();
        }
        // char szSource[] = buffer_LPC.read();
        int nInputSize = sizeof(szSource);
        // printf("\n\nOriginal message: [%n]\n", szSource);
        printf("\n\nOriginal message: [");
        for (i=0; i < SIZE; i++) {
            printf(" %d ",szSource[i]);
        }
        printf("]\n");
        printf("Number of bytes from the original uncompressed message = %d\n", nInputSize);
        char* pchCompressed = new char[nInputSize];

        if (LZ4_compress_default((const char *)(&szSource), pchCompressed,
            nInputSize, nInputSize) == 0){
                
            printf("\n\nCompression greater than original message !!!\n");
            printf("Sending original data instead...\n");

            pchCompressed = szSource;
            for (i=0; i<SIZE; i++) {
                codec_output[i].write(*(pchCompressed+i));
            }
            output_ready.pos();
            printf("Data (str): %s\n", pchCompressed);
            printf("Data (int array): ");
            for (i=0; i < SIZE; i++) {
                printf("%d ", *(pchCompressed+i));
            }
            printf("\n");            
        }
        else {
            printf("Data succesfully compressed\n");

            for (i=0; i<SIZE; i++) {
                codec_output[i].write((pchCompressed+i));
            }
            output_ready.pos();
            printf("Data: %s\n", pchCompressed);
        }
        // int nCompressedSize = LZ4_compress((const char *)(&szSource), pchCompressed, nInputSize);
        // printf("Number of bytes written into compressed buffer = %d\n\n\n", nCompressedSize);
        // printf("\n\nCompressed message: [%s]\n", pchCompressed);
    }

    SC_CTOR( coder ) {
        SC_METHOD( encode );
        sensitive << window_ready.pos();
    }

    // // Example function
    // void func() {
    //     f.write( a.read() & b.read() );
    // }

    // // Example Constructor
    // SC_CTOR( and2 ) {
    //     SC_METHOD( func );
    //     sensitive << clk.neg();
    // }
};

int sc_main(int argc, char* argv[]) {
    static const int SIZE = 20;

    sc_signal< sc_int<8> > buffer_LPC_input[SIZE];
    sc_signal< bool > window_ready_input;

    sc_signal< sc_int<8> > codec_output[SIZE];
    sc_signal< bool > output_ready;

    int z;
    // for (z=0; z<SIZE; z++) {
          
    // }
    
    coder test("test_coder");
    for (z=0; z<SIZE; z++) {
        test.buffer_LPC[z](buffer_LPC_input[z]);
        buffer_LPC_input[z] = rand(); 
    }
    test.window_ready(window_ready_input);
    test.output_ready(output_ready);

    for (z=0; z<SIZE; z++) {
        test.codec_output[z](codec_output[z]);
        // buffer_LPC_input[z] = rand(); 
    }
    // sc_start();

    // for (z=0; z<4; z++) {
    //     buffer_LPC_input[z] = rand();   
    // }
    window_ready_input = true;

    sc_start();

    window_ready_input = true;

    printf("\n\nData at output: [ ");
    for (z=0; z<SIZE; z++) {
        char temp = codec_output[z].read();
        printf("%d ", temp);
        // printf(" %c", codec_output[z].read());
    }
    printf("]\n\n");


    // test.encode();
    return 0;
}









// // RANDOM MODULE EXAMPLE
// SC_MODULE ( and2 ) {
//     sc_in<DT> a, b;
//     sc_out<DT> f;
//     sc_in<bool> clk;

//     void func() {
//         f.write( a.read() & b.read() );
//     }

//     SC_CTOR( and2 ) {
//         SC_METHOD( func );
//         sensitive << clk.neg();
//     }
// }