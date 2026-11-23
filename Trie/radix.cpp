#include <iostream>
#include <map>
#include <string>
using namespace std;

struct RadixNode {
    string edgeLabel;
    bool isEndOfWord;
    map<char, RadixNode*> children;

    RadixNode(string label = "") {
        edgeLabel = label;
        isEndOfWord = false;
    }
};

class RadixTrie {
private:
    RadixNode* root;
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

    int findCommonPrefixLength(const string& first,
                               const string& second) {
        int length = 0;

        while (length < (int)first.length() &&
               length < (int)second.length() &&
               first[length] == second[length]) {
            length++;
        }

        return length;
    }

    bool insertWord(RadixNode* current,
                    const string& word) {

        char firstCharacter = word[0];

        auto it = current->children.find(firstCharacter);

        // No matching edge exists
        if (it == current->children.end()) {
            RadixNode* newNode = new RadixNode(word);

            newNode->isEndOfWord = true;

            current->children[firstCharacter] = newNode;

            nodeCount++;

            return true;
        }

        RadixNode* child = it->second;

        int commonLength = findCommonPrefixLength(
            child->edgeLabel,
            word
        );

        // The entire existing edge matches
        if (commonLength == (int)child->edgeLabel.length()) {

            // The new word ends at this node
            if (commonLength == (int)word.length()) {

                if (child->isEndOfWord) {
                    return false;
                }

                child->isEndOfWord = true;
                return true;
            }

            // Continue with the remaining suffix
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

        RadixNode* middleNode =
            new RadixNode(commonPart);

        nodeCount++;

        // Update the existing child edge
        child->edgeLabel = oldSuffix;

        // Attach the old branch to the middle node
        middleNode->children[oldSuffix[0]] = child;

        // Replace the old edge with the common prefix
        current->children[firstCharacter] = middleNode;

        // Mark the middle node if the new word ends here
        if (newSuffix.empty()) {
            middleNode->isEndOfWord = true;
        }
        else {
            RadixNode* newChild =
                new RadixNode(newSuffix);

            newChild->isEndOfWord = true;

            middleNode->children[newSuffix[0]] = newChild;

            nodeCount++;
        }

        return true;
    }

    bool searchWord(RadixNode* current,
                    const string& word) {

        auto it = current->children.find(word[0]);

        if (it == current->children.end()) {
            return false;
        }

        RadixNode* child = it->second;

        int commonLength = findCommonPrefixLength(
            child->edgeLabel,
            word
        );

        // The complete edge must match
        if (commonLength != (int)child->edgeLabel.length()) {
            return false;
        }

        // The complete word has been matched
        if (commonLength == (int)word.length()) {
            return child->isEndOfWord;
        }

        return searchWord(
            child,
            word.substr(commonLength)
        );
    }

    bool searchPrefix(RadixNode* current,
                      const string& prefix) {

        auto it = current->children.find(prefix[0]);

        if (it == current->children.end()) {
            return false;
        }

        RadixNode* child = it->second;

        int commonLength = findCommonPrefixLength(
            child->edgeLabel,
            prefix
        );

        // The entire requested prefix matches
        if (commonLength == (int)prefix.length()) {
            return true;
        }

        // The edge itself must match before continuing
        if (commonLength == (int)child->edgeLabel.length()) {
            return searchPrefix(
                child,
                prefix.substr(commonLength)
            );
        }

        return false;
    }

    void displayWords(RadixNode* current,
                      string& currentWord) {

        if (current->isEndOfWord) {
            cout << currentWord << "\n";
        }

        for (auto& entry : current->children) {
            RadixNode* child = entry.second;

            currentWord += child->edgeLabel;

            displayWords(child, currentWord);

            currentWord.erase(
                currentWord.length() - child->edgeLabel.length()
            );
        }
    }

    void displayStructure(RadixNode* current, int depth) {

        for (auto& entry : current->children) {
            RadixNode* child = entry.second;

            for (int i = 0; i < depth; i++) {
                cout << "  ";
            }

            cout << "|-- " << child->edgeLabel;

            if (child->isEndOfWord) {
                cout << " [END]";
            }

            cout << "\n";

            displayStructure(child, depth + 1);
        }
    }

    void deleteTrie(RadixNode* current) {
        if (current == nullptr) {
            return;
        }

        for (auto& entry : current->children) {
            deleteTrie(entry.second);
        }

        delete current;
    }

public:
    RadixTrie() {
        root = new RadixNode();

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
            cout << "Radix Trie is empty.\n";
            return;
        }

        string currentWord;

        cout << "\nStored words:\n";

        displayWords(root, currentWord);
    }

    void displayTrieStructure() {
        cout << "\nRadix Trie Structure:\n";
        cout << "Root\n";

        displayStructure(root, 1);
    }

    int getWordCount() {
        return wordCount;
    }

    int getNodeCount() {
        return nodeCount;
    }

    ~RadixTrie() {
        deleteTrie(root);
    }
};

int main() {
    RadixTrie trie;

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
        cout << "7. Display Trie structure\n";

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
                cout << "Total Radix Trie nodes: "
                     << trie.getNodeCount() << "\n";
                break;

            case 7:
                trie.displayTrieStructure();
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
