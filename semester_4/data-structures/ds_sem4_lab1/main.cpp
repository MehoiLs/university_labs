#include <iostream>
#include "HashSet.h"
#include "HashString.h"
#include "Record.h"

using namespace std;
#define uint unsigned int

bool isLoggingEnabled = false;

int main() {
    HashSet<Record> hashSet;

    uint entries;
    cout << "Enter the number of entries: ";
    cin >> entries;

    for (int i = 0; i < entries; ++i) {
        Record record;
        record.input();
        hashSet.put(record);
    }

    /**
     * Actually, a HashSet probably isn't the best choice for this task.
     * I believe a HashMap would be better, because we need to search by telephone number.
     * Also, a HashSet shouldn't have 'get' method, because it's not a map.
     *
     * So, to get a record, we need to create a 'dummy' record so that 'equals' method could be called.
     * Maybe there is a better solution for that, but I haven't come up with one yet.
    **/

    bool isSearching = true;
    Record possibleRecord;
    while (isSearching) {
        HashString telephoneNumber;
        cout << "********************************************\n";
        cout << "Enter the telephone number to search.\n";
        cin >> telephoneNumber;
        possibleRecord.setTelephoneNumber(telephoneNumber);

        auto record = hashSet.get(possibleRecord);
        if (record.has_value()) {
            record.value().print();
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
 * По тел номеру найти остальные сведения
 * */
