/*
 * Project Three - Corner Grocer
 * Name: Pendeza Alimasi
 * Course: CS 210 Programming Languages
 * Date: 04/19/2026
 *
 * Description:
 * This program reads grocery item data from an input file and counts how many times
 * each item is purchased. It allows the user to search for a specific item, display
 * all item frequencies, and view a histogram representation of the data. The program
 * also creates a backup file (frequency.dat) that stores all item frequencies.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// This class stores grocery items and their purchase frequencies
class PurchaseCounter {
private:
    map<string, int> itemCounts;

public:
    // Reads the input file and counts how many times each item appears
    void loadFile(string filename) {
        ifstream file(filename);
        string item;

        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        while (file >> item) {
            itemCounts[item]++;
        }

        file.close();
    }

    // Returns the frequency of one specific item
    int getItemCount(string itemName) {
        if (itemCounts.find(itemName) != itemCounts.end()) {
            return itemCounts[itemName];
        }
        return 0;
    }

    // Prints all items with their numeric frequencies
    void printAllFrequencies() {
        cout << "\nAll Item Frequencies" << endl;
        cout << "--------------------" << endl;

        for (auto pair : itemCounts) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Prints all items in histogram form using asterisks
    void printHistogram() {
        cout << "\nItem Purchase Histogram" << endl;
        cout << "-----------------------" << endl;

        for (auto pair : itemCounts) {
            cout << pair.first << " ";

            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }

    // Creates frequency.dat file with all item counts
    void createBackupFile(string filename) {
        ofstream outFile(filename);

        if (!outFile.is_open()) {
            cout << "Error creating backup file." << endl;
            return;
        }

        for (auto pair : itemCounts) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }
};

// Displays the menu
void showMenu() {
    cout << "\nCorner Grocer Menu" << endl;
    cout << "------------------" << endl;
    cout << "1. Search for one item" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    PurchaseCounter tracker;
    int choice;
    string userItem;

    tracker.loadFile("CS210_Project_Three_Input_File.txt");
    tracker.createBackupFile("frequency.dat");
    cout << "Backup file created!" << endl;
    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Enter item name: ";
            cin >> userItem;
            cout << userItem << " was purchased "
                << tracker.getItemCount(userItem)
                << " time(s)." << endl;
        }
        else if (choice == 2) {
            tracker.printAllFrequencies();
        }
        else if (choice == 3) {
            tracker.printHistogram();
        }
        else if (choice == 4) {
            cout << "Exiting program." << endl;
        }
        else {
            cout << "Invalid option. Please choose 1, 2, 3, or 4." << endl;
        }

    } while (choice != 4);

    return 0;
}