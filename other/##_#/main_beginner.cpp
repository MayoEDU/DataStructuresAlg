#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SimpleMap {
private:
    vector<pair<string, int>> items;

public:
    void Insert(string key, int value) {
        items.push_back({key, value});
    }

    // Updates the value if the key is already in the map.
    bool Updates(string key, int newValue) {
        for (auto& item : items) {
            if (item.first == key) {
                item.second = newValue;
                return true;
            }
        }
        return false;
    }

    // Contains only checks if the key is there.
    bool Contains(string key) {
        for (auto item : items) {
            if (item.first == key) {
                return true;
            }
        }
        return false;
    }

    void Print() {
        for (auto item : items) {
            cout << item.first << ": " << item.second << endl;
        }
    }
};

int main() {
    SimpleMap scores;

    scores.Insert("Sam", 80);
    scores.Insert("Alex", 90);

    cout << "Before update:" << endl;
    scores.Print();

    // Updates changes the value for an existing key.
    if (scores.Updates("Sam", 95)) {
        cout << "Sam was updated." << endl;
    }

    // Contains returns true or false. It does not change the map.
    if (scores.Contains("Alex")) {
        cout << "Alex is in the map." << endl;
    }

    if (!scores.Contains("Taylor")) {
        cout << "Taylor is not in the map." << endl;
    }

    cout << "\nAfter update:" << endl;
    scores.Print();

    return 0;
}
