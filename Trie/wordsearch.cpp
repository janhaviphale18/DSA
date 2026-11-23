#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    string word;

    TrieNode() {
        word = "";

        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class WordSearch {
private:
    TrieNode* root;

    int rows;
    int columns;

    vector<string> result;

    int rowDirection[4] = {-1, 1, 0, 0};
    int columnDirection[4] = {0, 0, -1, 1};

    void insertWord(const string& word) {
        TrieNode* current = root;

        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->word = word;
    }

    void dfs(
        vector<vector<char>>& board,
        int row,
        int column,
        TrieNode* parent
    ) {
        char currentCharacter = board[row][column];

        if (currentCharacter == '#') {
            return;
        }

        int index = currentCharacter - 'a';

        TrieNode* currentNode = parent->children[index];

        if (currentNode == nullptr) {
            return;
        }

        if (!currentNode->word.empty()) {
            result.push_back(currentNode->word);

            // Prevent the same word from being added again.
            currentNode->word = "";
        }

        // Mark the current cell as visited.
        board[row][column] = '#';

        // Explore all four directions.
        for (int direction = 0; direction < 4; direction++) {
            int newRow = row + rowDirection[direction];
            int newColumn = column + columnDirection[direction];

            if (newRow >= 0 && newRow < rows &&
                newColumn >= 0 && newColumn < columns &&
                board[newRow][newColumn] != '#') {

                dfs(
                    board,
                    newRow,
                    newColumn,
                    currentNode
                );
            }
        }

        // Restore the original character.
        board[row][column] = currentCharacter;
    }

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 26; i++) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

public:
    WordSearch() {
        root = new TrieNode();

        rows = 0;
        columns = 0;
    }

    vector<string> findWords(
        vector<vector<char>>& board,
        const vector<string>& words
    ) {
        result.clear();

        rows = board.size();

        if (rows == 0) {
            return result;
        }

        columns = board[0].size();

        if (columns == 0) {
            return result;
        }

        // Build the Trie using all dictionary words.
        for (int i = 0; i < words.size(); i++) {
            insertWord(words[i]);
        }

        // Start DFS from every board cell.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                dfs(board, i, j, root);
            }
        }

        return result;
    }

    ~WordSearch() {
        deleteTrie(root);
    }
};

int main() {
    int rows, columns;

    cout << "Enter number of rows and columns: ";
    cin >> rows >> columns;

    if (rows <= 0 || columns <= 0) {
        cout << "Invalid board dimensions." << endl;
        return 0;
    }

    vector<vector<char>> board(
        rows,
        vector<char>(columns)
    );

    cout << "\nEnter board rows (lowercase letters only):\n";

    for (int i = 0; i < rows; i++) {
        string row;

        cin >> row;

        if (row.length() != columns) {
            cout << "Invalid row length." << endl;
            return 0;
        }

        for (int j = 0; j < columns; j++) {
            if (row[j] < 'a' || row[j] > 'z') {
                cout << "Invalid board character." << endl;
                return 0;
            }

            board[i][j] = row[j];
        }
    }

    int numberOfWords;

    cout << "\nEnter number of words to search: ";
    cin >> numberOfWords;

    if (numberOfWords < 0) {
        cout << "Invalid number of words." << endl;
        return 0;
    }

    vector<string> words;

    cout << "\nEnter dictionary words:\n";

    for (int i = 0; i < numberOfWords; i++) {
        string word;

        cin >> word;

        bool valid = !word.empty();

        for (int j = 0; j < word.length(); j++) {
            if (word[j] < 'a' || word[j] > 'z') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid word. Use lowercase letters only.\n";
            i--;
            continue;
        }

        words.push_back(word);
    }

    WordSearch search;

    vector<string> foundWords = search.findWords(board, words);

    cout << "\nWords found in the board:\n";

    if (foundWords.empty()) {
        cout << "No matching words found." << endl;
    } else {
        for (int i = 0; i < foundWords.size(); i++) {
            cout << foundWords[i] << endl;
        }
    }

    cout << "\nTotal words found: " << foundWords.size() << endl;

    return 0;
}
