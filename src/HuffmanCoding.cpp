// src/HuffmanCoding.cpp
#include "HuffmanCoding.h"
#include <fstream>
#include <bitset>
#include <iostream>
#include <sstream>
#include <queue>
#include <sys/stat.h>
#include <direct.h>

using namespace std;

bool directoryExists(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool createDirectory(const string& path) {
    return _mkdir(path.c_str()) == 0;
}

size_t getFileSize(const string& filename) {
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
}

HuffmanCoding::HuffmanCoding(string path) : inputFilePath(path) {
    cout << "Initializing HuffmanCoding with input file: " << path << endl;
}

unordered_map<char, int> HuffmanCoding::buildFrequencyTable(const string& text) {
    unordered_map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    cout << "Frequency table built. Unique characters: " << freqMap.size() << endl;
    return freqMap;
}

HuffmanNode* HuffmanCoding::buildHuffmanTree(unordered_map<char, int>& freqMap) {
    auto compare = [](HuffmanNode* left, HuffmanNode* right) { return left->freq > right->freq; };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(compare)> pq(compare);

    for (const auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    cout << "Huffman tree built." << endl;
    return pq.top();
}

void HuffmanCoding::generateCodes(HuffmanNode* root, string currentCode) {
    if (root == nullptr) return;

    if (root->ch != '\0') {
        codes[root->ch] = currentCode;
        reverseMapping[currentCode] = root->ch;
    }

    generateCodes(root->left, currentCode + "0");
    generateCodes(root->right, currentCode + "1");
}

string HuffmanCoding::encodeText(const string& text) {
    string encodedText;
    for (char c : text) {
        encodedText += codes[c];
    }
    cout << "Text encoded. Encoded length: " << encodedText.length() << " bits" << endl;
    return encodedText;
}

string HuffmanCoding::padEncodedText(const string& encodedText) {
    int padding = 8 - (encodedText.length() % 8);
    string paddedText = encodedText + string(padding, '0');
    paddedText = bitset<8>(padding).to_string() + paddedText;
    cout << "Encoded text padded. Final length: " << paddedText.length() << " bits" << endl;
    return paddedText;
}

void HuffmanCoding::compress() {
    cout << "Starting compression process..." << endl;

    ifstream inFile(inputFilePath);
    if (!inFile) {
        cerr << "Error: Unable to open input file: " << inputFilePath << endl;
        return;
    }

    stringstream buffer;
    buffer << inFile.rdbuf();
    string text = buffer.str();
    inFile.close();

    cout << "Input file read. Text length: " << text.length() << " characters" << endl;

    auto freqMap = buildFrequencyTable(text);
    HuffmanNode* root = buildHuffmanTree(freqMap);
    generateCodes(root, "");

    cout << "Huffman codes generated. Number of codes: " << codes.size() << endl;

    string encodedText = encodeText(text);
    string paddedEncodedText = padEncodedText(encodedText);

    // Ensure output directory exists
    if (!directoryExists("output")) {
        cout << "Creating output directory..." << endl;
        if (!createDirectory("output")) {
            cerr << "Error: Unable to create output directory" << endl;
            return;
        }
    }

    size_t lastSlash = inputFilePath.find_last_of("/\\");
    string fileName = inputFilePath.substr(lastSlash + 1);
    string compressedFilePath = "output/" + fileName + ".bin";

    ofstream outFile(compressedFilePath, ios::binary);
    if (!outFile) {
        cerr << "Error: Unable to open output file: " << compressedFilePath << endl;
        return;
    }

    for (size_t i = 0; i < paddedEncodedText.size(); i += 8) {
        bitset<8> byte(paddedEncodedText.substr(i, 8));
        outFile.put(static_cast<unsigned char>(byte.to_ulong()));
    }
    outFile.close();

    cout << "File compressed successfully. Output: " << compressedFilePath << endl;
    cout << "Original size: " << text.length() << " bytes" << endl;
    cout << "Compressed size: " << getFileSize(compressedFilePath) << " bytes" << endl;
}

string HuffmanCoding::removePadding(const string& paddedEncodedText) {
    int padding = bitset<8>(paddedEncodedText.substr(0, 8)).to_ulong();
    return paddedEncodedText.substr(8, paddedEncodedText.length() - 8 - padding);
}

string HuffmanCoding::decodeText(const string& encodedText) {
    string decodedText;
    string currentCode;
    for (char bit : encodedText) {
        currentCode += bit;
        if (reverseMapping.find(currentCode) != reverseMapping.end()) {
            decodedText += reverseMapping[currentCode];
            currentCode.clear();
        }
    }
    cout << "Text decoded. Decoded length: " << decodedText.length() << " characters" << endl;
    return decodedText;
}

void HuffmanCoding::decompress() {
    cout << "Starting decompression process..." << endl;

    size_t lastSlash = inputFilePath.find_last_of("/\\");
    string fileName = inputFilePath.substr(lastSlash + 1);
    string compressedFilePath = "output/" + fileName + ".bin";

    ifstream inFile(compressedFilePath, ios::binary);
    if (!inFile) {
        cerr << "Error: Unable to open compressed file: " << compressedFilePath << endl;
        return;
    }

    string bitString = "";
    unsigned char byte;
    while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
        bitString += bitset<8>(byte).to_string();
    }
    inFile.close();

    cout << "Compressed file read. Bit string length: " << bitString.length() << " bits" << endl;

    // Remove padding and decode the text
    string encodedText = removePadding(bitString);
    string decompressedText = decodeText(encodedText);

    // Ensure output directory exists
    if (!directoryExists("output")) {
        cout << "Creating output directory..." << endl;
        if (!createDirectory("output")) {
            cerr << "Error: Unable to create output directory" << endl;
            return;
        }
    }

    string decompressedFilePath = "output/" + fileName + "_decompressed.txt";

    ofstream outFile(decompressedFilePath);
    if (!outFile) {
        cerr << "Error: Unable to open output file: " << decompressedFilePath << endl;
        return;
    }

    outFile << decompressedText;
    outFile.close();

    cout << "File decompressed successfully. Output: " << decompressedFilePath << endl;
    cout << "Decompressed size: " << getFileSize(decompressedFilePath) << " bytes" << endl;
}