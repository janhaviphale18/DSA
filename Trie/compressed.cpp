#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct CompressedNode {
    string edgeLabel;
    bool isEndOfWord;
    vector<CompressedNode*> children;

    CompressedNode(string label = "") {
        edgeLabel = label;
        isEndOfWord = false;
    }
};

class CompressedTrie {
private:
    CompressedNode* root;
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

    int commonPrefixLength(const string& first,
                           const string& second) {
        int i = 0;

        while (i < (int)first.length() &&
               i < (int)second.length() &&
               first[i] == second[i]) {
            i++;
        }

        return i;
    }

    bool insertWord(CompressedNode* current,
                    const string& word) {

        for (int i = 0; i < (int)current->children.size(); i++) {
            CompressedNode* child = current->children[i];

            int commonLength =
                commonPrefixLength(child->edgeLabel, word);

            if (commonLength == 0) {
                continue;
            }

            // Entire existing edge matches
            if (commonLength == (int)child->edgeLabel.length()) {

                // Entire new word is already represented
                if (commonLength == (int)word.length()) {
                    if (child->isEndOfWord) {
                        return false;
                    }

                    child->isEndOfWord = true;
                    return true;
                }

                // Continue inserting the remaining suffix
                return insertWord(
                    child,
                    word.substr(commonLength)
                );
            }

            // Split the existing edge
            string commonPart =
                child->edgeLabel.substr(0, commonLength);

            string oldSuffix =
                child->edgeLabel.substr(commonLength);

            string newSuffix =
                word.substr(commonLength);

            CompressedNode* middle =
                new CompressedNode(commonPart);

            nodeCount++;

            child->edgeLabel = oldSuffix;

            middle->children.push_back(child);

            current->children[i] = middle;

            // The new word ends at the middle node
            if (newSuffix.empty()) {
                middle->isEndOfWord = true;
            }
            else {
                CompressedNode* newChild =
                    new CompressedNode(newSuffix);

                newChild->isEndOfWord = true;

                middle->children.push_back(newChild);
                nodeCount++;
            }

            return true;
        }

        // No existing edge shares a prefix
        CompressedNode* newChild =
            new CompressedNode(word);

        newChild->isEndOfWord = true;

        current->children.push_back(newChild);
        nodeCount++;

        return true;
    }

    bool searchWord(CompressedNode* current,
                    const string& word) {

        for (CompressedNode* child : current->children) {
            int commonLength =
                commonPrefixLength(child->edgeLabel, word);

            if (commonLength == (int)child->edgeLabel.length()) {

                if (commonLength == (int)word.length()) {
                    return child->isEndOfWord;
                }

                return searchWord(
                    child,
                    word.substr(commonLength)
                );
            }
        }

        return false;
    }

    bool searchPrefix(CompressedNode* current,
                      const string& prefix) {

        for (CompressedNode* child : current->children) {
            int commonLength =
                commonPrefixLength(child->edgeLabel, prefix);

            if (commonLength == (int)prefix.length()) {
                return true;
            }

            if (commonLength == (int)child->edgeLabel.length()) {
                return searchPrefix(
                    child,
                    prefix.substr(commonLength)
                );
            }
        }

        return false;
    }

    void displayWords(CompressedNode* current,
                      string& currentWord) {

        if (current->isEndOfWord) {
            cout << currentWord << "\n";
        }

        for (CompressedNode* child : current->children) {
            currentWord += child->edgeLabel;

            displayWords(child, currentWord);

            currentWord.erase(
                currentWord.length() - child->edgeLabel.length()
            );
        }
    }

    void deleteTrie(CompressedNode* current) {
        if (current == nullptr) {
            return;
        }

        for (CompressedNode* child : current->children) {
            deleteTrie(child);
        }

        delete current;
    }

public:
    CompressedTrie() {
        root = new CompressedNode();
        wordCount = 0;
        nodeCount = 1;
    }

    bool insert(const string& word) {
        if (!isValidWord(word)) {
            cout << "Invalid word. Use lowercase letters only.\n";
            return false;
        }

        bool inserted = insertWord(root, word);

        if (inserted) {
            wordCount++;
            cout << "Word inserted successfully.\n";
        }
        else {
            cout << "Word already exists.\n";
        }

        return inserted;
    }

    bool search(const string& word) {
        if (!isValidWord(word)) {
            return false;
        }

        return searchWord(root, word);
    }

    bool startsWith(const string& prefix) {
        if (!isValidWord(prefix)) {
            return false;
        }

        return searchPrefix(root, prefix);
    }

    void displayAllWords() {
        if (wordCount == 0) {
            cout << "Compressed Trie is empty.\n";
            return;
        }

        string currentWord;

        cout << "\nStored words:\n";
        displayWords(root, currentWord);
    }

    int getWordCount() {
        return wordCount;
    }

    int getNodeCount() {
        return nodeCount;
    }

    ~CompressedTrie() {
        deleteTrie(root);
    }
};

int main() {
    CompressedTrie trie;

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
        cout << "2. Search word\n";
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
                cout << "Total compressed Trie nodes: "
                     << trie.getNodeCount() << "\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
