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

// Check whether a prefix exists
bool startsWith(TrieNode* root, const string& prefix) {
    if (!isValidWord(prefix)) {
        return false;
    }

    TrieNode* current = root;

    for (char ch : prefix) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            return false;
        }

        current = current->children[index];
    }

    return true;
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

// Recursive helper for safe deletion
bool deleteWordHelper(
    TrieNode* node,
    const string& word,
    int depth
) {
    if (depth == static_cast<int>(word.length())) {
        node->isEndOfWord = false;

        return !hasChildren(node);
    }

    int index = word[depth] - 'a';

    TrieNode* child = node->children[index];

    bool shouldDeleteChild = deleteWordHelper(
        child, word, depth + 1
    );

    if (shouldDeleteChild) {
        delete child;
        node->children[index] = nullptr;

        return !node->isEndOfWord && !hasChildren(node);
    }

    return false;
}

// Delete a complete word safely
bool deleteWord(TrieNode* root, const string& word) {
    if (!isValidWord(word)) {
        return false;
    }

    if (!searchWord(root, word)) {
        return false;
    }

    deleteWordHelper(root, word, 0);

    return true;
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

// Display words in alphabetical order
void displayWords(
    TrieNode* node,
    string& currentWord,
    int& wordCount
) {
    if (node == nullptr) {
        return;
    }

    if (node->isEndOfWord) {
        cout << currentWord << endl;
        wordCount++;
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            currentWord.push_back(char('a' + i));

            displayWords(node->children[i], currentWord, wordCount);

            currentWord.pop_back();
        }
    }
}

// Free all allocated memory
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

    int choice;

    while (true) {
        cout << "\n========== TRIE EDGE CASES ==========\n";
        cout << "1. Insert a word\n";
        cout << "2. Search a word\n";
        cout << "3. Check a prefix\n";
        cout << "4. Delete a word\n";
        cout << "5. Display all words\n";
        cout << "6. Count words\n";
        cout << "7. Check whether Trie is empty\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        if (choice == 8) {
            break;
        }

        string word;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;

                if (!isValidWord(word)) {
                    cout << "Invalid word! Use lowercase letters only."
                         << endl;
                } else if (insertWord(root, word)) {
                    cout << "Word inserted successfully." << endl;
                } else {
                    cout << "Duplicate word! Already exists." << endl;
                }

                break;

            case 2:
                cout << "Enter word to search: ";
                cin >> word;

                if (searchWord(root, word)) {
                    cout << "Word found." << endl;
                } else {
                    cout << "Word not found or invalid input." << endl;
                }

                break;

            case 3:
                cout << "Enter prefix: ";
                cin >> word;

                if (startsWith(root, word)) {
                    cout << "Prefix exists." << endl;
                } else {
                    cout << "Prefix not found or invalid input."
                         << endl;
                }

                break;

            case 4:
                cout << "Enter word to delete: ";
                cin >> word;

                if (deleteWord(root, word)) {
                    cout << "Word deleted successfully." << endl;
                } else {
                    cout << "Word not found or invalid input."
                         << endl;
                }

                break;

            case 5: {
                int wordCount = 0;
                string currentWord = "";

                cout << "\nStored words:\n";

                displayWords(root, currentWord, wordCount);

                if (wordCount == 0) {
                    cout << "Trie is empty." << endl;
                }

                break;
            }

            case 6:
                cout << "Total unique words: "
                     << countWords(root) << endl;

                break;

            case 7:
                if (countWords(root) == 0) {
                    cout << "Trie is empty." << endl;
                } else {
                    cout << "Trie contains words." << endl;
                }

                break;

            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }

    deleteTrie(root);

    cout << "\nTrie memory released successfully." << endl;
    cout << "Program terminated." << endl;

    return 0;
}
