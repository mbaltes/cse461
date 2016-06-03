// Name: Mark Baltes
// ID:   004899202
// File: test-table.cpp
//
// Driver for Table.

#include "Table.h"
#include <stdexcept>
#include <iostream>

int main() {
    try {
        // Build table.
        Table t("disk7", 512, 128, "flat", "index");
        int x = t.buildTable("data.txt");

        // Ask user to enter searches by date.
        std::cout << "Enter 0 to exit." << '\n';
        int query = 1;
        while (query != 0) {
            std::cout << "What record has date: ";
            std::cin >> query;
            std::cout << t.search(query) << '\n';
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
}