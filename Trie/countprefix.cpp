#include <iostream>
#include <string>
#include <limits>
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

// Validate that a word contains only lowercase English letters
bool isValidWord(const string& word) {
    if (word.empty()) {
        return false;
    }

    for (char ch : word) {
        if (ch < 'a' || ch > 'z') {
            return false;
        }
    }

    return true;
}

// Insert a word into the Trie
bool insertWord(TrieNode* root, const string& word) {
    if (!isValidWord(word)) {
        return false;
    }

    TrieNode* current = root;

    for (char ch : word) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

    current->isEndOfWord = true;

    return true;
}

// Recursively count complete words in a subtree
int countWords(TrieNode* node) {
    if (node == nullptr) {
        return 0;
    }

    int count = 0;

    if (node->isEndOfWord) {
        count++;
    }

    for (int i = 0; i < 26; i++) {
        count += countWords(node->children[i]);
    }

    return count;
}

// Find the node corresponding to a given prefix
TrieNode* findPrefixNode(TrieNode* root, const string& prefix) {
    TrieNode* current = root;

    for (char ch : prefix) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            return nullptr;
        }

        current = current->children[index];
    }

    return current;
}

// Count words beginning with a given prefix
int countWordsWithPrefix(TrieNode* root, const string& prefix) {
    if (!isValidWord(prefix)) {
        return 0;
    }

    TrieNode* prefixNode = findPrefixNode(root, prefix);

    if (prefixNode == nullptr) {
        return 0;
    }

    return countWords(prefixNode);
}

// Free allocated Trie memory
void deleteTrie(TrieNode* node) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        deleteTrie(node->children[i]);
    }

    delete node;
}

int main() {
    TrieNode* root = new TrieNode();

    int numberOfWords;

    cout << "Enter the number of words to insert: ";

    if (!(cin >> numberOfWords) || numberOfWords < 0) {
        cout << "Invalid number of words!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter " << numberOfWords << " lowercase words:\n";

    for (int i = 0; i < numberOfWords; i++) {
        string word;
        cin >> word;

        if (insertWord(root, word)) {
            cout << "Inserted: " << word << endl;
        } else {
            cout << "Invalid word: " << word << endl;
        }
    }

    int numberOfQueries;

    cout << "\nEnter the number of prefix queries: ";

    if (!(cin >> numberOfQueries) || numberOfQueries < 0) {
        cout << "Invalid number of queries!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the prefixes to search:\n";

    for (int i = 0; i < numberOfQueries; i++) {
        string prefix;
        cin >> prefix;

        if (!isValidWord(prefix)) {
            cout << "Invalid prefix: " << prefix << endl;
            continue;
        }

        int result = countWordsWithPrefix(root, prefix);

        cout << "Words starting with \"" << prefix
             << "\": " << result << endl;
    }

    deleteTrie(root);

    return 0;
}
