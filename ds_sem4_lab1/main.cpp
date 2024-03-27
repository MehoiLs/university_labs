#include <iostream>
#include "MyClass.h"
#include "HashTable.h"
#include "HashString.h"

using namespace std;
#define uint unsigned int

struct Record {
    string fullName;
    string address;

    void input () {
        cin.ignore();
        cout << "Enter full name: ";
        getline(cin, fullName);
        cout << "Enter address: ";
        getline(cin, address);
    }
};

bool isLoggingEnabled = false;

int main() {
    HashTable<HashString, Record> hashTable;

    uint entries;
    cout << "Enter the number of entries: ";
    cin >> entries;

    for (int i = 0; i < entries; ++i) {
        HashString telephoneNumber;
        cout << "Input the telephone number: ";
        cin >> telephoneNumber;
        Record record;
        record.input();

        hashTable.put(telephoneNumber, record);
    }

    bool isSearching = true;
    while (isSearching) {
        HashString telephoneNumber;
        cout << "********************************************\n";
        cout << "Enter the telephone number to search.\n";
        cin >> telephoneNumber;

        auto record = hashTable.get(telephoneNumber);
        if (record.has_value()) {
            cout << "Full name: " << record.value().fullName << endl;
            cout << "Address: " << record.value().address << endl;
        } else {
            cerr << "Record not found." << endl;
        }

        cout << "Do you want to search for another record? (y/n):";
        char choice = 0;
        while (choice != 'y' && choice != 'n') {
            cin >> choice;
            if (choice == 'y') {
                continue;
            } else if (choice == 'n') {
                isSearching = false;
                break;
            } else {
                cerr << "Invalid choice." << endl;
            }
        }
    }

    return 0;
}


/* Задан набор записей след структуры:
 *      Тел номер
 *      ФИО
 *      адрес
 * По табельному номеру найти остальные сведения
 * */
