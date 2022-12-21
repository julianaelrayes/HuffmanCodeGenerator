//  Created by Juliana El Rayes (U03559866) and Jacob Hansen (U06857679) on 6/29/22.
// This program performs three tasks:
// 1. Given a string message, generate a HuffmanTree encoding scheme and return the same message encoded with this scheme
// 2. Convert the generated HuffmanTree into a single, serialized string
// 3. Given a serialized HuffmanTree string and an encoded message, recreate the HuffmanTree and decode the message, returning the decoded message.

#include "HuffmanTree.hpp"

void HuffmanTree::fill_charFrequencyMap(const std::string inputStr) //For use in compress()
{
    for (unsigned long int i = 0; i < inputStr.length(); i++)
    {
        auto itr = charFrequencyMap.find(inputStr[i]);
        if (itr == charFrequencyMap.end())
        {
            charFrequencyMap.insert({inputStr[i], 1});
        }
        else
        {
            charFrequencyMap[inputStr[i]] += 1;
        }
    }
}

void HuffmanTree::fill_priorityQueue() //For use in compress()
{
    for (auto i = charFrequencyMap.begin(); i != charFrequencyMap.end(); i++)
    {
        HuffmanNode* HN;
        HN = new HuffmanNode(i->first, i->second, nullptr, nullptr, nullptr);
        priorityQueue.insert(HN);
    }
}

void HuffmanTree::formTree() //For use in compress()
{
    while (priorityQueue.size() > 1)
    {
        HuffmanNode* firstPair = priorityQueue.min();
        priorityQueue.removeMin();
        HuffmanNode* secondPair = priorityQueue.min();
        priorityQueue.removeMin();
        HuffmanNode* sum = new HuffmanNode('\0', (firstPair->getFrequency() + secondPair->getFrequency()), nullptr, firstPair, secondPair);
        firstPair->parent = sum;
        secondPair->parent = sum;
        priorityQueue.insert(sum);
    }
}

void HuffmanTree::makeCode() //For use in compress()
{
    std::string binaryCode = "";
    traverseAndTrack(priorityQueue.min(), binaryCode);
}

void HuffmanTree::traverseAndTrack(const HuffmanNode* node, std::string binaryCode) //For use in compress()
{
    if (node->isLeaf() == true)
    {
        prefixCodesMap.insert({node->getCharacter(), binaryCode});
    }
    
    if (node->isBranch() == true)
    {
        traverseAndTrack(node->left, (binaryCode + '0'));
        traverseAndTrack(node->right, (binaryCode + '1'));
    }
}

std::string HuffmanTree::encode(const std::string inputStr) //For use in compress()
{
    std::string outputStr = "";
    for (unsigned long int i = 0; i < inputStr.length(); i++)
    {
        auto itr = prefixCodesMap.find(inputStr[i]);
        outputStr += itr->second;
    }
    return outputStr;
}

std::string HuffmanTree::compress(const std::string inputStr) //Given an input string, generate a Huffman encoding tree and return a string representing the input string encoded with the Huffman scheme
{
    fill_charFrequencyMap(inputStr);
    fill_priorityQueue();
    formTree();
    makeCode();
    root = priorityQueue.min();
    return encode(inputStr);
}

void HuffmanTree::postorder(const HuffmanNode* node, std::string &serialized) const //For use in serializeTree()
{
    if (node->isBranch() == true)
    {
        postorder(node->left, serialized);
    }
    
    if (node->isBranch() == true)
    {
        postorder(node->right, serialized);
        serialized += 'B';
    }
    
    if (node->isLeaf() == true)
    {
        serialized += 'L';
        serialized += node->getCharacter();
    }
}

std::string HuffmanTree::serializeTree() const //Creates the serialized tree string
{
    std::string serialized = "";
    postorder(root, serialized);
    return serialized;
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) //Given an encoded message and serialized Huffman Tree, recreates the Huffman tree and translates the encoded message back into its original form
{
    for (unsigned int i = 0; i < serializedTree.length();)
    {
        if (serializedTree[i] == 'L')
        {
            HuffmanNode* HN;
            HN = new HuffmanNode(serializedTree[i+1], 0, nullptr, nullptr, nullptr);
            deserializedTree.push(HN);
            i += 2;
        }
        else if (serializedTree[i] == 'B')
            {
                HuffmanNode* rightChild = deserializedTree.top();
                deserializedTree.pop();
                HuffmanNode* leftChild = deserializedTree.top();
                deserializedTree.pop();
                HuffmanNode* papa = new HuffmanNode('\0', 0, nullptr, leftChild, rightChild);
                leftChild->parent = papa;
                rightChild->parent = papa;
                deserializedTree.push(papa);
                i++;
            }
            else
            {
                throw "Unexpected character encountered.";
            }
    }
    
    return translate(inputCode, deserializedTree.top());
}

std::string HuffmanTree::translate(const std::string inputCode, const HuffmanNode* node) //For use in decompress()
{
    const HuffmanNode* root = node;
    std::string decodedString = "";
    
    for (unsigned long int i = 0; i < inputCode.length(); i++)
    {
        if (inputCode[i] == '0')
        {
            node = node->left;
        }
        else if (inputCode[i] == '1')
            {
                node = node->right;
            }
            else
            {
                throw "Encountered non-binary digit";
            }
        
        if (node->isLeaf() == true)
        {
            decodedString += node->getCharacter();
            node = root;
        }
    }
    return decodedString;
}
