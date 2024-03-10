#ifndef DS_SEM3_LAB1_HASHSTRING_H
#define DS_SEM3_LAB1_HASHSTRING_H

#include <string>
#include <utility>
#include "Hashable.h"

class HashString : public Hashable<HashString> {
private:
    std::string str;
public:
    explicit HashString(std::string str): str(std::move(str)) {}
    ~HashString() { str.erase(); }
    HashString(const HashString& other) : str(other.str) {}

    int hashCode() const override {
        int hash = 0;
        for (char ch : str) {
            hash = (hash * 31) + ch;
        }
        return hash;
    }

    bool equals(const HashString &obj) const override {
        return str == obj.str;
    }

    std::string get() {
        return str;
    }

    void set(const std::string& str) {
        this->str = str;
    }
};

#endif //DS_SEM3_LAB1_HASHSTRING_H
