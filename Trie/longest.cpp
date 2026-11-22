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

// Find the longest word whose every prefix exists
void findLongestWord(
    TrieNode* node,
    string& currentWord,
    string& longestWord
) {
    if (node == nullptr) {
        return;
    }

    // Update the answer at every valid word
    if (currentWord.length() > longestWord.length()) {
        longestWord = currentWord;
    } else if (
        currentWord.length() == longestWord.length() &&
        currentWord < longestWord
    ) {
        longestWord = currentWord;
    }

    // Explore only complete-word children
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr &&
            node->children[i]->isEndOfWord) {

            currentWord.push_back(char('a' + i));

            findLongestWord(
                node->children[i],
                currentWord,
                longestWord
            );

            // Backtrack
            currentWord.pop_back();
        }
    }
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

    string currentWord = "";
    string longestWord = "";

    findLongestWord(root, currentWord, longestWord);

    cout << "\nLongest word with all prefixes present: ";

    if (longestWord.empty()) {
        cout << "No valid word found.";
    } else {
        cout << longestWord;
    }

    cout << endl;

    deleteTrie(root);

    return 0;
}
