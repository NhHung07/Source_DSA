// Hash Table Implementation Template
// Instructions: Implement the missing function definitions for each class.
// Each function has comments indicating what it should do.

#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <vector>

//-------------------- HASH FUNCTION HELPERS --------------------
// Helper function to hash strings using Horner's rule
int hashString(const std::string& str, int tableSize) {
    // TODO: Implement string hashing function using Horner's rule
    // Use a prime number as the base (e.g., 31)
    // Return hash value modulo tableSize
    unsigned int hashVal = 0;
    const int base = 31; // A common prime number used for hashing strings
    for (char ch : str) {
        hashVal = (hashVal * base) + ch;
    }
    return hashVal % tableSize;
}

// Helper function to hash integers
int hashInt(int key, int tableSize) {
    // TODO: Implement simple integer hash function
    // Consider using the division method: h(k) = k mod tableSize
    int hashVal = key % tableSize;
    if (hashVal < 0) {
        hashVal += tableSize; // Ensure the hash is non-negative
    }
    return hashVal;
}

//-------------------- HASHER STRUCT FOR TYPE-BASED HASHING --------------------
// This allows the hash table to select the correct hash function based on key type.
template <typename T>
struct Hasher;

// Specialization for std::string keys
template <>
struct Hasher<std::string> {
    int operator()(const std::string& key, int tableSize) const {
        return hashString(key, tableSize);
    }
};

// Specialization for int keys
template <>
struct Hasher<int> {
    int operator()(int key, int tableSize) const {
        return hashInt(key, tableSize);
    }
};


//-------------------- SEPARATE CHAINING HASH TABLE --------------------
// Generic hash table using separate chaining for collision resolution
template <typename K, typename V>
class SeparateChainingHashTable {
private:
    // Each bucket contains a list of key-value pairs
    struct KeyValuePair {
        K key;
        V value;
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    };

    std::list<KeyValuePair>* buckets; // Array of linked lists
    int tableSize;                    // Number of buckets
    int itemCount;                    // Total number of items in the hash table

    // Hash function - will be defined differently for different key types
    int hash(const K& key) const {
        // TODO: Implement hash function selector based on key type
        // Use the Hasher struct to call the appropriate hash function
        return Hasher<K>()(key, tableSize);
    }

public:
    // Constructor: Initialize hash table with given size
    SeparateChainingHashTable(int size = 101) {
        // TODO: Implement constructor
        tableSize = size > 0 ? size : 101;
        itemCount = 0;
        buckets = new std::list<KeyValuePair>[tableSize];
    }

    // Destructor: Free dynamically allocated memory
    ~SeparateChainingHashTable() {
        // TODO: Implement destructor
        delete[] buckets;
    }

    // Insert a key-value pair into the hash table
    // If key already exists, update its value
    void insert(const K& key, const V& value) {
        // TODO: Implement insert function
        int index = hash(key);
        // Search for the key in the chain
        for (auto& pair : buckets[index]) {
            if (pair.key == key) {
                // Key found, update value and return
                pair.value = value;
                return;
            }
        }
        // Key not found, insert new pair at the end of the list
        buckets[index].emplace_back(key, value);
        itemCount++;
    }

    // Remove a key-value pair from the hash table
    // Throw exception if key not found
    void remove(const K& key) {
        // TODO: Implement remove function
        int index = hash(key);
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->key == key) {
                buckets[index].erase(it);
                itemCount--;
                return;
            }
        }
        throw std::runtime_error("Key not found for removal");
    }

    // Search for a value associated with the given key
    // Throw exception if key not found
    V search(const K& key) const {
        // TODO: Implement search function
        int index = hash(key);
        for (const auto& pair : buckets[index]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        throw std::runtime_error("Key not found in search");
    }

    // Check if the hash table contains the given key
    bool contains(const K& key) const {
        // TODO: Implement contains function
        int index = hash(key);
        for (const auto& pair : buckets[index]) {
            if (pair.key == key) {
                return true;
            }
        }
        return false;
    }

    // Return the current load factor
    float loadFactor() const {
        // TODO: Implement load factor calculation
        return tableSize > 0 ? static_cast<float>(itemCount) / tableSize : 0.0f;
    }

    // Return number of items in the hash table
    int size() const {
        // TODO: Implement size function
        return itemCount;
    }

    // Display the hash table (for debugging)
    void display() const {
        // TODO: Implement display function
        for (int i = 0; i < tableSize; ++i) {
            std::cout << "Bucket " << i << ": ";
            if (buckets[i].empty()) {
                std::cout << "EMPTY";
            } else {
                for (const auto& pair : buckets[i]) {
                    std::cout << "[" << pair.key << ": " << pair.value << "] -> ";
                }
                std::cout << "NULL";
            }
            std::cout << std::endl;
        }
    }
};

//-------------------- OPEN ADDRESSING HASH TABLE --------------------
// Generic hash table using open addressing for collision resolution
template <typename K, typename V>
class OpenAddressingHashTable {
private:
    enum EntryStatus { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        K key;
        V value;
        EntryStatus status;
        
        Entry() : status(EMPTY) {}
    };

    Entry* table;      // Array of entries
    int tableSize;     // Size of the table
    int itemCount;     // Number of items in the table

    // Hash function
    int hash(const K& key) const {
        // TODO: Implement hash function selector based on key type
        return Hasher<K>()(key, tableSize);
    }

    // Probe function for collision resolution (linear probing)
    int probe(int currentHash, int i) const {
        // TODO: Implement linear probing
        return (currentHash + i) % tableSize;
    }

public:
    // Constructor: Initialize hash table with given size
    OpenAddressingHashTable(int size = 101) {
        // TODO: Implement constructor
        tableSize = size > 0 ? size : 101;
        itemCount = 0;
        table = new Entry[tableSize];
    }

    // Destructor: Free dynamically allocated memory
    ~OpenAddressingHashTable() {
        // TODO: Implement destructor
        delete[] table;
    }

    // Insert a key-value pair into the hash table
    // If key already exists, update its value
    // If table is full, throw an exception
    void insert(const K& key, const V& value) {
        // TODO: Implement insert function
        if (itemCount >= tableSize) {
            throw std::runtime_error("Hash table is full");
        }

        int initialHash = hash(key);
        int firstDeleted = -1;

        for (int i = 0; i < tableSize; ++i) {
            int index = probe(initialHash, i);
            
            if (table[index].status == OCCUPIED && table[index].key == key) {
                // Key found, update value
                table[index].value = value;
                return;
            }
            if (table[index].status == EMPTY) {
                // Found an empty slot. Insert here or at the first deleted spot.
                int insertPos = (firstDeleted != -1) ? firstDeleted : index;
                table[insertPos].key = key;
                table[insertPos].value = value;
                table[insertPos].status = OCCUPIED;
                itemCount++;
                return;
            }
            if (table[index].status == DELETED && firstDeleted == -1) {
                // Keep track of the first deleted spot we find
                firstDeleted = index;
            }
        }
        
        // If we exit the loop, we can insert at the first deleted spot found
        if(firstDeleted != -1) {
            table[firstDeleted].key = key;
            table[firstDeleted].value = value;
            table[firstDeleted].status = OCCUPIED;
            itemCount++;
        } else {
             // This case should theoretically not be reached due to the initial fullness check
            throw std::runtime_error("Hash table is full, could not find position to insert");
        }
    }

    // Remove a key-value pair from the hash table
    // Throw exception if key not found
    void remove(const K& key) {
        // TODO: Implement remove function
        int initialHash = hash(key);
        for (int i = 0; i < tableSize; ++i) {
            int index = probe(initialHash, i);
            
            if (table[index].status == EMPTY) {
                // Key is not in the table
                throw std::runtime_error("Key not found for removal");
            }
            if (table[index].status == OCCUPIED && table[index].key == key) {
                // Found the key, mark it as deleted
                table[index].status = DELETED;
                itemCount--;
                return;
            }
        }
        // If we finish the loop, the key was not found
        throw std::runtime_error("Key not found for removal");
    }

    // Search for a value associated with the given key
    // Throw exception if key not found
    V search(const K& key) const {
        // TODO: Implement search function
        int initialHash = hash(key);
        for (int i = 0; i < tableSize; ++i) {
            int index = probe(initialHash, i);

            if (table[index].status == EMPTY) {
                // If we hit an empty spot, the key is not in the table
                throw std::runtime_error("Key not found in search");
            }
            if (table[index].status == OCCUPIED && table[index].key == key) {
                // Found the key
                return table[index].value;
            }
        }
        // If we complete the loop, the key was not found
        throw std::runtime_error("Key not found in search");
    }

    // Check if the hash table contains the given key
    bool contains(const K& key) const {
        // TODO: Implement contains function
        int initialHash = hash(key);
        for (int i = 0; i < tableSize; ++i) {
            int index = probe(initialHash, i);

            if (table[index].status == EMPTY) {
                return false;
            }
            if (table[index].status == OCCUPIED && table[index].key == key) {
                return true;
            }
        }
        return false;
    }

    // Return the current load factor
    float loadFactor() const {
        // TODO: Implement load factor calculation
        return tableSize > 0 ? static_cast<float>(itemCount) / tableSize : 0.0f;
    }

    // Return number of items in the hash table
    int size() const {
        // TODO: Implement size function
        return itemCount;
    }

    // Display the hash table (for debugging)
    void display() const {
        // TODO: Implement display function
        for (int i = 0; i < tableSize; ++i) {
            std::cout << "Index " << i << ": ";
            if (table[i].status == OCCUPIED) {
                std::cout << "[" << table[i].key << ": " << table[i].value << "] (OCCUPIED)";
            } else if (table[i].status == DELETED) {
                std::cout << "(DELETED)";
            } else {
                std::cout << "(EMPTY)";
            }
            std::cout << std::endl;
        }
    }
};

//-------------------- TESTING FUNCTION --------------------
void testHashTables() {
    // Test separate chaining hash table with string keys
    std::cout << "Testing Separate Chaining Hash Table with string keys:\n";
    SeparateChainingHashTable<std::string, int> scHashTable(10);
    
    // Insert some key-value pairs
    scHashTable.insert("apple", 5);
    scHashTable.insert("banana", 8);
    scHashTable.insert("cherry", 12);
    scHashTable.insert("date", 15);
    scHashTable.insert("elderberry", 20);
    scHashTable.insert("fig", 25);
    
    // Display the table
    std::cout << "After insertions:\n";
    scHashTable.display();
    
    // Search for some keys
    try {
        std::cout << "Value for 'apple': " << scHashTable.search("apple") << std::endl;
        std::cout << "Value for 'banana': " << scHashTable.search("banana") << std::endl;
        std::cout << "Value for 'grape': " << scHashTable.search("grape") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    // Remove a key
    std::cout << "\nRemoving 'banana'...\n";
    scHashTable.remove("banana");
    
    // Display the table again
    std::cout << "After removal:\n";
    scHashTable.display();
    
    // Test contains method
    std::cout << "Contains 'apple': " << (scHashTable.contains("apple") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'banana': " << (scHashTable.contains("banana") ? "Yes" : "No") << std::endl;
    
    // Test load factor
    std::cout << "Load factor: " << scHashTable.loadFactor() << std::endl;
    std::cout << "Size: " << scHashTable.size() << std::endl;
    
    std::cout << "\n--------------------------------------------------\n";

    // Test open addressing hash table with integer keys
    std::cout << "\nTesting Open Addressing Hash Table with integer keys:\n";
    OpenAddressingHashTable<int, std::string> oaHashTable(10);
    
    // Insert some key-value pairs
    oaHashTable.insert(5, "five");
    oaHashTable.insert(15, "fifteen"); // Collision with 5
    oaHashTable.insert(25, "twenty-five"); // Collision with 5, 15
    oaHashTable.insert(35, "thirty-five"); // Collision
    oaHashTable.insert(45, "forty-five"); // Collision
    
    // Display the table
    std::cout << "After insertions:\n";
    oaHashTable.display();
    
    // Search for some keys
    try {
        std::cout << "Value for 5: " << oaHashTable.search(5) << std::endl;
        std::cout << "Value for 15: " << oaHashTable.search(15) << std::endl;
        std::cout << "Value for 100: " << oaHashTable.search(100) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    // Remove a key
    std::cout << "\nRemoving 15...\n";
    oaHashTable.remove(15);
    
    // Display the table again
    std::cout << "After removal:\n";
    oaHashTable.display();

    // Insert another element to see if it uses the DELETED spot
    std::cout << "\nInserting 7 ('seven')...\n";
    oaHashTable.insert(7, "seven");
    std::cout << "After inserting 7:\n";
    oaHashTable.display();
    
    // Test contains method
    std::cout << "Contains 5: " << (oaHashTable.contains(5) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 15: " << (oaHashTable.contains(15) ? "Yes" : "No") << std::endl;
    
    // Test load factor
    std::cout << "Load factor: " << oaHashTable.loadFactor() << std::endl;
    std::cout << "Size: " << oaHashTable.size() << std::endl;
}

int main() {
    testHashTables();
    return 0;
}
