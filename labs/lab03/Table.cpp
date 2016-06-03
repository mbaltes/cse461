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
#include <stdexcept>

Table::Table(std::string diskName, int numberOfBlocks, int blockSize, 
    std::string flatFile, std::string indexFile)
    : Filesys(diskName, numberOfBlocks, blockSize) {
    this-> flatFile = flatFile;
    this-> indexFile = indexFile;
    newFile(flatFile);
    newFile(indexFile);
}

int Table::buildTable(std::string inputFile) {
    int iKey;
    int bID;
    std::ifstream infile;
    infile.open(inputFile.c_str());
    std::string rec;
    getline(infile, rec);
    while (infile.good()) {
        // process rec
        std::string key = rec.substr(0, 5);
        iKey = atoi(key.c_str());
        std::vector<std::string> b = block(rec, getBlocksize());
        bID = addBlock(flatFile, b[0]);
        this->key.push_back(iKey);
        blockID.push_back(bID);
        getline(infile, rec);
    }
    infile.close();
    return 1;
}
    
std::string Table::search(int value) {
    int block = indexSearch(value);
    if (block == 0) { // Value not found.
        return "Search value not found.";
    } else {
        std::string record;
        readBlock(flatFile, block, record);
        return record;
    }
}

int Table::indexSearch(int value) {
    // Search key vector for value
    for (int i = 0; i < key.size(); i++) {
        if (value == key[i]) { 
            return blockID[i];
        }
    }
    return 0; // Not found.
}