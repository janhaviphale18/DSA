#include <iostream>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;

        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

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
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;

        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEndOfWord = true;
    }

    string findShortestRoot(const string& word) {
        TrieNode* current = root;
        string prefix = "";

        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';

            if (current->children[index] == nullptr) {
                return word;
            }

            current = current->children[index];
            prefix += word[i];

            if (current->isEndOfWord) {
                return prefix;
            }
        }

        return word;
    }

    ~Trie() {
        deleteTrie(root);
    }
};

int main() {
    Trie trie;

    int numberOfRoots;

    cout << "Enter number of dictionary roots: ";
    cin >> numberOfRoots;

    if (numberOfRoots < 0) {
        cout << "Invalid number of roots." << endl;
        return 0;
    }

    cout << "\nEnter dictionary roots:\n";

    for (int i = 0; i < numberOfRoots; i++) {
        string rootWord;
        cin >> rootWord;

        bool valid = true;

        for (int j = 0; j < rootWord.length(); j++) {
            if (rootWord[j] < 'a' || rootWord[j] > 'z') {
                valid = false;
                break;
            }
        }

        if (rootWord.empty() || !valid) {
            cout << "Invalid root. Use lowercase letters only.\n";
            i--;
            continue;
        }

        trie.insert(rootWord);
    }

    int numberOfWords;

    cout << "\nEnter number of words in sentence: ";
    cin >> numberOfWords;

    if (numberOfWords < 0) {
        cout << "Invalid number of words." << endl;
        return 0;
    }

    cout << "\nEnter sentence words (lowercase only):\n";

    string result = "";

    for (int i = 0; i < numberOfWords; i++) {
        string word;
        cin >> word;

        bool valid = true;

        for (int j = 0; j < word.length(); j++) {
            if (word[j] < 'a' || word[j] > 'z') {
                valid = false;
                break;
            }
        }

        if (word.empty() || !valid) {
            cout << "Invalid word. Use lowercase letters only.\n";
            i--;
            continue;
        }

        string replacedWord = trie.findShortestRoot(word);

        if (i > 0) {
            result += " ";
        }

        result += replacedWord;
    }

    cout << "\nOriginal words replaced successfully:\n";
    cout << result << endl;

    return 0;
}
