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

// Find the node corresponding to a prefix
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

// Collect suggestions using DFS
bool collectSuggestions(
    TrieNode* node,
    string& currentWord,
    int maximumSuggestions,
    int& suggestionCount
) {
    if (node == nullptr) {
        return false;
    }

    // Stop if the required number of suggestions is reached
    if (suggestionCount >= maximumSuggestions) {
        return true;
    }

    // Display the word if it is complete
    if (node->isEndOfWord) {
        cout << currentWord << endl;
        suggestionCount++;

        if (suggestionCount >= maximumSuggestions) {
            return true;
        }
    }

    // Explore children alphabetically
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            currentWord.push_back(char('a' + i));

            bool limitReached = collectSuggestions(
                node->children[i],
                currentWord,
                maximumSuggestions,
                suggestionCount
            );

            currentWord.pop_back();

            if (limitReached) {
                return true;
            }
        }
    }

    return false;
}

// Generate autocomplete suggestions
void autocomplete(
    TrieNode* root,
    const string& prefix,
    int maximumSuggestions
) {
    if (!isValidWord(prefix)) {
        cout << "Invalid prefix!" << endl;
        return;
    }

    if (maximumSuggestions <= 0) {
        cout << "Suggestion limit must be positive." << endl;
        return;
    }

    TrieNode* prefixNode = findPrefixNode(root, prefix);

    if (prefixNode == nullptr) {
        cout << "No suggestions found for: "
             << prefix << endl;
        return;
    }

    string currentWord = prefix;
    int suggestionCount = 0;

    cout << "\nAutocomplete suggestions:\n";

    collectSuggestions(
        prefixNode,
        currentWord,
        maximumSuggestions,
        suggestionCount
    );

    if (suggestionCount == 0) {
        cout << "No suggestions found." << endl;
    } else {
        cout << "Total suggestions: "
             << suggestionCount << endl;
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

    cout << "Enter the number of dictionary words: ";

    if (!(cin >> numberOfWords) || numberOfWords < 0) {
        cout << "Invalid number of words!" << endl;
        deleteTrie(root);
        return 1;
    }

    cout << "\nEnter the dictionary words:\n";

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

    string prefix;
    int maximumSuggestions;

    cout << "\nEnter search prefix: ";
    cin >> prefix;

    cout << "Enter maximum number of suggestions: ";

    if (!(cin >> maximumSuggestions)) {
        cout << "Invalid suggestion limit!" << endl;
        deleteTrie(root);
        return 1;
    }

    autocomplete(root, prefix, maximumSuggestions);

    deleteTrie(root);

    return 0;
}
