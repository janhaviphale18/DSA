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

// Insert a word
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

// Check whether a node has any children
bool hasChildren(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            return true;
        }
    }

    return false;
}

// Recursive helper for safe deletion
bool deleteWordHelper(TrieNode* node, const string& word, int depth) {
    // Base case: reached the end of the word
    if (depth == word.length()) {
        node->isEndOfWord = false;

        // This node can be removed only if it has no children
        return !hasChildren(node);
    }

    int index = word[depth] - 'a';

    TrieNode* child = node->children[index];

    // Recursively process the next character
    bool shouldDeleteChild = deleteWordHelper(
        child, word, depth + 1
    );

    // Remove child if it is no longer required
    if (shouldDeleteChild) {
        delete child;
        node->children[index] = nullptr;

        // Current node can also be removed if it is unnecessary
        return !node->isEndOfWord && !hasChildren(node);
    }

    return false;
}

// Safely delete a word
bool deleteWord(TrieNode* root, const string& word) {
    if (!isValidWord(word)) {
        return false;
    }

    // Verify the complete word exists
    if (!searchWord(root, word)) {
        return false;
    }

    deleteWordHelper(root, word, 0);

    return true;
}

// Display all words
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

// Count complete words
int countWords(TrieNode* node) {
    if (node == nullptr) {
        return 0;
    }

    int count = node->isEndOfWord ? 1 : 0;

    for (int i = 0; i < 26; i++) {
        count += countWords(node->children[i]);
    }

    return count;
}

// Free allocated memory
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

    cout << "Enter number of words: ";

    if (!(cin >> numberOfWords) || numberOfWords < 0) {
        cout << "Invalid number!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the words:\n";

    for (int i = 0; i < numberOfWords; i++) {
        string word;
        cin >> word;

        if (!isValidWord(word)) {
            cout << "Invalid word: " << word << endl;
        } else if (insertWord(root, word)) {
            cout << word << " inserted." << endl;
        } else {
            cout << word << " already exists." << endl;
        }
    }

    cout << "\nWords before deletion:\n";

    string currentWord = "";
    displayWords(root, currentWord);

    cout << "\nTotal words: " << countWords(root) << endl;

    int numberOfDeletions;

    cout << "\nEnter number of words to delete: ";

    if (!(cin >> numberOfDeletions) || numberOfDeletions < 0) {
        cout << "Invalid number!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter words to delete:\n";

    for (int i = 0; i < numberOfDeletions; i++) {
        string word;
        cin >> word;

        if (deleteWord(root, word)) {
            cout << word << " deleted successfully." << endl;
        } else {
            cout << word << " could not be deleted." << endl;
        }
    }

    cout << "\nWords after deletion:\n";

    currentWord = "";
    displayWords(root, currentWord);

    cout << "\nTotal words remaining: "
         << countWords(root) << endl;

    cout << "\nVerification:\n";

    string checkWord;

    cout << "Enter a word to search: ";
    cin >> checkWord;

    if (searchWord(root, checkWord)) {
        cout << checkWord << " still exists." << endl;
    } else {
        cout << checkWord << " does not exist." << endl;
    }

    deleteTrie(root);

    return 0;
}
