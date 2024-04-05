#ifndef DS_SEM3_LAB1_MYCLASS_H
#define DS_SEM3_LAB1_MYCLASS_H

#include "../Hashable.h"

class MyClass : public Hashable<MyClass> {

public:
    MyClass(int i) {
        var = i;
    }

    MyClass(const MyClass& other) : var(other.var) {}

    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            var = other.var;
        }
        return *this;
    }


    int var{};

    int hashCode() const override {
        return var * 31;
    }

    bool equals(const MyClass &obj) const override {
        return var == obj.var;
    }
};

#endif //DS_SEM3_LAB1_MYCLASS_H
