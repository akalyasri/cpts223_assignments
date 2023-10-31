/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {

private:
    vector<list<pair<K, V>>> table;
    int currentSize;

public:
    ChainingHash(int n = 11) :currentSize(0) {
        
        int size = findNextPrime(n);
        table.resize(size);
    }

    ~ChainingHash() {
        this->clear();
    }

    int size() {
        return currentSize;
    }

    V operator[](const K& key) {

        int index = hash(key);

        for (const auto& entry : table[index]) {

            if (entry.first == key) {

                return entry.second;
            }
        }
        throw std::out_of_range("Key not found");
    
    }

    bool insert(const std::pair<K, V>& pair) {

        int index = hash(pair.first);

        for (auto& entry : table[index]) {

            if (entry.first == pair.first) {

                entry.second = pair.second;  // update the value if the key already exists
                return false;
            }
        }

        table[index].push_back(pair);
        currentSize++;

        // rehash if the load factor exceeds 0.75
        if (static_cast<float>(currentSize) / table.size() > 0.75) {
            rehash();
        }

        return true;
    }

    void erase(const K& key) {

        int index = hash(key);

        auto& entries = table[index];

        for (auto it = entries.begin(); it != entries.end(); ++it) {

            if (it->first == key) {

                entries.erase(it);
                currentSize--;
                return;
            }
        }
    }

    void clear() {

         table.clear();
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
        //returns index of bucket

        return std::hash<K>{}(key) % table.size();
             
    }

    void rehash() {

        int newSize = findNextPrime(2 * table.size());
        vector<list<pair<K, V>>> newTable(newSize);

        for (const auto& bucket : table) {

            for (const auto& entry : bucket) {

                int index = std::hash<K>{}(entry.first) % newSize;
                newTable[index].push_back(entry);
            }
        }

        table = std::move(newTable);
    }


};

#endif //__CHAINING_HASH_H
