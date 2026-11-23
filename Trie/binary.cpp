#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
    TrieNode* children[2];
    bool isEndOfNumber;

    TrieNode() {
        children[0] = nullptr;
        children[1] = nullptr;

        isEndOfNumber = false;
    }
};

class BinaryTrie {
private:
    TrieNode* root;

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        deleteTrie(node->children[0]);
        deleteTrie(node->children[1]);

        delete node;
    }

public:
    BinaryTrie() {
        root = new TrieNode();
    }

    void insertNumber(int number) {
        TrieNode* current = root;

        for (int i = 7; i >= 0; i--) {
            int bit = (number >> i) & 1;

            if (current->children[bit] == nullptr) {
                current->children[bit] = new TrieNode();
            }

            current = current->children[bit];
        }

        current->isEndOfNumber = true;
    }

    bool searchNumber(int number) {
        TrieNode* current = root;

        for (int i = 7; i >= 0; i--) {
            int bit = (number >> i) & 1;

            if (current->children[bit] == nullptr) {
                return false;
            }

            current = current->children[bit];
        }

        return current->isEndOfNumber;
    }

    ~BinaryTrie() {
        deleteTrie(root);
    }
};

int main() {
    BinaryTrie trie;

    int numberOfElements;

    cout << "Enter number of elements: ";
    cin >> numberOfElements;

    if (numberOfElements < 0) {
        cout << "Invalid number of elements." << endl;
        return 0;
    }

    vector<int> numbers;

    cout << "\nEnter numbers between 0 and 255:\n";

    for (int i = 0; i < numberOfElements; i++) {
        int number;
        cin >> number;

        if (number < 0 || number > 255) {
            cout << "Invalid number. Enter a value from 0 to 255.\n";
            i--;
            continue;
        }

        numbers.push_back(number);
        trie.insertNumber(number);
    }

    cout << "\nBinary Trie created successfully.\n";

    int numberOfSearches;

    cout << "\nEnter number of searches: ";
    cin >> numberOfSearches;

    if (numberOfSearches < 0) {
        cout << "Invalid number of searches." << endl;
        return 0;
    }

    cout << "\nEnter numbers to search:\n";

    for (int i = 0; i < numberOfSearches; i++) {
        int target;
        cin >> target;

        if (target < 0 || target > 255) {
            cout << "Invalid number. Enter a value from 0 to 255.\n";
            i--;
            continue;
        }

        if (trie.searchNumber(target)) {
            cout << target << " -> Number found\n";
        } else {
            cout << target << " -> Number not found\n";
        }
    }

    return 0;
}
