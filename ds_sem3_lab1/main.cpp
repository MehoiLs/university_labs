#include <iostream>
#include "MyClass.h"
#include "HashTable.h"
#include "HashString.h"

using namespace std;

struct Record {
    HashString telephoneNumber;
    HashString fullName;
    unsigned int salary;
};

int main() {
    HashTable<MyClass, string> hashTable;

    auto key1 = MyClass(5);
    auto key2 = MyClass(96);
    auto key3 = MyClass(97);

    hashTable.put(key1, "lol");
    hashTable.put(key2, "kek");

    auto opt1 = hashTable.get(key1);
    auto opt2 = hashTable.get(key2);
    auto opt3 = hashTable.get(key3);

    cout << (opt1.has_value() ? opt1.value() : "nullopt") << endl;
    cout << (opt2.has_value() ? opt2.value() : "nullopt") << endl;
    cout << (opt3.has_value() ? opt3.value() : "nullopt") << endl;

    hashTable.remove(key2);
    opt2 = hashTable.get(key2);
    cout << (opt2.has_value() ? opt2.value() : "nullopt") << endl;

    return 0;
}
