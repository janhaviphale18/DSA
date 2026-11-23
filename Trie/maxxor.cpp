#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct TrieNode {
    TrieNode* children[2];

    TrieNode() {
        children[0] = nullptr;
        children[1] = nullptr;
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

        for (int i = 31; i >= 0; i--) {
            int bit = (number >> i) & 1;

            if (current->children[bit] == nullptr) {
                current->children[bit] = new TrieNode();
            }

            current = current->children[bit];
        }
    }

    int findMaximumXOR(int number) {
        TrieNode* current = root;

        int maximumXOR = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (number >> i) & 1;

            int oppositeBit = 1 - bit;

            if (current->children[oppositeBit] != nullptr) {
                maximumXOR |= (1 << i);

                current = current->children[oppositeBit];
            } else {
                current = current->children[bit];
            }
        }

        return maximumXOR;
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

    if (numberOfElements < 2) {
        cout << "At least two elements are required." << endl;
        return 0;
    }

    vector<int> numbers(numberOfElements);

    cout << "\nEnter non-negative integers:\n";

    for (int i = 0; i < numberOfElements; i++) {
        cin >> numbers[i];

        if (numbers[i] < 0) {
            cout << "Negative numbers are not allowed." << endl;
            return 0;
        }
    }

    int maximumXOR = 0;

    // Insert the first number.
    trie.insertNumber(numbers[0]);

    // Query first, then insert each remaining number.
    for (int i = 1; i < numberOfElements; i++) {
        int currentXOR = trie.findMaximumXOR(numbers[i]);

        if (currentXOR > maximumXOR) {
            maximumXOR = currentXOR;
        }

        trie.insertNumber(numbers[i]);
    }

    cout << "\nMaximum XOR value: "
         << maximumXOR << endl;

    return 0;
}
