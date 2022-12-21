//  Created by Juliana El Rayes (U03559866) and Jacob Hansen (U06857679) on 6/29/22.

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <stack>
#include <string>

#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase
{
public:
    std::string compress(const std::string inputStr); //Given an input string, generate a Huffman encoding tree and return a string representing the input string encoded with the Huffman scheme
    void fill_charFrequencyMap(const std::string inputStr); //Calculate the frequency of each character and store in a map
    void fill_priorityQueue(); //Create a priority queue with each node containing the frequency of a character (key) and the character itself (value)
    void formTree(); //Merge the priority queue nodes into a Huffman Code Tree
    void makeCode(); //Create the prefix codes for the characters in the string using a map
    void traverseAndTrack(const HuffmanNode* node, std::string binaryCode); //Uses preorder traversal of the HuffmanTree and calculates the prefix codes for each character in the tree
    std::string encode(const std::string inputStr); //Replaces the characters in the inputStr with the corresponding Huffman codes and returns the encoded string
    
    void postorder(const HuffmanNode* node, std::string &serialized) const; //Traverses the HuffmanTree in postorder and creates the serialized tree string
    std::string serializeTree() const; //Using the postorder function, creates the serialized tree string

    std::string decompress(const std::string inputCode, const std::string serializedTree); //Given an encoded message and serialized Huffman Tree, recreates the Huffman tree and returns the encoded message in its original form
    std::string translate(const std::string inputCode, const HuffmanNode* node); //Function to decode and return a Huffman encoded message given the encoded message and root node of a deserialized Huffman tree
    
private:
    std::map<char,int> charFrequencyMap;
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;
    std::map<char, const std::string> prefixCodesMap;
    HuffmanNode* root;
    std::stack<HuffmanNode*> deserializedTree;
};

#endif /* HUFFMAN_H */
