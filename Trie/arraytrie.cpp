#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
    TrieNode* child[2];
    int count;

    TrieNode() {
        child[0] = nullptr;
        child[1] = nullptr;
        count = 0;
    }
};

class BinaryTrie {
private:
    TrieNode* root;

public:
    BinaryTrie() {
        root = new TrieNode();
    }

    void insertNumber(int number) {
        TrieNode* current = root;

        for (int bit = 30; bit >= 0; bit--) {
            int bitValue = (number >> bit) & 1;

            if (current->child[bitValue] == nullptr) {
                current->child[bitValue] = new TrieNode();
            }

            current = current->child[bitValue];
            current->count++;
        }
    }

    int countLessThan(int number, int limit) {
        if (limit <= 0) {
            return 0;
        }

        TrieNode* current = root;
        int result = 0;

        for (int bit = 30; bit >= 0; bit--) {
            if (current == nullptr) {
                break;
            }

            int numberBit = (number >> bit) & 1;
            int limitBit = (limit >> bit) & 1;

            if (limitBit == 1) {
                if (current->child[numberBit] != nullptr) {
                    result += current->child[numberBit]->count;
                }

                current = current->child[1 - numberBit];
            }
            else {
                current = current->child[numberBit];
            }
        }

        return result;
    }

    ~BinaryTrie() {
        deleteTrie(root);
    }

private:
    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        deleteTrie(node->child[0]);
        deleteTrie(node->child[1]);

        delete node;
    }
};

int main() {
    int n;

    cout << "Enter number of array elements: ";

    if (!(cin >> n) || n <= 0) {
        cout << "Invalid array size.\n";
        return 1;
    }

    vector<int> nums(n);

    cout << "Enter array elements (0 to 1000000000):\n";

    for (int i = 0; i < n; i++) {
        if (!(cin >> nums[i]) ||
            nums[i] < 0 || nums[i] > 1000000000) {
            cout << "Invalid array element.\n";
            return 1;
        }
    }

    int low, high;

    cout << "Enter low and high: ";

    if (!(cin >> low >> high) ||
        low < 0 || high < low || high > 1000000000) {
        cout << "Invalid range.\n";
        return 1;
    }

    BinaryTrie trie;

    long long answer = 0;

    for (int i = 0; i < n; i++) {
        int countUpToHigh =
            trie.countLessThan(nums[i], high + 1);

        int countBelowLow =
            trie.countLessThan(nums[i], low);

        answer += countUpToHigh - countBelowLow;

        trie.insertNumber(nums[i]);
    }

    cout << "\nNumber of pairs with XOR in range ["
         << low << ", " << high << "]: "
         << answer << "\n";

    return 0;
}
