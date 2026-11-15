#include <iostream>
#include <vector>
#include <string>
using namespace std;

int rows, cols;
int maxSolutions;

vector<vector<int>> maze;
vector<vector<bool>> visited;

vector<pair<int, int>> currentPath;
vector<vector<pair<int, int>>> solutions;

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

string directions[] = {"Down", "Right", "Up", "Left"};

bool searchMaze(int r, int c) {

    // Check boundaries
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        return false;
    }

    // Check blocked or already visited cells
    if (maze[r][c] == 0 || visited[r][c]) {
        return false;
    }

    // Mark current cell as visited
    visited[r][c] = true;
    currentPath.push_back({r, c});

    // Destination reached
    if (r == rows - 1 && c == cols - 1) {

        solutions.push_back(currentPath);

        currentPath.pop_back();
        visited[r][c] = false;

        // Stop if display limit is reached
        if ((int)solutions.size() >= maxSolutions) {
            return true;
        }

        return false;
    }

    // Explore all four directions
    for (int i = 0; i < 4; i++) {

        int newRow = r + dr[i];
        int newCol = c + dc[i];

        if (searchMaze(newRow, newCol)) {

            currentPath.pop_back();
            visited[r][c] = false;

            return true;
        }
    }

    // Backtrack
    currentPath.pop_back();
    visited[r][c] = false;

    return false;
}

void displaySolutions() {

    cout << "\n========== POSSIBLE PATHS ==========\n";

    for (int i = 0; i < (int)solutions.size(); i++) {

        cout << "\nPath " << i + 1 << ": ";

        for (int j = 0; j < (int)solutions[i].size(); j++) {

            cout << "("
                 << solutions[i][j].first
                 << ", "
                 << solutions[i][j].second
                 << ")";

            if (j != (int)solutions[i].size() - 1) {
                cout << " -> ";
            }
        }

        cout << endl;
    }

    cout << "\nTotal paths found: " << solutions.size() << endl;

    if ((int)solutions.size() >= maxSolutions) {
        cout << "Search stopped after reaching the path display limit."
             << endl;
        cout << "Additional paths, if any, were not explored." << endl;
    }
}

void displayFirstPath() {

    if (solutions.empty()) {
        return;
    }

    vector<vector<char>> result(rows, vector<char>(cols, '.'));

    // Mark blocked cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if (maze[i][j] == 0) {
                result[i][j] = '#';
            }
        }
    }

    // Mark the first valid path
    for (auto cell : solutions[0]) {

        result[cell.first][cell.second] = '*';
    }

    cout << "\n========== FIRST VALID PATH ==========\n";

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
            cout << result[i][j] << " ";
        }

        cout << endl;
    }

    cout << "\nLegend:\n";
    cout << "* = Path\n";
    cout << ". = Open cell not used in first path\n";
    cout << "# = Blocked cell\n";
}

int main() {

    cout << "===== RAT IN A MAZE =====\n";

    cout << "\nEnter number of rows: ";
    cin >> rows;

    cout << "Enter number of columns: ";
    cin >> cols;

    if (rows <= 0 || cols <= 0) {
        cout << "\nInvalid maze dimensions.\n";
        return 0;
    }

    maze.resize(rows, vector<int>(cols));
    visited.resize(rows, vector<bool>(cols, false));

    cout << "\nEnter maze values (0 = Blocked, 1 = Open):\n";

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            cin >> maze[i][j];

            if (maze[i][j] != 0 && maze[i][j] != 1) {
                cout << "\nInvalid cell value. Enter only 0 or 1.\n";
                return 0;
            }
        }
    }

    cout << "\nEnter maximum number of paths to display: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {
        cout << "\nPath display limit must be positive.\n";
        return 0;
    }

    // Check starting and destination cells
    if (maze[0][0] == 0) {
        cout << "\nStarting cell is blocked. No path exists.\n";
        return 0;
    }

    if (maze[rows - 1][cols - 1] == 0) {
        cout << "\nDestination cell is blocked. No path exists.\n";
        return 0;
    }

    // Find all possible paths up to the given limit
    searchMaze(0, 0);

    if (solutions.empty()) {

        cout << "\nNo valid path exists from source to destination.\n";
        return 0;
    }

    displaySolutions();
    displayFirstPath();

    return 0;
}
