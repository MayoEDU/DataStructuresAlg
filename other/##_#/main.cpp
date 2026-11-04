// Hashmaps (called unordered_map in the C++ standard library)
//
// The one-sentence idea:
//     hash(key) -> bucket number -> look through that small bucket for the key.
//
// A map stores pairs: key -> value.
// Example: "alice" -> 42 means Alice has score 42.
//
// Run this file and read the output alongside the comments. Then change the
// examples and predict the output before running it again.

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// This small implementation is intentionally visible so the data structure is
// not magic. Real programs should normally use std::unordered_map.
class SimpleHashMap {
private:
    using Entry = std::pair<std::string, int>;
    std::vector<std::vector<Entry>> buckets;
    std::size_t itemCount = 0;

    std::size_t bucketFor(const std::string& key) const {
        return std::hash<std::string>{}(key) % buckets.size();
    }

public:
    explicit SimpleHashMap(std::size_t bucketCount = 8)
        : buckets(bucketCount == 0 ? 1 : bucketCount) {}

    // Insert a new key, or update the value when the key already exists.
    void set(const std::string& key, int value) {
        auto& bucket = buckets[bucketFor(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value; // update, not a duplicate key
                return;
            }
        }
        bucket.emplace_back(key, value); // collision: another entry in bucket
        ++itemCount;
    }

    // Returns a pointer so "not found" can be represented by nullptr.
    const int* get(const std::string& key) const {
        const auto& bucket = buckets[bucketFor(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }

    bool contains(const std::string& key) const {
        return get(key) != nullptr;
    }

    bool erase(const std::string& key) {
        auto& bucket = buckets[bucketFor(key)];
        for (auto entry = bucket.begin(); entry != bucket.end(); ++entry) {
            if (entry->first == key) {
                bucket.erase(entry);
                --itemCount;
                return true;
            }
        }
        return false;
    }

    std::size_t size() const { return itemCount; }
};

// A common assignment version uses integer keys. The important part of the
// API is the bool: update can report whether the key was actually present.
class IntHashMap {
private:
    using Entry = std::pair<int, int>;
    std::vector<std::vector<Entry>> buckets;

    std::size_t bucketFor(int key) const {
        return std::hash<int>{}(key) % buckets.size();
    }

public:
    explicit IntHashMap(std::size_t bucketCount = 8)
        : buckets(bucketCount == 0 ? 1 : bucketCount) {}

    void insert(int key, int value) {
        auto& bucket = buckets[bucketFor(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
    }

    // const int& means "I promise not to change value"; for an int, simply
    // writing int value is also good and is usually more readable.
    bool update(int key, const int& value) {
        auto& bucket = buckets[bucketFor(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return true;
            }
        }
        return false; // no key: nothing was updated
    }

    bool contains(int key) const {
        const auto& bucket = buckets[bucketFor(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    // A bool plus an output parameter is another common "find" pattern.
    bool get(int key, int& value) const {
        const auto& bucket = buckets[bucketFor(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                value = entry.second;
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::cout << "HASHMAP LESSON\n\n";

    // 1. Create and insert.
    std::unordered_map<std::string, int> scores;
    scores["Alice"] = 95;            // insert
    scores.insert({"Bob", 81});      // insert
    scores.emplace("Cara", 100);     // insert (constructs in place)

    // 2. Read/find. operator[] creates a missing key, so use find/contains
    // when you only want to check.
    std::cout << "Alice: " << scores.at("Alice") << '\n';
    if (scores.find("Bob") != scores.end()) {
        std::cout << "Bob exists\n";
    }
    if (scores.find("Nobody") == scores.end()) {
        std::cout << "Nobody was not found\n";
    }

    // 3. Update: assigning the same key replaces its value.
    scores["Alice"] = 98;
    std::cout << "Alice after update: " << scores.at("Alice") << '\n';

    // 4. Delete: erase(key) returns how many entries were removed.
    scores.erase("Bob");
    std::cout << "After deleting Bob, size = " << scores.size() << "\n\n";

    // 5. Iteration order is intentionally not sorted and is not guaranteed.
    std::cout << "Current entries (order may change):\n";
    for (const auto& [name, score] : scores) {
        std::cout << "  " << name << " -> " << score << '\n';
    }

    // 6. The implementation below makes collisions visible conceptually.
    SimpleHashMap visibleMap(4);
    visibleMap.set("red", 1);
    visibleMap.set("blue", 2);
    visibleMap.set("red", 99); // update: still only two items
    std::cout << "\nSimple map red: " << *visibleMap.get("red") << '\n';
    std::cout << "Simple map size after update: " << visibleMap.size() << '\n';
    visibleMap.erase("blue");
    std::cout << "Simple map contains blue: "
              << (visibleMap.contains("blue") ? "yes" : "no") << '\n';

    IntHashMap ids;
    ids.insert(7, 42);
    std::cout << "\nInteger-key API:\n";
    std::cout << "contains(7): " << (ids.contains(7) ? "true" : "false") << '\n';
    std::cout << "update(7, 99): " << (ids.update(7, 99) ? "true" : "false") << '\n';
    std::cout << "update(8, 10): " << (ids.update(8, 10) ? "true" : "false") << '\n';
    int value = 0;
    if (ids.get(7, value)) {
        std::cout << "get(7) found value " << value << '\n';
    }
    return 0;
}

/*
COMPLEXITY CHEAT SHEET

Let n be the number of key/value pairs and alpha = n / bucket_count be the
load factor (average entries per bucket).

Operation                  Average         Worst case
------------------------------------------------------
insert / update             O(1)            O(n)
find / contains              O(1)            O(n)
erase                       O(1)            O(n)
iteration over all entries  O(n)            O(n)
space                       O(n)            O(n)

Why can the worst case be O(n)? Different keys can have the same bucket index
(a collision). Then one bucket becomes a list, and searching that list is
linear. A good hash function and rehashing keep alpha small in normal use.

Important details:
- Keys must be hashable and comparable. std::string already is.
- An update method can return bool: true means the key existed and changed;
  false means the key was absent. Do not silently insert unless that is wanted.
- `bool contains(int key)` should only answer whether the key exists. It should
  not return the stored value.
- A `bool get(int key, int& value)` can return success and write the value into
  `value`; this avoids returning a fake value for a missing key.
- Updating an existing key does not add another pair.
- operator[] inserts a default value when the key is missing:
      scores["new name"] = 0;
  Use find, contains, or at when accidental insertion would be a bug.
- unordered_map is not sorted. Use std::map for sorted keys (usually O(log n)).
- Rehashing grows the bucket array and moves entries. An individual insert can
  therefore be expensive, but inserts are amortized O(1).
- Reserve capacity before many inserts to reduce rehashes:
      scores.reserve(1000);

Mental model: the key is not an array index. The hash function converts it to
an index, and the bucket resolves collisions by checking candidate keys.
*/