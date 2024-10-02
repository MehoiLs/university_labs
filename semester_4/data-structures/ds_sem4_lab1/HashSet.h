#ifndef DS_SEM3_LAB1_HASHTABLE_H
#define DS_SEM3_LAB1_HASHTABLE_H

#include <vector>
#include <list>
#include <optional>
#include "Hashable.h"
#include "Logger.h"

using std::list;
using std::vector;
using std::pair;

static constexpr int INIT_SIZE = 32;

template<typename V>
class HashSet {
private:
    static_assert(std::is_base_of_v<Hashable<V>, V>, "Key type must implement Hashable interface.");
    const Logger<HashSet> logger;

    size_t capacity;
    size_t size;
    vector<list<V>> table;

    void rehash() {
        try {
            logger.log("Rehashing table..." + std::to_string(capacity) + " -> " + std::to_string(capacity * 2) + "...");
            capacity *= 2;
            vector<list<V>> oldTable = std::move(table);
            freeTableMemory();
            table.resize(capacity);

            for (auto &bucket: oldTable) {
                for (auto &entry: bucket) {
                    put(entry);
                }
            }
            logger.log("Rehashing completed.");
        } catch (std::exception& e) {
            logger.error("Failed to rehash table. " + std::string(e.what()));
        }
    }

    int hashCode(const V& value) {
        return value.hashCode() % capacity;
    }

    void freeTableMemory() {
        for (auto &bucket : table) {
            bucket.clear();
        }
        table.clear();
    }

public:
    HashSet() : capacity(INIT_SIZE), size(0) {
        table.resize(capacity);
    }
    ~HashSet() {
        freeTableMemory();
        size = capacity = 0;
    }

    void put(const V& value) {
        if (size >= capacity) {
            rehash();
        }

        int index = hashCode(value);
        for (auto& listEntry : table[index]) {
            if (listEntry.equals(value)) {
                listEntry = value;
                return;
            }
        }

        table[index].push_back({value});
        size++;

        if (table[index].size() >= 10) {
            rehash();
        }
    }

    std::optional<V> get(const V& value) {
        int index = hashCode(value);
        for (auto& listEntry : table[index]) {
            if (listEntry.equals(value)) {
                return listEntry;
            }
        }
        return std::nullopt;
    }

    bool remove(const V& value) {
        int index = hashCode(value);
        auto& tableList = table[index];
        for (auto it = tableList.begin(); it != tableList.end(); ++it) {
            if (it->equals(value)) {
                tableList.erase(it);
                size--;
                return true;
            }
        }

        return false;
    }
};


#endif //DS_SEM3_LAB1_HASHTABLE_H
