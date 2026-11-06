#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SimpleMap {
private:
    vector<pair<string, int>> items;

    int searchIndex(const string& key) const {
        for (int i = 0; i < static_cast<int>(items.size()); ++i) {
            if (items[i].first == key) {
                return i;
            }
        }
        return -1;
    }

public:
    void Insert(string key, int value) {
        items.push_back({key, value});
    }

    // Updates the value if the key is already in the map.
    bool Updates(string key, int newValue) {
        int index = searchIndex(key);
        if (index == -1) {
            return false;
        }

        items[index].second = newValue;
        return true;
    }

    // Contains only checks if the key is there.
    bool Contains(string key) const {
        return searchIndex(key) != -1;
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
