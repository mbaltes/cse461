// Name: Mark Baltes
// ID:   004899202
// File: test-sdisk.cpp
//
// Driver for Sdisk class.

#include "Sdisk.cpp"

int main() {
    try {
        Sdisk disk1("test1", 16, 32);
        std::string block1, block2, block3, block4;
        for (int i=1; i<=32; i++) block1=block1+"1";
        for (int i=1; i<=32; i++) block2=block2+"2";
        disk1.putBlock(4,block1);
        disk1.getBlock(4,block3);
        std::cout << "Should be 32 1s : ";
        std::cout << block3 << std::endl;
        disk1.putBlock(8,block2);
        disk1.getBlock(8,block4);
        std::cout << "Should be 32 2s : ";
        std::cout << block4 << std::endl;;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
}