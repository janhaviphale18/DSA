#include <iostream>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    int prefixCount;

    TrieNode() {
        isEndOfWord = false;
        prefixCount = 0;

        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

// Validate lowercase English words
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

// Search for an exact word
bool searchWord(TrieNode* root, const string& word) {
    if (!isValidWord(word)) {
        return false;
    }

    TrieNode* current = root;

    for (char ch : word) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            return false;
        }

        current = current->children[index];
    }

    return current->isEndOfWord;
}

// Insert a distinct word into the Trie
bool insertWord(TrieNode* root, const string& word) {
    if (!isValidWord(word)) {
        return false;
    }

    // Prevent duplicate insertion
    if (searchWord(root, word)) {
        return false;
    }

    TrieNode* current = root;

    for (char ch : word) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];

        // Count words passing through this node
        current->prefixCount++;
    }

    current->isEndOfWord = true;

    return true;
}

// Find the shortest unique prefix of a word
string shortestUniquePrefix(TrieNode* root, const string& word) {
    if (!searchWord(root, word)) {
        return "";
    }

    TrieNode* current = root;
    string prefix = "";

    for (char ch : word) {
        int index = ch - 'a';

        current = current->children[index];

        prefix += ch;

        // First prefix used by only one word
        if (current->prefixCount == 1) {
            return prefix;
        }
    }

    return prefix;
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

    cout << "Enter the number of words: ";

    if (!(cin >> numberOfWords) || numberOfWords < 0) {
        cout << "Invalid number of words!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the lowercase words:\n";

    for (int i = 0; i < numberOfWords; i++) {
        string word;
        cin >> word;

        if (!isValidWord(word)) {
            cout << "Invalid word: " << word << endl;
        } else if (insertWord(root, word)) {
            cout << word << " inserted successfully." << endl;
        } else {
            cout << word << " already exists." << endl;
        }
    }

    cout << "\nShortest unique prefixes:\n";

    // Read the words again to display their unique prefixes
    // The Trie stores the words, so no separate word array is required.
    int queryCount;

    cout << "\nEnter the number of words to check: ";

    if (!(cin >> queryCount) || queryCount < 0) {
        cout << "Invalid number of queries!" << endl;
        deleteTrie(root);
        return 1;
    }

    for (int i = 0; i < queryCount; i++) {
        string word;

        cout << "Enter word: ";
        cin >> word;

        if (!isValidWord(word) || !searchWord(root, word)) {
            cout << "Word not found or invalid input." << endl;
        } else {
            cout << word << " -> "
                 << shortestUniquePrefix(root, word) << endl;
        }
    }

    deleteTrie(root);

    return 0;
}
