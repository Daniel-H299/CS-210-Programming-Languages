
#include <iostream>
#include <fstream>
#include <map>
#include <string>

class GroceryTracker {
private:
    std::map<std::string, int> itemFrequency;

public:
    void loadItemsFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string item;
        while (file >> item) {
            itemFrequency[item]++;
        }
        file.close();
    }

    int getFrequency(const std::string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0; // Item not found
    }

    void printItemList() const {
        for (const auto& entry : itemFrequency) {
            std::cout << entry.first << " " << entry.second << std::endl;
        }
    }

    void printHistogram() const {
        for (const auto& entry : itemFrequency) {
            std::cout << entry.first << " ";
            for (int i = 0; i < entry.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    void saveFrequencyToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        for (const auto& entry : itemFrequency) {
            outFile << entry.first << " " << entry.second << std::endl;
        }
        outFile.close();
    }
};

int main() {
    GroceryTracker tracker;
    tracker.loadItemsFromFile("CS210_Project_Three_Input_File.txt");

    int choice = 0;
    std::string inputItem;
    while (choice != 4) {
        std::cout << "1. Look for an item\n2. Print frequency of all items\n3. Print histogram\n4. Exit\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter item to look for: ";
            std::cin >> inputItem;
            std::cout << inputItem << " was purchased " << tracker.getFrequency(inputItem) << " times." << std::endl;
            break;
        case 2:
            tracker.printItemList();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            tracker.saveFrequencyToFile("frequency.dat");
            std::cout << "Data saved. Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid option. Try again." << std::endl;
        }
    }

    return 0;
}
