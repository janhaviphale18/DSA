#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_EDIT_DISTANCE = 2;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class SpellChecker {
private:
    TrieNode* root;
    int wordCount;

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

    void findSuggestions(
        TrieNode* current,
        const string& target,
        const vector<int>& previousRow,
        string& currentWord,
        vector<string>& suggestions
    ) {
        if (current == nullptr) {
            return;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {

            if (current->children[i] == nullptr) {
                continue;
            }

            char character = char('a' + i);

            vector<int> currentRow(target.length() + 1);

            currentRow[0] = previousRow[0] + 1;

            int minimumDistance = currentRow[0];

            for (int j = 1; j <= (int)target.length(); j++) {

                int insertionCost = currentRow[j - 1] + 1;

                int deletionCost = previousRow[j] + 1;

                int substitutionCost =
                    previousRow[j - 1] +
                    (character == target[j - 1] ? 0 : 1);

                currentRow[j] = min({
                    insertionCost,
                    deletionCost,
                    substitutionCost
                });

                minimumDistance = min(
                    minimumDistance,
                    currentRow[j]
                );
            }

            currentWord.push_back(character);

            TrieNode* nextNode = current->children[i];

            if (nextNode->isEndOfWord &&
                currentRow[target.length()] <= MAX_EDIT_DISTANCE) {

                suggestions.push_back(currentWord);
            }

            // Continue only if this branch can still
            // produce a word within the allowed distance
            if (minimumDistance <= MAX_EDIT_DISTANCE) {

                findSuggestions(
                    nextNode,
                    target,
                    currentRow,
                    currentWord,
                    suggestions
                );
            }

            currentWord.pop_back();
        }
    }

    void displayWords(TrieNode* current, string& word) {
        if (current->isEndOfWord) {
            cout << word << "\n";
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (current->children[i] != nullptr) {

                word.push_back(char('a' + i));

                displayWords(current->children[i], word);

                word.pop_back();
            }
        }
    }

    void deleteTrie(TrieNode* current) {
        if (current == nullptr) {
            return;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            deleteTrie(current->children[i]);
        }

        delete current;
    }

public:
    SpellChecker() {
        root = new TrieNode();
        wordCount = 0;
    }

    bool insertWord(const string& word) {
        if (!isValidWord(word)) {
            cout << "Invalid word. Use lowercase letters only.\n";
            return false;
        }

        TrieNode* current = root;

        for (char character : word) {
            int index = character - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        if (current->isEndOfWord) {
            cout << "Word already exists in dictionary.\n";
            return false;
        }

        current->isEndOfWord = true;
        wordCount++;

        cout << "Word added to dictionary successfully.\n";
        return true;
    }

    bool searchWord(const string& word) {
        if (!isValidWord(word)) {
            return false;
        }

        TrieNode* current = root;

        for (char character : word) {
            int index = character - 'a';

            if (current->children[index] == nullptr) {
                return false;
            }

            current = current->children[index];
        }

        return current->isEndOfWord;
    }

    void checkSpelling(const string& word) {
        if (!isValidWord(word)) {
            cout << "Invalid word. Use lowercase letters only.\n";
            return;
        }

        if (searchWord(word)) {
            cout << "Correct spelling! Word exists in dictionary.\n";
            return;
        }

        cout << "Incorrect spelling: " << word << "\n";

        vector<int> initialRow(word.length() + 1);

        for (int i = 0; i <= (int)word.length(); i++) {
            initialRow[i] = i;
        }

        vector<string> suggestions;
        string currentWord;

        findSuggestions(
            root,
            word,
            initialRow,
            currentWord,
            suggestions
        );

        if (suggestions.empty()) {
            cout << "No suggestions found within edit distance "
                 << MAX_EDIT_DISTANCE << ".\n";
        }
        else {
            cout << "\nSuggested corrections:\n";

            for (const string& suggestion : suggestions) {
                cout << suggestion << "\n";
            }
        }
    }

    void displayDictionary() {
        if (wordCount == 0) {
            cout << "Dictionary is empty.\n";
            return;
        }

        string word;

        cout << "\nDictionary words:\n";

        displayWords(root, word);
    }

    int getWordCount() {
        return wordCount;
    }

    ~SpellChecker() {
        deleteTrie(root);
    }
};

int main() {
    SpellChecker checker;

    int n;

    cout << "Enter number of dictionary words: ";

    if (!(cin >> n) || n < 0) {
        cout << "Invalid dictionary size.\n";
        return 1;
    }

    string word;

    cout << "Enter dictionary words (lowercase only):\n";

    for (int i = 0; i < n; i++) {
        if (!(cin >> word)) {
            cout << "Invalid input.\n";
            return 1;
        }

        checker.insertWord(word);
    }

    int operationCount;

    cout << "\nEnter number of operations: ";

    if (!(cin >> operationCount) || operationCount < 0) {
        cout << "Invalid number of operations.\n";
        return 1;
    }

    for (int i = 0; i < operationCount; i++) {
        int choice;

        cout << "\n1. Add dictionary word\n";
        cout << "2. Check spelling\n";
        cout << "3. Search exact word\n";
        cout << "4. Display dictionary\n";
        cout << "5. Count dictionary words\n";

        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                cout << "Enter new word: ";
                cin >> word;

                checker.insertWord(word);
                break;

            case 2:
                cout << "Enter word to check: ";
                cin >> word;

                checker.checkSpelling(word);
                break;

            case 3:
                cout << "Enter word to search: ";
                cin >> word;

                if (checker.searchWord(word)) {
                    cout << "Word exists in dictionary.\n";
                }
                else {
                    cout << "Word does not exist.\n";
                }
                break;

            case 4:
                checker.displayDictionary();
                break;

            case 5:
                cout << "Total dictionary words: "
                     << checker.getWordCount() << "\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
