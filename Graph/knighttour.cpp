#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int n;

vector<vector<int>> board;

// Eight possible knight moves
int rowMove[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int colMove[] = {1, 2, 2, 1, -1, -2, -2, -1};

long long nodesExplored = 0;

bool isSafe(int row, int col) {

    // Check board boundaries
    if (row < 0 || row >= n || col < 0 || col >= n) {
        return false;
    }

    // Check whether the cell is already visited
    if (board[row][col] != -1) {
        return false;
    }

    return true;
}

bool solveKnightTour(int row, int col, int moveNumber) {

    nodesExplored++;

    // All squares have been visited
    if (moveNumber == n * n) {
        return true;
    }

    // Try all eight possible knight moves
    for (int i = 0; i < 8; i++) {

        int nextRow = row + rowMove[i];
        int nextCol = col + colMove[i];

        if (isSafe(nextRow, nextCol)) {

            // Make the move
            board[nextRow][nextCol] = moveNumber;

            // Recursively explore the next position
            if (solveKnightTour(nextRow, nextCol, moveNumber + 1)) {
                return true;
            }

            // Backtrack if the move does not lead to a solution
            board[nextRow][nextCol] = -1;
        }
    }

    return false;
}

void displayBoard() {

    cout << "\n========== KNIGHT'S TOUR ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cout << setw(4) << board[i][j];
        }

        cout << endl;
    }
}

int main() {

    cout << "===== KNIGHT'S TOUR USING BACKTRACKING =====\n";

    cout << "\nEnter chessboard size N: ";
    cin >> n;

    if (n <= 0) {
        cout << "\nInvalid chessboard size.\n";
        return 0;
    }

    if (n > 8) {
        cout << "\nBoard size is too large for this basic backtracking implementation.\n";
        cout << "Please enter a value between 1 and 8.\n";
        return 0;
    }

    board.resize(n, vector<int>(n, -1));

    int startRow, startCol;

    cout << "\nEnter starting row (0 to " << n - 1 << "): ";
    cin >> startRow;

    cout << "Enter starting column (0 to " << n - 1 << "): ";
    cin >> startCol;

    if (startRow < 0 || startRow >= n ||
        startCol < 0 || startCol >= n) {

        cout << "\nInvalid starting position.\n";
        return 0;
    }

    // Mark the starting position as move 0
    board[startRow][startCol] = 0;

    cout << "\nSearching for a valid Knight's Tour...\n";

    if (solveKnightTour(startRow, startCol, 1)) {

        cout << "\nKnight's Tour exists!\n";

        displayBoard();

    } else {

        cout << "\nNo Knight's Tour was found.\n";
    }

    cout << "\nTotal recursive calls: " << nodesExplored << endl;

    return 0;
}
