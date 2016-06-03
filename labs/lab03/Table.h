// Name: Mark Baltes
// ID:   004899202
// File: Table.h
//
// Table class description.

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "Filesys.h"

class Table : public Filesys {
public:
    Table(std::string diskName, int numberOfBlocks, int blockSize,
          std::string flatFile, std::string indexFile);
    int buildTable(std::string inputFile);
    std::string search(int value);
private:
    std::string flatFile;
    std::string indexFile;
    int numberOfRecords;
    //Filesys fileSystem;
    int indexSearch(int value);
    std::vector<int> key;
    std::vector<int> blockID;
};

#endif