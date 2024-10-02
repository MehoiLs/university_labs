#ifndef DS_SEM3_LAB1_HASHABLE_H
#define DS_SEM3_LAB1_HASHABLE_H

template<class T>
class Hashable {
public:
    virtual int hashCode() const = 0;
    virtual bool equals(const T& obj) const = 0;
};

#endif //DS_SEM3_LAB1_HASHABLE_H
