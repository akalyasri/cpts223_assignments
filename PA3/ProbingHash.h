#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    //vector<pair<EntryState,pair<K,V>>> pTable;

    vector<pair<K, V>> table; // table for key-value pairs
    vector<EntryState> states; // state of each table entry (EMPTY, VALID, DELETED)

    // Table should be a vector of std::pairs for lazy deletion
    int currentSize;

public:
    ProbingHash(int n = 11) {   

        //tableSize = n;
       // pTable.resize(findNextPrime(n),pair<EntryState,pair<K,V>>());
       
        int size = findNextPrime(n);
        table.resize(size);
        states.resize(size, EMPTY);

    }

    ~ProbingHash() {
        // free table
        this->clear();
    }

    int size() {
        
        return currentSize;
    }

    V operator[](const K& key) {

        int index = findPosition(key);
        if (states[index] == VALID) {
            return table[index].second;
        }
        throw std::out_of_range("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) {

        if (static_cast<float>(currentSize + 1) / table.size() > 0.75) {
            rehash();
        }

        int index = findPosition(pair.first);
        if (states[index] == EMPTY || states[index] == DELETED) {
            table[index] = pair;
            states[index] = VALID;
            currentSize++;
            return true;
        }
        return false; // Key already exists
        
    }

    void erase(const K& key) {

        int index = findPosition(key);
        if (states[index] == VALID) {
            states[index] = DELETED;
            currentSize--;
        }
    }

    void clear() {
        table.clear();
        states.clear();
        currentSize = 0;
    }

    int bucket_count() {
        return table.size();
    }

    float load_factor() {
        return static_cast<float>(currentSize) / table.size();
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return std::hash<K>{}(key) % table.size();   
    }
/*
    void rehash() { // changed vector - doesnt work
        int newSize = findNextPrime(2 * table.size());
        vector<pair<K, V>> newTable(newSize, { K(), V() });

        for (const auto& entry : table) {
            if (states[findPosition(entry.first)] != VALID) {
                int index = findPosition(entry.first);
                newTable[index] = entry;
            }
        }

        table = std::move(newTable);
    }
*/


    void rehash() {
        int newSize = findNextPrime(2 * table.size());

        if (newSize <= table.size()) {
            // avoid resizing to a smaller size
            return;
        }

        vector<pair<K, V>> newTable(newSize, { K(), V() });
        vector<EntryState> newStates(newSize, EMPTY);

        for (int i = 0; i < table.size(); i++) {

            if (states[i] == VALID) {

                // reinsert the element with linear probing
                int index = findPosition(table[i].first);
                newTable[index] = table[i];
                newStates[index] = VALID;
            }
        }

        table = std::move(newTable);
        states = std::move(newStates);
    }

    int findPosition(const K& key) {
        int index = hash(key);
        int offset = 1;

        while (states[index] == VALID && table[index].first != key) {

            index += offset;
            offset++;
            
            if (index >= table.size()) {
                index -= table.size();
            }
        }

        return index;
    }
    
};

#endif //__PROBING_HASH_H
