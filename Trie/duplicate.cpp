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

// Insert a word and identify duplicates
bool insertWord(TrieNode* root, const string& word, int& totalWords) {
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

    // Check whether the word already exists
    if (current->isEndOfWord) {
        return false;
    }

    // Mark the word as complete
    current->isEndOfWord = true;

    totalWords++;

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

// Count all unique words using DFS
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

// Free Trie memory
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

    int totalWords = 0;
    int numberOfInsertions;

    cout << "Enter the number of words to insert: ";

    if (!(cin >> numberOfInsertions) || numberOfInsertions < 0) {
        cout << "Invalid number of insertions!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the words:\n";

    for (int i = 0; i < numberOfInsertions; i++) {
        string word;
        cin >> word;

        if (!isValidWord(word)) {
            cout << word << " is invalid. Use lowercase letters only."
                 << endl;
            continue;
        }

        if (insertWord(root, word, totalWords)) {
            cout << word << " inserted successfully." << endl;
        } else {
            cout << word << " is a duplicate. Not inserted again."
                 << endl;
        }
    }

    cout << "\nTotal unique words: " << totalWords << endl;

    cout << "Total words verified using DFS: "
         << countWords(root) << endl;

    cout << "\nEnter a word to check whether it exists: ";

    string search;
    cin >> search;

    if (searchWord(root, search)) {
        cout << search << " exists in the Trie." << endl;
    } else {
        cout << search << " does not exist in the Trie." << endl;
    }

    deleteTrie(root);

    return 0;
}
