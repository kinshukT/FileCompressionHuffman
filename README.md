# Huffman Coding Project

This project implements the Huffman Coding algorithm for text compression and decompression. Huffman Coding is a lossless data compression technique that assigns variable-length codes to characters based on their frequency of occurrence.

## Project Structure

```
HuffmanCoding/
├── src/
│   ├── main.cpp
│   ├── HuffmanCoding.cpp
│   ├── HuffmanNode.cpp
├── include/
│   ├── HuffmanCoding.h
│   ├── HuffmanNode.h
├── input/
│   ├── sample.txt
├── output/
│   ├── (compressed and decompressed files will be saved here)
├── CMakeLists.txt
├── README.md
```

## How to Run

1. Ensure you have CMake and a C++ compiler (like MinGW) installed on your system.

2. Clone or download this repository.

3. Navigate to the project directory and create a build folder:
   ```
   cd path/to/HuffmanCoding
   mkdir build
   cd build
   ```

4. Generate the build files using CMake:
   ```
   cmake -G "MinGW Makefiles" ..
   ```

5. Build the project:
   ```
   mingw32-make
   ```

6. Run the program with an input file:
   ```
   .\HuffmanCoding.exe ..\input\sample.txt
   ```

   Replace `sample.txt` with the name of your input file.

7. Check the build/output folder for the compressed (.bin) and decompressed files.

## Algorithm Logic

The Huffman Coding algorithm works as follows:

1. **Frequency Analysis**: 
   - The program reads the input file and counts the frequency of each character.

2. **Building the Huffman Tree**:
   - Create a leaf node for each character and add it to a priority queue.
   - Repeatedly remove the two nodes with the lowest frequency from the queue.
   - Create a new internal node with these two nodes as children, with frequency equal to the sum of the two nodes' frequencies.
   - Add the new node back into the queue.
   - Repeat until only one node remains (the root of the Huffman tree).

3. **Generating Huffman Codes**:
   - Traverse the Huffman tree, assigning '0' for left branches and '1' for right branches.
   - The path from the root to a leaf node gives the Huffman code for the character in that leaf.

4. **Compression**:
   - Replace each character in the input text with its Huffman code.
   - Pad the resulting binary string to ensure its length is a multiple of 8.
   - Write the padded binary string to the output file as bytes.

5. **Decompression**:
   - Read the compressed file and convert it back to a binary string.
   - Remove the padding.
   - Traverse the Huffman tree based on the bits in the binary string to recover the original characters.

## Key Components

- `HuffmanNode`: Represents a node in the Huffman tree.
- `HuffmanCoding`: Main class that handles the compression and decompression logic.
- `buildFrequencyTable()`: Creates a frequency map of characters.
- `buildHuffmanTree()`: Constructs the Huffman tree using a priority queue.
- `generateCodes()`: Generates Huffman codes for each character.
- `compress()`: Compresses the input file.
- `decompress()`: Decompresses the compressed file.

## Efficiency

Huffman Coding provides efficient compression for text files where character frequencies vary significantly. The time complexity for both compression and decompression is O(n log k), where n is the number of characters in the text and k is the number of unique characters.

## Limitations

- This implementation is designed for text files and may not be optimal for binary files.
- The compressed file includes the Huffman codes, which adds some overhead for small files.
- Very large files might cause memory issues as the entire file is read into memory.

## Future Improvements

- Implement adaptive Huffman Coding for better compression of dynamic content.
- Add support for compressing directories or multiple files.
- Optimize memory usage for handling very large files.
