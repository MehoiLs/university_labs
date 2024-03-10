#ifndef DS_SEM3_LAB1_HASHTABLE_H
#define DS_SEM3_LAB1_HASHTABLE_H

#include <vector>
#include <list>
#include <optional>
#include "Hashable.h"

using std::list;
using std::vector;
using std::pair;

static const int INIT_SIZE = 32;

template<typename K, typename V>
class HashTable {
private:
    static_assert(std::is_base_of<Hashable<K>, K>::value, "Key type must implement Hashable interface.");

    size_t capacity;
    size_t size;
    vector<list<pair<K, V>>> table;

    void rehash() {
        capacity *= 2;
        vector<list<pair<K, V>>> oldTable = std::move(table);
        freeTableMemory();
        table.resize(capacity);

        for (auto &bucket : oldTable) {
            for (auto &entry : bucket) {
                put(entry.first, entry.second);
            }
        }
    }

    int hashCode(const K& key) {
        return key.hashCode() % capacity;
    }

    void freeTableMemory() {
        for (auto &bucket : table) {
            bucket.clear();
        }
        table.clear();
    }

public:
    HashTable() : capacity(INIT_SIZE), size(0) {
        table.resize(capacity);
    }
    ~HashTable() {
        freeTableMemory();
        size = capacity = 0;
    }

    void put(const K& key, const V& value) {
        if (size >= capacity) {
            rehash();
        }

        int index = hashCode(key);
        for (auto& pair : table[index])  {
            if (pair.first.equals(key)) {
                pair.second = value;
                return;
            }
        }

        table[index].push_back({key, value});
        size++;

        if (table[index].size() >= 10) {
            rehash();
        }
    }

    std::optional<V> get(const K& key) {
        int index = hashCode(key);
        for (auto& pair : table[index]) {
            if (pair.first.equals(key)) {
                return pair.second;
            }
        }
        return std::nullopt;
    }

    bool remove(const K& key) {
        int index = hashCode(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first.equals(key)) {
                bucket.erase(it);
                size--;
                return true;
            }
        }

        return false;
    }
};


#endif //DS_SEM3_LAB1_HASHTABLE_H
