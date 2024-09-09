// include/HuffmanCoding.h
#pragma once

#include "HuffmanNode.h"
#include <unordered_map>
#include <string>
using namespace std;
class HuffmanCoding {
private:
    unordered_map<char, string> codes;
    unordered_map<string, char> reverseMapping;
    string inputFilePath;

    unordered_map<char, int> buildFrequencyTable(const string& text);
    HuffmanNode* buildHuffmanTree(unordered_map<char, int>& freqMap);
    void generateCodes(HuffmanNode* root, string currentCode);
    string encodeText(const string& text);
    string padEncodedText(const string& encodedText);
    string removePadding(const string& paddedEncodedText);
    string decodeText(const string& encodedText);

public:
    HuffmanCoding(string path);
    void compress();
    void decompress();
};