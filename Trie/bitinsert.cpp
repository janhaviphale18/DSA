#include <iostream>
#include <string>
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
    int numberCount;

    void displayNumbers(
        TrieNode* node,
        string& binaryNumber
    ) {
        if (node == nullptr) {
            return;
        }

        if (node->isEndOfNumber) {
            cout << binaryNumber << endl;
        }

        for (int i = 0; i < 2; i++) {
            if (node->children[i] != nullptr) {
                binaryNumber += char('0' + i);

                displayNumbers(
                    node->children[i],
                    binaryNumber
                );

                binaryNumber.pop_back();
            }
        }
    }

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
        numberCount = 0;
    }

    bool insertNumber(int number) {
        if (number < 0 || number > 255) {
            return false;
        }

        TrieNode* current = root;

        for (int i = 7; i >= 0; i--) {
            int bit = (number >> i) & 1;

            if (current->children[bit] == nullptr) {
                current->children[bit] = new TrieNode();
            }

            current = current->children[bit];
        }

        if (current->isEndOfNumber) {
            return false;
        }

        current->isEndOfNumber = true;
        numberCount++;

        return true;
    }

    bool searchNumber(int number) {
        if (number < 0 || number > 255) {
            return false;
        }

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

    void displayAllNumbers() {
        if (numberCount == 0) {
            cout << "Binary Trie is empty.\n";
            return;
        }

        string binaryNumber = "";

        cout << "\nStored binary numbers:\n";

        displayNumbers(root, binaryNumber);
    }

    int getCount() {
        return numberCount;
    }

    ~BinaryTrie() {
        deleteTrie(root);
    }
};

int main() {
    BinaryTrie trie;

    int numberOfInsertions;

    cout << "Enter number of insertions: ";
    cin >> numberOfInsertions;

    if (numberOfInsertions < 0) {
        cout << "Invalid number of insertions.\n";
        return 0;
    }

    cout << "\nEnter numbers between 0 and 255:\n";

    for (int i = 0; i < numberOfInsertions; i++) {
        int number;
        cin >> number;

        if (number < 0 || number > 255) {
            cout << "Invalid number. Try again.\n";
            i--;
            continue;
        }

        if (trie.insertNumber(number)) {
            cout << number << " inserted successfully.\n";
        } else {
            cout << number << " already exists.\n";
        }
    }

    int numberOfSearches;

    cout << "\nEnter number of searches: ";
    cin >> numberOfSearches;

    if (numberOfSearches < 0) {
        cout << "Invalid number of searches.\n";
        return 0;
    }

    for (int i = 0; i < numberOfSearches; i++) {
        int target;

        cout << "Enter number to search: ";
        cin >> target;

        if (trie.searchNumber(target)) {
            cout << target << " found in Binary Trie.\n";
        } else {
            cout << target << " not found in Binary Trie.\n";
        }
    }

    trie.displayAllNumbers();

    cout << "\nTotal distinct numbers stored: "
         << trie.getCount() << endl;

    return 0;
}
