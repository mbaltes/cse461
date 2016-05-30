// Name: Mark Baltes
// ID:   004899202
// File: Table.cpp
//
// Table class implementation.

#include "Table.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

Table::Table(std::string diskName, int numberOfBlocks, int blockSize, 
    std::string flatFile, std::string indexFile)
    : Filesys(diskName, numberOfBlocks, blockSize) {
    this-> flatFile = flatFile;
    this-> indexFile = indexFile;
    newFile(flatFile);
    newFile(indexFile);
}

int Table::buildTable(std::string inputFile) {
    std::ifstream infile;
    infile.open(inputFile.c_str());
    std::string rec;
    getline(infile, rec);
    while (infile.good()) {
        // process rec
        std::string key = rec.substr(0, 5);
        int iKey = atoi(key.c_str());
        std::vector<std::string> b = block(rec, getBlocksize());
        int bID = addBlock(flatFile, b[0]);
        key.push_back(iKey);
        blockID.push_back(bID);
        getline(infile, rec);
    }
    return 1;
}
    
std::string Table::search(int value) {
    //
}