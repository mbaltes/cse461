// Name: Mark Baltes
// ID:   004899202
// File: test-filesys.cpp
//
// Driver for Table.

#include "Table.h"
#include <stdexcept>
#include <iostream>

int main() {
    try {
        Table t("disk7", 512, 128, "flat", "index");
        int x = t.buildTable("data.txt");
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
}