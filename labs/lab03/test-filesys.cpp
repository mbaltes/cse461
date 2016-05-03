// Name: Mark Baltes
// ID:   004899202
// File: test-filesys.cpp
//
// Driver for Filesys.

#include "Filesys.h"
#include <stdexcept>
#include <iostream>

// int main() {
//     try {
//         //Sdisk fsdisk("test3", 16, 32);
//         Filesys fs("test3", 16, 32);
//         fs.test();
//     } catch (const std::invalid_argument& e) {
//         std::cout << e.what() << '\n';
//         return -1;
//     }
// }

// int main() {
//     try {
//         Filesys fs("disk2", 16, 32);
//         fs.newFile("test");
//         fs.newFile("test1");
//         std::string file1 = "Hello test. This is going to be a long long file. I hope all goes well with you.";
//         //fs.newFile("hi");
//         //fs.test();
//         //fs.rmFile("test;lsfj");
//         std::vector<std::string> blocks = fs.block(file1, 32); 
//         //fs.addBlock("test", file1);
//         for (int i = 0; i < blocks.size(); i++) {

//         }
//         //fs.addBlock("test1", "Boom push this to test1.");
//         //fs.delBlock("test1", 7);
//     } catch (const std::invalid_argument& e) {
//         std::cout << e.what() << '\n';
//         return -1;
//     }
// }

int main() {
    try {
        // You can use this to test your Filesys class 

        //Sdisk disk1("disk1",256,128);
        Filesys fsys("disk1",256,128);
        fsys.newFile("file1");
        fsys.newFile("file2");

        std::string bfile1;
        std::string bfile2;

        for (int i = 1; i <= 1024; i++) {
            bfile1+="1";
        }

        std::vector<std::string> blocks = fsys.block(bfile1,128); 

        int blocknumber = 0;

        for (int i = 0; i < blocks.size(); i++) {
            blocknumber = fsys.addBlock("file1",blocks[i]);
        }

        fsys.delBlock("file1",fsys.getFirstBlock("file1"));

        for (int i = 1; i <= 2048; i++) {
            bfile2 += "2";
        }

        blocks = fsys.block(bfile2,128); 

        for (int i = 0; i < blocks.size(); i++) {
            blocknumber = fsys.addBlock("file2", blocks[i]);
        }

        fsys.delBlock("file2",blocknumber);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
}