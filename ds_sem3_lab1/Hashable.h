#ifndef DS_SEM3_LAB1_HASHABLE_H
#define DS_SEM3_LAB1_HASHABLE_H

template<class Clazz>
class Hashable {
public:
    virtual int hashCode() const = 0;
    virtual bool equals(const Clazz& obj) const = 0;
};

#endif //DS_SEM3_LAB1_HASHABLE_H
