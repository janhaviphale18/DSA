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

    if (current->isEndOfWord) {
        return false;
    }

    current->isEndOfWord = true;

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

// Check whether a node has children
bool hasChildren(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            return true;
        }
    }

    return false;
}

// Recursively delete a word from the Trie
bool deleteWordHelper(TrieNode* node, const string& word, int depth) {
    if (node == nullptr) {
        return false;
    }

    // Base case: reached the final character
    if (depth == word.length()) {
        if (!node->isEndOfWord) {
            return false;
        }

        node->isEndOfWord = false;

        return !hasChildren(node);
    }

    int index = word[depth] - 'a';

    // Required character path does not exist
    if (node->children[index] == nullptr) {
        return false;
    }

    // Recursively delete the remaining characters
    bool shouldDeleteChild = deleteWordHelper(
        node->children[index], word, depth + 1
    );

    // Delete child node if it is no longer needed
    if (shouldDeleteChild) {
        delete node->children[index];
        node->children[index] = nullptr;

        return !node->isEndOfWord && !hasChildren(node);
    }

    return false;
}

// Delete a word from the Trie
bool deleteWord(TrieNode* root, const string& word) {
    if (!isValidWord(word)) {
        return false;
    }

    return deleteWordHelper(root, word, 0);
}

// Count all complete words
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

// Display all words in alphabetical order
void displayWords(TrieNode* node, string& currentWord) {
    if (node == nullptr) {
        return;
    }

    if (node->isEndOfWord) {
        cout << currentWord << endl;
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            currentWord.push_back(char('a' + i));

            displayWords(node->children[i], currentWord);

            currentWord.pop_back();
        }
    }
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

    int numberOfWords;

    cout << "Enter the number of words to insert: ";

    if (!(cin >> numberOfWords) || numberOfWords < 0) {
        cout << "Invalid number of words!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the words:\n";

    for (int i = 0; i < numberOfWords; i++) {
        string word;
        cin >> word;

        if (!insertWord(root, word)) {
            if (isValidWord(word)) {
                cout << word << " already exists." << endl;
            } else {
                cout << "Invalid word: " << word << endl;
            }
        } else {
            cout << word << " inserted successfully." << endl;
        }
    }

    cout << "\nWords before deletion:\n";

    string currentWord = "";
    displayWords(root, currentWord);

    cout << "\nTotal words: " << countWords(root) << endl;

    int numberOfDeletions;

    cout << "\nEnter the number of words to delete: ";

    if (!(cin >> numberOfDeletions) || numberOfDeletions < 0) {
        cout << "Invalid number of deletions!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the words to delete:\n";

    for (int i = 0; i < numberOfDeletions; i++) {
        string word;
        cin >> word;

        if (!isValidWord(word)) {
            cout << "Invalid word: " << word << endl;
            continue;
        }

        if (deleteWord(root, word)) {
            cout << word << " deleted successfully." << endl;
        } else {
            cout << word << " not found in the Trie." << endl;
        }
    }

    cout << "\nWords after deletion:\n";

    currentWord = "";
    displayWords(root, currentWord);

    cout << "\nTotal words after deletion: "
         << countWords(root) << endl;

    deleteTrie(root);

    return 0;
}
