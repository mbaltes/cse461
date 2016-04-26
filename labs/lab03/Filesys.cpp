// Name: Mark Baltes
// ID:   004899202
// File: Filesys.cpp
//
// Filesys class implementation.

#include "Filesys.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iomanip>

Filesys::Filesys(std::string diskName, int numberOfBlocks, int blockSize) 
    : Sdisk(diskName, numberOfBlocks, blockSize) {
    // Calculate rootSize and fatSize
    rootSize = blockSize / 12;
    fatSize = (6 * numberOfBlocks) / blockSize + 1;

    // If no filesystem exists on disk, build one and synch. If a filesystem
    // exists, read in to ROOT and FAT and synch.
    std::string buffer;
    getBlock(0, buffer);

    if (buffer[0] == '#') { // No filesystem exists
        std::cout << "Creating fs..." << '\n';
        for (int i = 1; i <= rootSize; i++) {
            fileName.push_back("xxxxx");
            firstBlock.push_back(0);
        }
        fat.push_back(fatSize + 1);
        for (int i = 1; i <= fatSize; i++) {
            fat.push_back(0);
        }
        for (int i = fatSize + 1; i <= numberOfBlocks - 1; i++) {
            fat.push_back(i + 1);
        }
        fat[numberOfBlocks - 1] = 0;
        // ROOT and FAT created, now write to disk.
        fssynch();
    } else {
        // Filesys exists, read in ROOT and FAT.
        std::cout << "Reading fs..." << '\n';
        std::string readBuffer, file;
        int block;
        getBlock(0, readBuffer);
        std::istringstream instream;
        instream.str(readBuffer);
        for (int i = 0; i < rootSize; i++) {
            instream >> file >> block;
            fileName.push_back(file);
            firstBlock.push_back(block);
        }
        // Read in FAT
        std::string tempBuffer, fatBuffer;
        for (int i = 1; i <= fatSize; i++) {
            getBlock(i, tempBuffer);
            fatBuffer += tempBuffer;
        }
        
        std::istringstream instream2(tempBuffer);
        int toInt;
        for (int i = 0; i < numberOfBlocks; i++) {
            instream2 >> toInt;
            fat.push_back(toInt);
        }

        fssynch();
    }

}

int Filesys::fsclose() {
    //
}

int Filesys::fssynch() {
    // Write FAT to Sdisk.
    std::string buffer;
    std::ostringstream outstream, outstream2;
    for (int i = 0; i < getNumberOfBlocks(); i++) {
        outstream << std::setfill('0') << std::setw(5)<< fat[i] << " ";
    }
    buffer = outstream.str();
    // Block before writing
    std::vector<std::string> blocks = block(buffer, getBlocksize());
    std::cout << "blocks size: " << blocks.size() << '\n';
    for (int i = 1; i <= blocks.size(); i++) {
        std::cout << blocks[i-1] << '\n';
        putBlock(i, blocks[i - 1]);
    }

    // Now write root to disk
    for (int i = 0; i < rootSize; i++) {
        outstream2 << fileName[i] << " " << std::setfill('0') 
                   << std::setw(5) << firstBlock[i] << " ";
    }
    buffer = outstream2.str();
    std::cout << "Root buffer: " << buffer << '\n';
    blocks.clear();
    blocks = block(buffer, getBlocksize());
    std::cout << "blocks size: " << blocks.size() << '\n';
    for (int i = 0; i < blocks.size(); i++) {
        putBlock(i, blocks[i]);
    }
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

std::vector<std::string> Filesys::block(std::string buffer, int b) {
    std::vector<std::string> blocks;
    int numberOfBlocks = 0;

    if (buffer.length() % b == 0) {
        numberOfBlocks = buffer.length() / b;
    } else {
        numberOfBlocks = buffer.length() / b + 1;
    }

    std::string tempBlock;
    for (int i = 0; i < numberOfBlocks; i++) {
        tempBlock = buffer.substr(b * i, b);
        blocks.push_back(tempBlock);
    }

    int lastBlock = blocks.size() - 1;

    for (int i = blocks[lastBlock].length(); i < b; i++) {
        blocks[lastBlock] += '#';
    }
    return blocks;
}

void Filesys::test() {
    std::cout << "Rootsize: " << rootSize << '\n';
    std::cout << "Fatsize: " << fatSize << '\n';
    std::cout << "Iterating filename vector... " << '\n';
    for (int i = 0; i < fileName.size(); i++) {
        std::cout << fileName[i] << '\n';
    }

    std::cout << "Iterating firstBlock vector... " << '\n';
    for (int i = 0; i < firstBlock.size(); i++) {
        std::cout << firstBlock[i] << '\n';
    }

    std::cout << "Iterating FAT vector... " << '\n';
    for (int i = 0; i < fat.size(); i++) {
        std::cout << fat[i] << '\n';
    }
}
