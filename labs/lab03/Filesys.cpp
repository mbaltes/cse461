// Name: Mark Baltes
// ID:   004899202
// File: Filesys.cpp
//
// Filesys class implementation.

#include "Filesys.h"
#include <stdexcept>

Filesys::Filesys() {
    // 
}

int Filesys::fsclose() {
    //
}
int Filesys::fssynch() {
    //
}

int Filesys::newFile(std::string file) {
    //
}

int Filesys::rmFile(std::string file) {
    //
}

int Filesys::getFirstBlock(std::string file) {
    //
}

int Filesys::addBlock(std::string file, std::string block) {

}

int Filesys::delBlock(std::string file, int blockNumber) {
    //
}

int Filesys::readBlock(std::string file, int blockNumber, std::string& buffer) {
    //
}

int Filesys::writeBlock(std::string file, int blockNumber, std::string buffer) {
    //
}

int Filesys::nextBlock(std::string file, int blockNumber) {
    //
}
