// Name: Mark Baltes
// ID:   004899202
// File: Sdisk.h
//
// Sdisk class description.

#include <string>

class Sdisk {
public:
    Sdisk(std::string diskName, int numberOfBlocks, int blockSize);
    int getBlock(int blockNumber, std::string& buffer);
    int putBlock(int blockNumber, std::string buffer);
    int getNumberOfBlocks();
    int getBlocksize();
private:
    std::string diskName;
    int numberOfBlocks;
    int blockSize;
};