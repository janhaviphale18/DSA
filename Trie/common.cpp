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

// Find the longest common prefix
string longestCommonPrefix(TrieNode* root) {
    string prefix = "";

    TrieNode* current = root;

    while (true) {
        // Stop if the current node ends a word
        if (current->isEndOfWord) {
            break;
        }

        int childCount = 0;
        int childIndex = -1;

        // Count existing children
        for (int i = 0; i < 26; i++) {
            if (current->children[i] != nullptr) {
                childCount++;
                childIndex = i;
            }
        }

        // Stop if there are zero or multiple children
        if (childCount != 1) {
            break;
        }

        // Add the only available character
        prefix += char('a' + childIndex);

        // Move to the next node
        current = current->children[childIndex];
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

    if (!(cin >> numberOfWords) || numberOfWords <= 0) {
        cout << "Please enter a positive number of words!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the lowercase words:\n";

    for (int i = 0; i < numberOfWords; i++) {
        string word;
        cin >> word;

        if (!isValidWord(word)) {
            cout << "Invalid word: " << word << endl;
            deleteTrie(root);
            return 1;
        }

        insertWord(root, word);
    }

    string result = longestCommonPrefix(root);

    cout << "\nLongest Common Prefix: ";

    if (result.empty()) {
        cout << "No common prefix";
    } else {
        cout << result;
    }

    cout << endl;

    deleteTrie(root);

    return 0;
}
