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

// Display all words in the prefix subtree
void displayPrefixWords(
    TrieNode* node,
    string& currentWord,
    int& wordCount
) {
    if (node == nullptr) {
        return;
    }

    // Print the word if this node marks its end
    if (node->isEndOfWord) {
        cout << currentWord << endl;
        wordCount++;
    }

    // Explore all children
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            currentWord.push_back(char('a' + i));

            displayPrefixWords(
                node->children[i],
                currentWord,
                wordCount
            );

            // Backtrack
            currentWord.pop_back();
        }
    }
}

// Display words beginning with a given prefix
void displayWordsWithPrefix(
    TrieNode* root,
    const string& prefix
) {
    if (!isValidWord(prefix)) {
        cout << "Invalid prefix!" << endl;
        return;
    }

    TrieNode* prefixNode = findPrefixNode(root, prefix);

    if (prefixNode == nullptr) {
        cout << "No words found with prefix: "
             << prefix << endl;
        return;
    }

    string currentWord = prefix;
    int wordCount = 0;

    cout << "\nWords beginning with \"" << prefix << "\":\n";

    displayPrefixWords(prefixNode, currentWord, wordCount);

    if (wordCount == 0) {
        cout << "No complete words found." << endl;
    } else {
        cout << "Total matching words: " << wordCount << endl;
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

    cout << "\nEnter the words:\n";

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

    int numberOfQueries;

    cout << "\nEnter the number of prefix queries: ";

    if (!(cin >> numberOfQueries) || numberOfQueries < 0) {
        cout << "Invalid number of queries!" << endl;
        deleteTrie(root);
        return 1;
    }

    for (int i = 0; i < numberOfQueries; i++) {
        string prefix;

        cout << "\nEnter prefix " << i + 1 << ": ";
        cin >> prefix;

        displayWordsWithPrefix(root, prefix);
    }

    deleteTrie(root);

    return 0;
}
