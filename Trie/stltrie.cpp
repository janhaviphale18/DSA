#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

// Trie implementation using unordered_map
struct UnorderedNode {
    unordered_map<char, UnorderedNode*> children;
    bool isEndOfWord;

    UnorderedNode() {
        isEndOfWord = false;
    }
};

class UnorderedTrie {
private:
    UnorderedNode* root;
    int wordCount;
    int nodeCount;

    void displayWords(UnorderedNode* current, string& word) {
        if (current->isEndOfWord) {
            cout << word << "\n";
        }

        for (auto& entry : current->children) {
            word.push_back(entry.first);

            displayWords(entry.second, word);

            word.pop_back();
        }
    }

    void deleteTrie(UnorderedNode* current) {
        if (current == nullptr) {
            return;
        }

        for (auto& entry : current->children) {
            deleteTrie(entry.second);
        }

        delete current;
    }

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

public:
    UnorderedTrie() {
        root = new UnorderedNode();
        wordCount = 0;
        nodeCount = 1;
    }

    bool insertWord(const string& word) {
        if (!isValidWord(word)) {
            cout << "Invalid word. Use lowercase letters only.\n";
            return false;
        }

        UnorderedNode* current = root;

        for (char character : word) {
            if (current->children.find(character) ==
                current->children.end()) {

                current->children[character] = new UnorderedNode();
                nodeCount++;
            }

            current = current->children[character];
        }

        if (current->isEndOfWord) {
            cout << "Word already exists.\n";
            return false;
        }

        current->isEndOfWord = true;
        wordCount++;

        cout << "Word inserted successfully.\n";
        return true;
    }

    bool searchWord(const string& word) {
        if (!isValidWord(word)) {
            return false;
        }

        UnorderedNode* current = root;

        for (char character : word) {
            auto it = current->children.find(character);

            if (it == current->children.end()) {
                return false;
            }

            current = it->second;
        }

        return current->isEndOfWord;
    }

    bool searchPrefix(const string& prefix) {
        if (!isValidWord(prefix)) {
            return false;
        }

        UnorderedNode* current = root;

        for (char character : prefix) {
            auto it = current->children.find(character);

            if (it == current->children.end()) {
                return false;
            }

            current = it->second;
        }

        return true;
    }

    void displayAllWords() {
        if (wordCount == 0) {
            cout << "Trie is empty.\n";
            return;
        }

        string word;

        cout << "\nWords in Unordered Trie:\n";
        displayWords(root, word);
    }

    int getWordCount() {
        return wordCount;
    }

    int getNodeCount() {
        return nodeCount;
    }

    ~UnorderedTrie() {
        deleteTrie(root);
    }
};

// Trie implementation using map
struct OrderedNode {
    map<char, OrderedNode*> children;
    bool isEndOfWord;

    OrderedNode() {
        isEndOfWord = false;
    }
};

class OrderedTrie {
private:
    OrderedNode* root;
    int wordCount;
    int nodeCount;

    void displayWords(OrderedNode* current, string& word) {
        if (current->isEndOfWord) {
            cout << word << "\n";
        }

        for (auto& entry : current->children) {
            word.push_back(entry.first);

            displayWords(entry.second, word);

            word.pop_back();
        }
    }

    void deleteTrie(OrderedNode* current) {
        if (current == nullptr) {
            return;
        }

        for (auto& entry : current->children) {
            deleteTrie(entry.second);
        }

        delete current;
    }

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

public:
    OrderedTrie() {
        root = new OrderedNode();
        wordCount = 0;
        nodeCount = 1;
    }

    bool insertWord(const string& word) {
        if (!isValidWord(word)) {
            cout << "Invalid word. Use lowercase letters only.\n";
            return false;
        }

        OrderedNode* current = root;

        for (char character : word) {
            if (current->children.find(character) ==
                current->children.end()) {

                current->children[character] = new OrderedNode();
                nodeCount++;
            }

            current = current->children[character];
        }

        if (current->isEndOfWord) {
            cout << "Word already exists.\n";
            return false;
        }

        current->isEndOfWord = true;
        wordCount++;

        cout << "Word inserted successfully.\n";
        return true;
    }

    bool searchWord(const string& word) {
        if (!isValidWord(word)) {
            return false;
        }

        OrderedNode* current = root;

        for (char character : word) {
            auto it = current->children.find(character);

            if (it == current->children.end()) {
                return false;
            }

            current = it->second;
        }

        return current->isEndOfWord;
    }

    bool searchPrefix(const string& prefix) {
        if (!isValidWord(prefix)) {
            return false;
        }

        OrderedNode* current = root;

        for (char character : prefix) {
            auto it = current->children.find(character);

            if (it == current->children.end()) {
                return false;
            }

            current = it->second;
        }

        return true;
    }

    void displayAllWords() {
        if (wordCount == 0) {
            cout << "Trie is empty.\n";
            return;
        }

        string word;

        cout << "\nWords in Ordered Trie:\n";
        displayWords(root, word);
    }

    int getWordCount() {
        return wordCount;
    }

    int getNodeCount() {
        return nodeCount;
    }

    ~OrderedTrie() {
        deleteTrie(root);
    }
};

int main() {
    UnorderedTrie unorderedTrie;
    OrderedTrie orderedTrie;

    int n;

    cout << "Enter number of words: ";

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

        unorderedTrie.insertWord(word);
        orderedTrie.insertWord(word);
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
        cout << "2. Search word\n";
        cout << "3. Search prefix\n";
        cout << "4. Display unordered Trie\n";
        cout << "5. Display ordered Trie\n";
        cout << "6. Compare statistics\n";

        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;

                unorderedTrie.insertWord(word);
                orderedTrie.insertWord(word);
                break;

            case 2:
                cout << "Enter word to search: ";
                cin >> word;

                if (unorderedTrie.searchWord(word)) {
                    cout << "Word found in both Tries.\n";
                }
                else {
                    cout << "Word not found.\n";
                }
                break;

            case 3:
                cout << "Enter prefix: ";
                cin >> word;

                if (unorderedTrie.searchPrefix(word)) {
                    cout << "Prefix exists in both Tries.\n";
                }
                else {
                    cout << "Prefix does not exist.\n";
                }
                break;

            case 4:
                unorderedTrie.displayAllWords();
                break;

            case 5:
                orderedTrie.displayAllWords();
                break;

            case 6:
                cout << "\nUnordered Trie:\n";
                cout << "Words: "
                     << unorderedTrie.getWordCount() << "\n";
                cout << "Nodes: "
                     << unorderedTrie.getNodeCount() << "\n";

                cout << "\nOrdered Trie:\n";
                cout << "Words: "
                     << orderedTrie.getWordCount() << "\n";
                cout << "Nodes: "
                     << orderedTrie.getNodeCount() << "\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
