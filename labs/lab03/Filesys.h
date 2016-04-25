// Name: Mark Baltes
// ID:   004899202
// File: Filesys.h
//
// Filesys class description.

#ifndef FILESYS_H
#define FILESYS_H

#include <string>
#include <vector>
#include "../lab02/Sdisk.h"

class Filesys : public Sdisk {
public:
    Filesys(std::string diskName, int numberOfBlocks, int blockSize);
    int fsclose();
    int fssynch();
    int newFile(std::string file);
    int rmFile(std::string file);
    int getFirstBlock(std::string file);
    int addBlock(std::string file, std::string block);
    int delBlock(std::string file, int blockNumber);
    int readBlock(std::string file, int blockNumber, std::string& buffer);
    int writeBlock(std::string file, int blockNumber, std::string buffer);
    int nextBlock(std::string file, int blockNumber);
    std::vector<std::string> block(std::string buffer, int b);
    void test();
private:
    int rootSize;
    int fatSize;
    std::vector<std::string> fileName;
    std::vector<int> firstBlock;
    std::vector<int> fat;
};

#endif