#include <systemc.h>

// #include <cstdio>
// #include <cstring>
// #include <cstdlib>
// #include <lz4xx.h>

#include <fstream>
#include <iostream>

#include <lz4.h>

using namespace std;

SC_MODULE (hello) {  // module named hello
  SC_CTOR (hello) {  //constructor phase, which is empty in this case
  }

  void say_hello() {
    std::cout << "Hello World!" << std::endl;
  }

  void codec() {
    char szSource[] = "2013-01-07 00:00:04,0.98644,0.98676 2013-01-07 00:01:19,0.98654,0.98676 2013-01-07 00:01:38,0.98644,0.98696";
    int nInputSize = sizeof(szSource);
    printf("\n\nOriginal message: [%s]\n", szSource);
    printf("Number of bytes from the original uncompressed message = %d\n", nInputSize);

    // compress szSource into pchCompressed
    char* pchCompressed = new char[nInputSize];
    int nCompressedSize = LZ4_compress((const char *)(&szSource), pchCompressed, nInputSize);
    // int nCompressedSize = LZ4_compress_default((const char *)(&szSource), pchCompressed, nInputSize, nInputSize);
    // // int LZ4_compress_default(const char* source, char* dest, int sourceSize, int maxDestSize);
    printf("Number of bytes written into compressed buffer = %d\n\n\n", nCompressedSize);

    // write pachCompressed to binary lz4.dat
    ofstream outBinaryFile("lz4.dat",ofstream::binary);
    outBinaryFile.write(pchCompressed, nCompressedSize);
    outBinaryFile.close();
    delete[] pchCompressed;
    pchCompressed = 0;

    //read compressed binary file (assume we pass/encode nInputSize but don't know nCompressedSize)
    ifstream infCompressedBinaryFile( "lz4.dat", ifstream::binary );

    //Get compressed file size for buffer
    infCompressedBinaryFile.seekg (0,infCompressedBinaryFile.end);
    int nCompressedInputSize = infCompressedBinaryFile.tellg();
    infCompressedBinaryFile.clear();
    infCompressedBinaryFile.seekg(0,ios::beg);
    printf("Number of bytes from the received compressed buffer = %d\n", nCompressedInputSize);

    //Read file into buffer
    char* pchCompressedInput = new char[nCompressedInputSize];
    infCompressedBinaryFile.read(pchCompressedInput,nCompressedSize);
    infCompressedBinaryFile.close();

    // Decompress buffer
    char* pchDeCompressed = new char[nInputSize]; //(nCompressedInputSize *2) +8
    // LZ4_uncompress(pchCompressedInput, pchDeCompressed, nInputSize);
    LZ4_decompress_fast(pchCompressedInput, pchDeCompressed, nInputSize);
    delete[] pchCompressedInput;
    pchCompressedInput = 0;
    printf("The message was uncompressed to the original and known size = %d bytes\n", nInputSize);
    printf("Received message: [%s]\n", pchDeCompressed);

    // write decompressed pachUnCompressed to
    ofstream outFile("lz4.txt");
    outFile.write(pchDeCompressed, nInputSize);
    outFile.close();

    delete[] pchDeCompressed;
    pchDeCompressed = 0;
  }
};

int sc_main(int argc, char* argv[]) {
  hello h("hello");

  h.codec();
  return 0;
}