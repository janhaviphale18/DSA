#include <iostream>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class DistinctSubstringCounter {
private:
    TrieNode* root;
    int distinctCount;

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 26; i++) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

public:
    DistinctSubstringCounter() {
        root = new TrieNode();
        distinctCount = 0;
    }

    int countDistinctSubstrings(const string& text) {
        distinctCount = 0;

        for (int i = 0; i < text.length(); i++) {
            TrieNode* current = root;

            for (int j = i; j < text.length(); j++) {
                int index = text[j] - 'a';

                if (current->children[index] == nullptr) {
                    current->children[index] = new TrieNode();

                    distinctCount++;
                }

                current = current->children[index];
            }
        }

        return distinctCount;
    }

    ~DistinctSubstringCounter() {
        deleteTrie(root);
    }
};

int main() {
    DistinctSubstringCounter counter;

    string text;

    cout << "Enter a lowercase string: ";
    cin >> text;

    bool valid = !text.empty();

    for (int i = 0; i < text.length(); i++) {
        if (text[i] < 'a' || text[i] > 'z') {
            valid = false;
            break;
        }
    }

    if (!valid) {
        cout << "Invalid input. Use lowercase letters only."
             << endl;
        return 0;
    }

    int result = counter.countDistinctSubstrings(text);

    cout << "\nInput string: " << text << endl;

    cout << "Number of distinct non-empty substrings: "
         << result << endl;

    cout << "Number of distinct substrings including empty: "
         << result + 1 << endl;

    return 0;
}
