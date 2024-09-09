// src/main.cpp
#include "HuffmanCoding.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file_path>" << endl;
        return 1;
    }

    string filePath = argv[1];
    cout << "Input file path: " << filePath << endl;

    HuffmanCoding huffman(filePath);

    cout << "Starting compression..." << endl;
    huffman.compress();
    cout << "Compression completed." << endl;

    cout << "Starting decompression..." << endl;
    huffman.decompress();
    cout << "Decompression completed." << endl;

    return 0;
}