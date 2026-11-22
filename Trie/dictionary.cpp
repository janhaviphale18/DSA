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

class WordDictionary {
private:
    TrieNode* root;

    bool searchHelper(TrieNode* node, const string& pattern, int index) {
        if (node == nullptr) {
            return false;
        }

        if (index == pattern.length()) {
            return node->isEndOfWord;
        }

        char currentCharacter = pattern[index];

        if (currentCharacter == '.') {
            for (int i = 0; i < 26; i++) {
                if (node->children[i] != nullptr) {
                    if (searchHelper(node->children[i], pattern, index + 1)) {
                        return true;
                    }
                }
            }

            return false;
        }

        int childIndex = currentCharacter - 'a';

        if (node->children[childIndex] == nullptr) {
            return false;
        }

        return searchHelper(
            node->children[childIndex],
            pattern,
            index + 1
        );
    }

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
    WordDictionary() {
        root = new TrieNode();
    }

    void addWord(const string& word) {
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

    bool search(const string& pattern) {
        if (pattern.empty()) {
            return false;
        }

        for (int i = 0; i < pattern.length(); i++) {
            if (pattern[i] != '.' &&
                (pattern[i] < 'a' || pattern[i] > 'z')) {
                return false;
            }
        }

        return searchHelper(root, pattern, 0);
    }

    ~WordDictionary() {
        deleteTrie(root);
    }
};

int main() {
    WordDictionary dictionary;

    int numberOfWords;

    cout << "Enter number of words to insert: ";
    cin >> numberOfWords;

    if (numberOfWords < 0) {
        cout << "Invalid number of words." << endl;
        return 0;
    }

    cout << "\nEnter words:\n";

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

        dictionary.addWord(word);
    }

    int numberOfSearches;

    cout << "\nEnter number of search patterns: ";
    cin >> numberOfSearches;

    if (numberOfSearches < 0) {
        cout << "Invalid number of searches." << endl;
        return 0;
    }

    cout << "\nEnter search patterns (. for wildcard):\n";

    for (int i = 0; i < numberOfSearches; i++) {
        string pattern;
        cin >> pattern;

        if (dictionary.search(pattern)) {
            cout << pattern << " -> Word found\n";
        } else {
            cout << pattern << " -> Word not found\n";
        }
    }

    return 0;
}
