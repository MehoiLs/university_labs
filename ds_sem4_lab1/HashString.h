#ifndef DS_SEM3_LAB1_HASHSTRING_H
#define DS_SEM3_LAB1_HASHSTRING_H

#include <string>
#include <utility>
#include "Hashable.h"

class HashString : public Hashable<HashString> {
private:
    std::string str;
public:
    HashString() = default;
    explicit HashString(std::string str): str(std::move(str)) {}
    ~HashString() { str.erase(); }
    HashString(const HashString& other) : str(other.str) {}

    [[nodiscard]] int hashCode() const override {
        int hash = 0;
        for (char ch : str) {
            hash = (hash * 31) + ch;
        }
        return hash;
    }

    [[nodiscard]] bool equals(const HashString &obj) const override {
        return str == obj.str;
    }

    std::string get() {
        return str;
    }

    void set(const std::string& str) {
        this->str = str;
    }

    friend std::istream& operator>>(std::istream& is, HashString& hashString) {
        is >> hashString.str;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, HashString& hashString) {
        os << hashString.str;
        return os;
    }
};

#endif //DS_SEM3_LAB1_HASHSTRING_H
