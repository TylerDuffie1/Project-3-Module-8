#include "ItemTracker.h"
#include <iostream>
#include <limits>
#include <string>

/**
 * Corner Grocer - Item Tracking Program
 * Menu:
 * 1) Query frequency of a specific item
 * 2) Print all item frequencies
 * 3) Print histogram
 * 4) Exit
 *
 * Notes:
 *  - On startup we load the input file and immediately back up to frequency.dat
 *  - Robust input validation for menu choice and query strings.
 */
static void PrintMenu() {
    std::cout << "\n===== Corner Grocer - Item Tracker =====\n";
    std::cout << "1. Look up frequency of an item\n";
    std::cout << "2. Print all items with counts\n";
    std::cout << "3. Print histogram\n";
    std::cout << "4. Exit\n";
    std::cout << "Select an option (1-4): ";
}

static int ReadIntChoice() {
    int choice;
    while (true) {
        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 4) return choice;
            std::cout << "Please enter a number 1-4: ";
        } else {
            std::cout << "Invalid input. Enter a number 1-4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    const std::string inputPath = "data/CS210_Project_Three_Input_File.txt";
    ItemTracker tracker(inputPath);

    if (!tracker.Load()) {
        std::cout << "Fatal: could not load input file at '" << inputPath << "'.\n";
        std::cout << "Make sure the file exists. Exiting.\n";
        return 1;
    }

    if (tracker.WriteFrequencyBackup("frequency.dat")) {
        std::cout << "Backup written to frequency.dat\n";
    } else {
        std::cout << "Warning: could not write frequency.dat\n";
    }

    while (true) {
        PrintMenu();
        int choice = ReadIntChoice();

        if (choice == 1) {
            std::cout << "Enter item to search: ";
            std::string item;
            std::cin >> item;
            int freq = tracker.FrequencyOf(item);
            std::cout << item << " -> " << freq << std::endl;
        } else if (choice == 2) {
            tracker.PrintAllFrequencies();
        } else if (choice == 3) {
            tracker.PrintHistogram('*');
        } else if (choice == 4) {
            std::cout << "Goodbye!\n";
            break;
        }
    }
    return 0;
}
