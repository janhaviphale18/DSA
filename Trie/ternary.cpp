#include <iostream>
#include <string>
using namespace std;

struct TSTNode {
    char character;

    bool isEndOfWord;

    TSTNode* left;
    TSTNode* equal;
    TSTNode* right;

    TSTNode(char ch) {
        character = ch;
        isEndOfWord = false;

        left = nullptr;
        equal = nullptr;
        right = nullptr;
    }
};

class TernarySearchTrie {
private:
    TSTNode* root;
    int wordCount;
    int nodeCount;

    bool isValidWord(const string& word) {
        if (word.empty()) {
            return false;
        }

        for (char character : word) {
            if (character < 'a' || character > 'z') {
                return false;
            }
        }

        return true;
    }

    TSTNode* insertWord(TSTNode* current,
                        const string& word,
                        int index) {

        char character = word[index];

        if (current == nullptr) {
            current = new TSTNode(character);
            nodeCount++;
        }

        if (character < current->character) {
            current->left = insertWord(
                current->left,
                word,
                index
            );
        }
        else if (character > current->character) {
            current->right = insertWord(
                current->right,
                word,
                index
            );
        }
        else {
            if (index + 1 == (int)word.length()) {
                current->isEndOfWord = true;
            }
            else {
                current->equal = insertWord(
                    current->equal,
                    word,
                    index + 1
                );
            }
        }

        return current;
    }

    TSTNode* searchNode(const string& word) {
        if (!isValidWord(word)) {
            return nullptr;
        }

        TSTNode* current = root;
        int index = 0;

        while (current != nullptr) {
            char character = word[index];

            if (character < current->character) {
                current = current->left;
            }
            else if (character > current->character) {
                current = current->right;
            }
            else {
                if (index + 1 == (int)word.length()) {
                    return current;
                }

                index++;
                current = current->equal;
            }
        }

        return nullptr;
    }

    void displayWords(TSTNode* current,
                      string& word) {

        if (current == nullptr) {
            return;
        }

        // Explore smaller characters first
        displayWords(current->left, word);

        // Add the current character
        word.push_back(current->character);

        if (current->isEndOfWord) {
            cout << word << "\n";
        }

        // Continue to the next character
        displayWords(current->equal, word);

        // Remove the current character
        word.pop_back();

        // Explore larger characters
        displayWords(current->right, word);
    }

    void deleteTrie(TSTNode* current) {
        if (current == nullptr) {
            return;
        }

        deleteTrie(current->left);
        deleteTrie(current->equal);
        deleteTrie(current->right);

        delete current;
    }

public:
    TernarySearchTrie() {
        root = nullptr;
        wordCount = 0;
        nodeCount = 0;
    }

    bool insert(const string& word) {
        if (!isValidWord(word)) {
            cout << "Invalid word. Use lowercase letters only.\n";
            return false;
        }

        TSTNode* existing = searchNode(word);

        if (existing != nullptr && existing->isEndOfWord) {
            cout << "Word already exists.\n";
            return false;
        }

        root = insertWord(root, word, 0);

        wordCount++;

        cout << "Word inserted successfully.\n";
        return true;
    }

    bool search(const string& word) {
        TSTNode* result = searchNode(word);

        return result != nullptr && result->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        return searchNode(prefix) != nullptr;
    }

    void displayAllWords() {
        if (wordCount == 0) {
            cout << "Ternary Search Trie is empty.\n";
            return;
        }

        string word;

        cout << "\nStored words:\n";

        displayWords(root, word);
    }

    int getWordCount() {
        return wordCount;
    }

    int getNodeCount() {
        return nodeCount;
    }

    ~TernarySearchTrie() {
        deleteTrie(root);
    }
};

int main() {
    TernarySearchTrie trie;

    int n;

    cout << "Enter number of initial words: ";

    if (!(cin >> n) || n < 0) {
        cout << "Invalid number of words.\n";
        return 1;
    }

    string word;

    cout << "Enter words (lowercase only):\n";

    for (int i = 0; i < n; i++) {
        if (!(cin >> word)) {
            cout << "Invalid input.\n";
            return 1;
        }

        trie.insert(word);
    }

    int operationCount;

    cout << "\nEnter number of operations: ";

    if (!(cin >> operationCount) || operationCount < 0) {
        cout << "Invalid number of operations.\n";
        return 1;
    }

    for (int i = 0; i < operationCount; i++) {
        int choice;

        cout << "\n1. Insert word\n";
        cout << "2. Search exact word\n";
        cout << "3. Search prefix\n";
        cout << "4. Display all words\n";
        cout << "5. Count words\n";
        cout << "6. Count nodes\n";

        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                trie.insert(word);
                break;

            case 2:
                cout << "Enter word to search: ";
                cin >> word;

                if (trie.search(word)) {
                    cout << "Word found.\n";
                }
                else {
                    cout << "Word not found.\n";
                }
                break;

            case 3:
                cout << "Enter prefix: ";
                cin >> word;

                if (trie.startsWith(word)) {
                    cout << "Prefix exists.\n";
                }
                else {
                    cout << "Prefix does not exist.\n";
                }
                break;

            case 4:
                trie.displayAllWords();
                break;

            case 5:
                cout << "Total distinct words: "
                     << trie.getWordCount() << "\n";
                break;

            case 6:
                cout << "Total Trie nodes: "
                     << trie.getNodeCount() << "\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
