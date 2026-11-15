#include <iostream>
#include <vector>
#include <string>
using namespace std;

int rows, cols;

vector<vector<char>> grid;
vector<vector<bool>> visited;

string targetWord;

vector<pair<int, int>> currentPath;
vector<pair<int, int>> solutionPath;

long long recursiveCalls = 0;

// Four possible directions
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

string directions[] = {"Up", "Down", "Left", "Right"};

// Check whether a position is valid
bool isValid(int row, int col) {

    if (row < 0 || row >= rows ||
        col < 0 || col >= cols) {

        return false;
    }

    if (visited[row][col]) {
        return false;
    }

    return true;
}

// Recursive word search
bool searchWord(int row, int col, int index) {

    recursiveCalls++;

    // Check boundaries and visited cells
    if (!isValid(row, col)) {
        return false;
    }

    // Check whether the current character matches
    if (grid[row][col] != targetWord[index]) {
        return false;
    }

    // Mark current cell as visited
    visited[row][col] = true;

    currentPath.push_back({row, col});

    // Entire word has been matched
    if (index == (int)targetWord.length() - 1) {

        solutionPath = currentPath;

        currentPath.pop_back();
        visited[row][col] = false;

        return true;
    }

    // Explore all four directions
    for (int i = 0; i < 4; i++) {

        int newRow = row + dr[i];
        int newCol = col + dc[i];

        if (searchWord(newRow, newCol, index + 1)) {

            currentPath.pop_back();
            visited[row][col] = false;

            return true;
        }
    }

    // Backtrack
    currentPath.pop_back();
    visited[row][col] = false;

    return false;
}

// Search from every possible starting cell
bool findWord() {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            if (grid[i][j] == targetWord[0]) {

                if (searchWord(i, j, 0)) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Display the found path
void displayPath() {

    cout << "\n========== WORD PATH ==========\n";

    for (int i = 0; i < (int)solutionPath.size(); i++) {

        cout << "("
             << solutionPath[i].first
             << ", "
             << solutionPath[i].second
             << ")";

        if (i != (int)solutionPath.size() - 1) {
            cout << " -> ";
        }
    }

    cout << "\n\nCharacter-by-character path:\n";

    for (int i = 0; i < (int)solutionPath.size(); i++) {

        int r = solutionPath[i].first;
        int c = solutionPath[i].second;

        cout << grid[r][c];

        if (i != (int)solutionPath.size() - 1) {
            cout << " -> ";
        }
    }

    cout << endl;
}

// Display the original grid
void displayGrid() {

    cout << "\n========== CHARACTER GRID ==========\n";

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }

        cout << endl;
    }
}

int main() {

    cout << "===== WORD SEARCH USING BACKTRACKING =====\n";

    cout << "\nEnter number of rows: ";
    cin >> rows;

    cout << "Enter number of columns: ";
    cin >> cols;

    if (rows <= 0 || cols <= 0) {

        cout << "\nInvalid grid dimensions.\n";
        return 0;
    }

    if (rows > 100 || cols > 100) {

        cout << "\nGrid dimensions are too large.\n";
        return 0;
    }

    grid.resize(rows, vector<char>(cols));
    visited.resize(rows, vector<bool>(cols, false));

    cout << "\nEnter grid characters:\n";

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            cin >> grid[i][j];
        }
    }

    cout << "\nEnter word to search: ";
    cin >> targetWord;

    if (targetWord.empty()) {

        cout << "\nTarget word cannot be empty.\n";
        return 0;
    }

    if (targetWord.length() > (size_t)rows * cols) {

        cout << "\nWord cannot exist because it is longer than the number of cells.\n";
        return 0;
    }

    displayGrid();

    cout << "\nSearching for word: " << targetWord << endl;

    if (findWord()) {

        cout << "\nWord found successfully!\n";

        displayPath();

    } else {

        cout << "\nWord not found in the given grid.\n";
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
