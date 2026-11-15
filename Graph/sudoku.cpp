#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 9;

vector<vector<int>> board(SIZE, vector<int>(SIZE));

long long recursiveCalls = 0;

// Check whether a number can be placed safely
bool isSafe(int row, int col, int num) {

    // Check the current row
    for (int j = 0; j < SIZE; j++) {

        if (board[row][j] == num) {
            return false;
        }
    }

    // Check the current column
    for (int i = 0; i < SIZE; i++) {

        if (board[i][col] == num) {
            return false;
        }
    }

    // Find the starting position of the 3x3 subgrid
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    // Check the 3x3 subgrid
    for (int i = startRow; i < startRow + 3; i++) {

        for (int j = startCol; j < startCol + 3; j++) {

            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Find the next empty cell
bool findEmptyCell(int &row, int &col) {

    for (row = 0; row < SIZE; row++) {

        for (col = 0; col < SIZE; col++) {

            if (board[row][col] == 0) {
                return true;
            }
        }
    }

    return false;
}

// Recursive Sudoku solver
bool solveSudoku() {

    recursiveCalls++;

    int row, col;

    // No empty cells means puzzle is solved
    if (!findEmptyCell(row, col)) {
        return true;
    }

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {

        if (isSafe(row, col, num)) {

            // Place the number
            board[row][col] = num;

            // Recursively solve the remaining puzzle
            if (solveSudoku()) {
                return true;
            }

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

// Validate the initial Sudoku board
bool validateInitialBoard() {

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            int num = board[i][j];

            if (num < 0 || num > 9) {
                return false;
            }

            if (num != 0) {

                board[i][j] = 0;

                if (!isSafe(i, j, num)) {
                    board[i][j] = num;
                    return false;
                }

                board[i][j] = num;
            }
        }
    }

    return true;
}

// Display the Sudoku board
void displayBoard() {

    cout << "\n";

    for (int i = 0; i < SIZE; i++) {

        if (i % 3 == 0) {
            cout << "+-------+-------+-------+\n";
        }

        for (int j = 0; j < SIZE; j++) {

            if (j % 3 == 0) {
                cout << "| ";
            }

            cout << board[i][j] << " ";
        }

        cout << "|\n";
    }

    cout << "+-------+-------+-------+\n";
}

int main() {

    cout << "===== SUDOKU SOLVER USING BACKTRACKING =====\n";

    cout << "\nEnter the Sudoku board:\n";
    cout << "Use 0 for empty cells.\n\n";

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            cin >> board[i][j];
        }
    }

    // Validate input values and initial board
    if (!validateInitialBoard()) {

        cout << "\nInvalid Sudoku board.\n";
        cout << "Duplicate or out-of-range values detected.\n";

        return 0;
    }

    cout << "\n========== ORIGINAL SUDOKU ==========\n";

    displayBoard();

    cout << "\nSolving Sudoku...\n";

    if (solveSudoku()) {

        cout << "\nSudoku solved successfully!\n";

        cout << "\n========== SOLVED SUDOKU ==========\n";

        displayBoard();

    } else {

        cout << "\nNo valid solution exists for the given Sudoku.\n";
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
