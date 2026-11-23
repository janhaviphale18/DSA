#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TrieNode {
    TrieNode* child[2];

    TrieNode() {
        child[0] = nullptr;
        child[1] = nullptr;
    }
};

class BinaryTrie {
private:
    TrieNode* root;
    int insertedCount;

public:
    BinaryTrie() {
        root = new TrieNode();
        insertedCount = 0;
    }

    void insertNumber(int number) {
        TrieNode* current = root;

        for (int bit = 30; bit >= 0; bit--) {
            int bitValue = (number >> bit) & 1;

            if (current->child[bitValue] == nullptr) {
                current->child[bitValue] = new TrieNode();
            }

            current = current->child[bitValue];
        }

        insertedCount++;
    }

    int findMaximumXOR(int number) {
        if (insertedCount == 0) {
            return -1;
        }

        TrieNode* current = root;
        int maximumXOR = 0;

        for (int bit = 30; bit >= 0; bit--) {
            int bitValue = (number >> bit) & 1;
            int oppositeBit = 1 - bitValue;

            if (current->child[oppositeBit] != nullptr) {
                maximumXOR |= (1 << bit);
                current = current->child[oppositeBit];
            }
            else {
                current = current->child[bitValue];
            }
        }

        return maximumXOR;
    }

    bool isEmpty() {
        return insertedCount == 0;
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

struct Query {
    int x;
    int m;
    int originalIndex;
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

    int q;

    cout << "Enter number of queries: ";
    if (!(cin >> q) || q <= 0) {
        cout << "Invalid number of queries.\n";
        return 1;
    }

    vector<Query> queries(q);

    cout << "Enter each query as x m:\n";

    for (int i = 0; i < q; i++) {
        if (!(cin >> queries[i].x >> queries[i].m) ||
            queries[i].x < 0 || queries[i].x > 1000000000 ||
            queries[i].m < 0 || queries[i].m > 1000000000) {
            cout << "Invalid query values.\n";
            return 1;
        }

        queries[i].originalIndex = i;
    }

    sort(nums.begin(), nums.end());

    sort(queries.begin(), queries.end(),
         [](const Query& a, const Query& b) {
             return a.m < b.m;
         });

    BinaryTrie trie;

    vector<int> answers(q, -1);

    int j = 0;

    for (int i = 0; i < q; i++) {
        int x = queries[i].x;
        int m = queries[i].m;

        while (j < n && nums[j] <= m) {
            trie.insertNumber(nums[j]);
            j++;
        }

        if (!trie.isEmpty()) {
            answers[queries[i].originalIndex] =
                trie.findMaximumXOR(x);
        }
    }

    cout << "\nMaximum XOR Results:\n";

    for (int i = 0; i < q; i++) {
        cout << "Query " << i + 1 << ": "
             << answers[i] << "\n";
    }

    return 0;
}
