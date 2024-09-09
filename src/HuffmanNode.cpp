// src/HuffmanNode.cpp
#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(char character, int frequency) {
    ch = character;
    freq = frequency;
    left = nullptr;
    right = nullptr;
}