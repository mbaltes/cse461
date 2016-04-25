// Helper function for project. 
// Takes a string and blocks it for filesystem.

#include <string>
#include <vector>

std::vector<std::string> block(std::string buffer, int b) {
    std::vector<std::string> blocks;
    int numberOfBlocks = 0;

    if (buffer.length() % b == 0) {
        numberOfBlocks = buffer.length() / b;
    } else {
        numberOfBlocks = buffer.length() / (b + 1);
    }

    std::string tempBlock;
    for (int i = 0; i < numberOfBlocks; i++) {
        tempBlock = buffer.substr(b * i, b);
        blocks.push_back(tempBlock);
    }

    int lastBlock = blocks.size() - 1;

    for (int i = blocks[lastBlock].length(); i < b; i++) {
        blocks[lastBlock] += "#";
    }

    return blocks;
}