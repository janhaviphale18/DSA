#include <iostream>
#include <vector>
using namespace std;

int n;
long long maxSolutions;

vector<vector<int>> board;
vector<vector<vector<int>>> solutions;

long long recursiveCalls = 0;
bool limitReached = false;

// Check whether a queen can be placed safely
bool isSafe(int row, int col) {

    // Check the same column in previous rows
    for (int i = 0; i < row; i++) {

        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0;
         i--, j--) {

        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n;
         i--, j++) {

        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Recursive function to place queens
void solveNQueens(int row) {

    recursiveCalls++;

    // Stop if solution limit has been reached
    if ((long long)solutions.size() >= maxSolutions) {
        limitReached = true;
        return;
    }

    // All queens have been placed
    if (row == n) {

        solutions.push_back(board);
        return;
    }

    // Try every column in the current row
    for (int col = 0; col < n; col++) {

        if (isSafe(row, col)) {

            // Place queen
            board[row][col] = 1;

            // Explore next row
            solveNQueens(row + 1);

            // Backtrack
            board[row][col] = 0;

            // Stop if the solution limit is reached
            if (limitReached) {
                return;
            }
        }
    }
}

// Display all stored solutions
void displaySolutions() {

    cout << "\n========== N-QUEENS SOLUTIONS ==========\n";

    for (int s = 0; s < (int)solutions.size(); s++) {

        cout << "\nSolution " << s + 1 << ":\n";

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (solutions[s][i][j] == 1) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }

            cout << endl;
        }
    }

    cout << "\nTotal solutions found: "
         << solutions.size() << endl;

    if (limitReached) {
        cout << "Search stopped after reaching the solution limit.\n";
        cout << "Additional solutions, if any, were not explored.\n";
    }
}

int main() {

    cout << "===== N-QUEENS USING BACKTRACKING =====\n";

    cout << "\nEnter number of queens (N): ";
    cin >> n;

    if (n <= 0) {
        cout << "\nInvalid board size.\n";
        return 0;
    }

    if (n > 12) {
        cout << "\nBoard size is too large for this basic implementation.\n";
        cout << "Please enter N between 1 and 12.\n";
        return 0;
    }

    cout << "\nEnter maximum number of solutions to display: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {
        cout << "\nSolution limit must be positive.\n";
        return 0;
    }

    // Initialize empty chessboard
    board.resize(n, vector<int>(n, 0));

    // Start placing queens from row 0
    solveNQueens(0);

    if (solutions.empty()) {

        cout << "\nNo valid arrangement exists for N = "
             << n << ".\n";

    } else {

        displaySolutions();
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
