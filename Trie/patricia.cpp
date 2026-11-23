#include <iostream>
#include <vector>
using namespace std;

const int BIT_WIDTH = 8;

struct PatriciaNode {
    bool isLeaf;
    int bitIndex;
    unsigned int value;

    PatriciaNode* child[2];

    PatriciaNode(unsigned int number) {
        isLeaf = true;
        bitIndex = -1;
        value = number;

        child[0] = nullptr;
        child[1] = nullptr;
    }

    PatriciaNode(int bit, PatriciaNode* left,
                 PatriciaNode* right) {
        isLeaf = false;
        bitIndex = bit;
        value = 0;

        child[0] = left;
        child[1] = right;
    }
};

class PatriciaTrie {
private:
    PatriciaNode* root;
    int wordCount;

    int getBit(unsigned int number, int bitIndex) {
        return (number >> bitIndex) & 1U;
    }

    int findFirstDifferentBit(unsigned int first,
                              unsigned int second) {
        for (int bit = BIT_WIDTH - 1; bit >= 0; bit--) {
            if (getBit(first, bit) != getBit(second, bit)) {
                return bit;
            }
        }

        return -1;
    }

    PatriciaNode* findLeaf(unsigned int number) {
        PatriciaNode* current = root;

        while (current != nullptr && !current->isLeaf) {
            int direction = getBit(number, current->bitIndex);

            current = current->child[direction];
        }

        return current;
    }

    void insertNode(PatriciaNode*& current,
                    unsigned int number,
                    int newBit) {

        if (current == nullptr || current->isLeaf ||
            current->bitIndex < newBit) {

            PatriciaNode* newLeaf = new PatriciaNode(number);

            PatriciaNode* oldNode = current;

            int direction = getBit(number, newBit);

            if (direction == 0) {
                current = new PatriciaNode(
                    newBit,
                    newLeaf,
                    oldNode
                );
            }
            else {
                current = new PatriciaNode(
                    newBit,
                    oldNode,
                    newLeaf
                );
            }

            return;
        }

        int direction = getBit(number, current->bitIndex);

        insertNode(
            current->child[direction],
            number,
            newBit
        );
    }

    void displayBinary(unsigned int number) {
        for (int bit = BIT_WIDTH - 1; bit >= 0; bit--) {
            cout << getBit(number, bit);
        }
    }

    void displayValues(PatriciaNode* current) {
        if (current == nullptr) {
            return;
        }

        if (current->isLeaf) {
            displayBinary(current->value);
            cout << " (" << current->value << ")\n";
            return;
        }

        displayValues(current->child[0]);
        displayValues(current->child[1]);
    }

    void displayStructure(PatriciaNode* current, int depth) {
        if (current == nullptr) {
            return;
        }

        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }

        if (current->isLeaf) {
            cout << "Leaf: ";
            displayBinary(current->value);
            cout << " (" << current->value << ")\n";
            return;
        }

        cout << "Branch at bit " << current->bitIndex << "\n";

        displayStructure(current->child[0], depth + 1);
        displayStructure(current->child[1], depth + 1);
    }

    void deleteTrie(PatriciaNode* current) {
        if (current == nullptr) {
            return;
        }

        if (!current->isLeaf) {
            deleteTrie(current->child[0]);
            deleteTrie(current->child[1]);
        }

        delete current;
    }

public:
    PatriciaTrie() {
        root = nullptr;
        wordCount = 0;
    }

    bool insert(unsigned int number) {
        if (number > 255) {
            cout << "Only 8-bit numbers (0 to 255) are allowed.\n";
            return false;
        }

        if (root == nullptr) {
            root = new PatriciaNode(number);
            wordCount++;

            cout << "Number inserted successfully.\n";
            return true;
        }

        PatriciaNode* existingLeaf = findLeaf(number);

        if (existingLeaf->value == number) {
            cout << "Number already exists.\n";
            return false;
        }

        int differentBit = findFirstDifferentBit(
            number,
            existingLeaf->value
        );

        insertNode(root, number, differentBit);

        wordCount++;

        cout << "Number inserted successfully.\n";
        return true;
    }

    bool search(unsigned int number) {
        if (number > 255 || root == nullptr) {
            return false;
        }

        PatriciaNode* result = findLeaf(number);

        return result != nullptr && result->value == number;
    }

    void displayAllNumbers() {
        if (root == nullptr) {
            cout << "Patricia Trie is empty.\n";
            return;
        }

        cout << "\nStored numbers:\n";
        displayValues(root);
    }

    void displayTrieStructure() {
        if (root == nullptr) {
            cout << "Patricia Trie is empty.\n";
            return;
        }

        cout << "\nPatricia Trie Structure:\n";
        displayStructure(root, 0);
    }

    int getWordCount() {
        return wordCount;
    }

    ~PatriciaTrie() {
        deleteTrie(root);
    }
};

int main() {
    PatriciaTrie trie;

    int n;

    cout << "Enter number of initial numbers: ";

    if (!(cin >> n) || n < 0) {
        cout << "Invalid number of elements.\n";
        return 1;
    }

    unsigned int number;

    cout << "Enter numbers (0 to 255):\n";

    for (int i = 0; i < n; i++) {
        if (!(cin >> number)) {
            cout << "Invalid input.\n";
            return 1;
        }

        trie.insert(number);
    }

    int operationCount;

    cout << "\nEnter number of operations: ";

    if (!(cin >> operationCount) || operationCount < 0) {
        cout << "Invalid number of operations.\n";
        return 1;
    }

    for (int i = 0; i < operationCount; i++) {
        int choice;

        cout << "\n1. Insert number\n";
        cout << "2. Search number\n";
        cout << "3. Display all numbers\n";
        cout << "4. Count numbers\n";
        cout << "5. Display Trie structure\n";

        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                cout << "Enter number: ";

                if (!(cin >> number)) {
                    cout << "Invalid input.\n";
                    return 1;
                }

                trie.insert(number);
                break;

            case 2:
                cout << "Enter number to search: ";

                if (!(cin >> number)) {
                    cout << "Invalid input.\n";
                    return 1;
                }

                if (trie.search(number)) {
                    cout << "Number found.\n";
                }
                else {
                    cout << "Number not found.\n";
                }
                break;

            case 3:
                trie.displayAllNumbers();
                break;

            case 4:
                cout << "Total distinct numbers: "
                     << trie.getWordCount() << "\n";
                break;

            case 5:
                trie.displayTrieStructure();
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
