// Name: Mark Baltes
// ID:   004899202
// File: Filesys.h
//
// Filesys class description.

#include <string>
#include <vector>
#include "../Sdisk.h"

class Filesys : public Sdisk {
public:
    Filesys();
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
private:
    int rootSize;
    int fatSize;
    std::vector<string> fileName;
    std::vector<int> firstBlock;
    std::vector<int> fat;
};