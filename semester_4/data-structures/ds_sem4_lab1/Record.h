#ifndef DS_SEM4_LAB1_RECORD_H
#define DS_SEM4_LAB1_RECORD_H

#include <iostream>
#include <string>
#include "Hashable.h"
#include "HashString.h"

using std::string;
using std::cout;
using std::cin;

class Record : public Hashable<Record> {
private:
    HashString telephoneNumber;
    HashString fullName;
    HashString address;

public:
    [[nodiscard]] int hashCode() const override {
        // return 31 * (telephoneNumber.hashCode() + fullName.hashCode() + address.hashCode());
        return telephoneNumber.hashCode();
    }

    [[nodiscard]] bool equals(const Record &obj) const override {
        return telephoneNumber.equals(obj.telephoneNumber); // hardcode :(
    }

    void print() {
        cout << "Telephone number: " << telephoneNumber.get() << std::endl;
        cout << "Full name: " << fullName.get() << std::endl;
        cout << "Address: " << address.get() << std::endl;
    }

    void input() {
        string temp;

        cout << "Enter the telephone number: ";
        cin >> temp;
        telephoneNumber.set(temp);

        cin.ignore();
        cout << "Enter full name: ";
        getline(cin, temp);
        fullName.set(temp);

        cout << "Enter address: ";
        getline(cin, temp);
        address.set(temp);
    }

    [[nodiscard]] const HashString &getTelephoneNumber() const {
        return telephoneNumber;
    }

    void setTelephoneNumber(const HashString &telephoneNum) {
        this->telephoneNumber = telephoneNum;
    }

    [[nodiscard]] const HashString &getFullName() const {
        return fullName;
    }

    void setFullName(const HashString &fullName) {
        this->fullName = fullName;
    }

    [[nodiscard]] const HashString &getAddress() const {
        return address;
    }

    void setAddress(const HashString &address) {
        this->address = address;
    }
};

#endif //DS_SEM4_LAB1_RECORD_H
