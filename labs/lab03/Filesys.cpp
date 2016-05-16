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
    //std::cout << "blocks size: " << blocks.size() << '\n';
    for (int i = 1; i <= blocks.size(); i++) {
        //std::cout << blocks[i-1] << '\n';
        putBlock(i, blocks[i - 1]);
    }

    // Now write root to disk
    for (int i = 0; i < rootSize; i++) {
        outstream2 << fileName[i] << " " << std::setfill('0') 
                   << std::setw(5) << firstBlock[i] << " ";
    }
    buffer = outstream2.str();
    //std::cout << "Root buffer: " << buffer << '\n';
    blocks.clear();
    blocks = block(buffer, getBlocksize());
    //std::cout << "blocks size: " << blocks.size() << '\n';
    for (int i = 0; i < blocks.size(); i++) {
        putBlock(i, blocks[i]);
    }
}

int Filesys::newFile(std::string file) {
    // Need to make sure the filename length is < 6
    if (file.length() > 5) {
        throw std::invalid_argument("Cannot add file. Filename too long.");
        return 0;
    }
    for (int i = 0; i < fileName.size(); i++) {
        // Don't allow overwriting of files.
        if (fileName[i] == file) {
            throw std::invalid_argument("File already exists.");
            return 0;
        } else if (fileName[i] == "xxxxx") { // File available.
            fileName[i] = file;
            fssynch();
            return 1;
        }
    }
    // If here, there is no free space available.
    throw std::invalid_argument("No free space for additional files.");
    return 0;
}

int Filesys::rmFile(std::string file) {
    for (int i = 0; i < fileName.size(); i++) {
        if (fileName[i] == file) {
            // Don't remove if firstblock is not empty.
            if (getFirstBlock(file) != 0) {
                throw std::invalid_argument("Cannot remove non-empty file.");
                return 0;
            } else {
                // File is empty and thus removeable.
                fileName[i] = "xxxxx";
                fssynch();
                return 1;
            }
        }
    }
    // File doesn't exist.
    throw std::invalid_argument("Cannot delete file that doesn't exist.");
    return 0;
}

int Filesys::getFirstBlock(std::string file) {
    for (int i = 0; i < fileName.size(); i++) {
        if (fileName[i] == file) {
            return firstBlock[i];
        }
    }
    // File doesn't exist.
    throw std::invalid_argument("Cannot get first block of non-existing file.");
    return 0;
}

int Filesys::addBlock(std::string file, std::string block) {
    int allocate;
    int fileBlock = getFirstBlock(file);
    if (fileBlock == -1) { // No available blocks; fs full.
        throw std::invalid_argument("Cannot add block. File doesn't exist.");
        return 0;
    } else if (fileBlock == 0) { // No blocks in file, OK to add.
        allocate = fat[0];
        if (allocate == 0) { // Disk is full.
            throw std::invalid_argument("Disk is full, cannot add block.");
            return -1;
        } else {
            fat[0] = fat[fat[0]];
            fat[allocate] = 0;
            // Update root
            for (int i = 0; i < fileName.size(); i++) {
                if (fileName[i] == file) {
                    firstBlock[i] = allocate;
                }
            }
        }
    } else { // File already has blocks. 
        allocate = fat[0];
        fat[0] = fat[fat[0]];
        fat[allocate] = 0;
        // Follow links to change previous last block.
        while (fat[fileBlock] != 0) {
            fileBlock = fat[fileBlock];
        }
        fat[fileBlock] = allocate;
    }
    fssynch();
    putBlock(allocate, block);
    return allocate;
}

int Filesys::delBlock(std::string file, int blockNumber) {
    int nextBlock = getFirstBlock(file);
    // Can't delete block of empty file.
    if (nextBlock == 0) { // File doesn't exist or is empty.
        throw std::invalid_argument("Cannot delete block.");
        return 0;
    } else if (nextBlock == blockNumber) { // Block to del is first block.
        for (int i = 0; i < fileName.size(); i++) {
            if (fileName[i] == file) {
                firstBlock[i] = fat[blockNumber];
            }
        }
    } else { // Block to del is not first block.
        while (fat[nextBlock] != blockNumber && fat[nextBlock] != 0) {
            nextBlock = fat[nextBlock];
        }
        if (fat[nextBlock] != 0) {
            fat[nextBlock] = fat[blockNumber];
        } else {
            throw std::invalid_argument("Block not in file.");
            return 0;
        }
    }
    fat[blockNumber] = fat[0];
    fat[0] = blockNumber;
    fssynch();
}

int Filesys::readBlock(std::string file, int blockNumber, std::string& buffer) {
    if (checkBlock(file, blockNumber)) { // Block is in file.
        getBlock(blockNumber, buffer);
        return 1;
    } else { // Block not in file.
        throw std::invalid_argument("Cannot read: block permission error.");
        return 0;
    }
}

int Filesys::writeBlock(std::string file, int blockNumber, std::string buffer) {
    if (checkBlock(file, blockNumber)) { // Block is in file.
        putBlock(blockNumber, buffer);
        fssynch();
        return 1;
    } else { // Block not in file.
        throw std::invalid_argument("Cannot write: block permission error.");
        return 0;
    }
}

int Filesys::nextBlock(std::string file, int blockNumber) {
    if (checkBlock(file, blockNumber)) { // Block is in file.
        return fat[blockNumber];
    } else { // Block not in file.
        throw std::invalid_argument("nextBlock error: block not in file.");
        return 0;
    }
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

int Filesys::checkBlock(std::string file, int blockNumber) {
    int nextBlock = getFirstBlock(file);
    if (nextBlock == blockNumber) {
        return 1;
    } else {
        while (fat[nextBlock] != 0) {
            nextBlock = fat[nextBlock];
            if (nextBlock == blockNumber) {
                return 1;
            }
        }
        // When here blockNumber is not a part of the file.
        return 0;
    }
}

std::vector<std::string> Filesys::ls() {
    std::vector<std::string> flist;
    for (int i = 0; i < fileName.size(); i++) {
        if (fileName[i] != "xxxxx") {
            flist.push_back(fileName[i]);
        }
    }
    return flist;
}
