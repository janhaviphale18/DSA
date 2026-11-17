#include <iostream>
#include <vector>
using namespace std;

int n;
int m;

long long maxSolutions;

vector<vector<bool>> adj;

vector<bool> removed;
vector<bool> visited;

vector<int> currentSet;
vector<vector<int>> minimumSets;

int minimumSize = -1;

long long totalMinimumSets = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// DFS cycle detection
bool hasCycleDFS(int vertex, int parent) {

    visited[vertex] = true;

    for (int neighbor = 0; neighbor < n; neighbor++) {

        // Skip removed vertices and nonexistent edges
        if (removed[neighbor] || !adj[vertex][neighbor]) {
            continue;
        }

        // Visit an unvisited neighbor
        if (!visited[neighbor]) {

            if (hasCycleDFS(neighbor, vertex)) {
                return true;
            }
        }

        // A visited neighbor other than the parent
        // indicates a cycle
        else if (neighbor != parent) {

            return true;
        }
    }

    return false;
}

// Check whether the remaining graph contains a cycle
bool hasCycle() {

    visited.assign(n, false);

    for (int i = 0; i < n; i++) {

        // Ignore removed and already visited vertices
        if (removed[i] || visited[i]) {
            continue;
        }

        if (hasCycleDFS(i, -1)) {
            return true;
        }
    }

    return false;
}

// Store a minimum feedback vertex set
void storeSolution() {

    totalMinimumSets++;

    if ((long long)minimumSets.size() < maxSolutions) {

        minimumSets.push_back(currentSet);

    } else {

        storageLimitReached = true;
    }
}

// Recursive backtracking
void findMinimumFeedbackSet(int index) {

    recursiveCalls++;

    // If the remaining graph is acyclic,
    // the current selection is a valid solution
    if (!hasCycle()) {

        int currentSize = (int)currentSet.size();

        // A smaller solution has been found
        if (minimumSize == -1 ||
            currentSize < minimumSize) {

            minimumSize = currentSize;

            minimumSets.clear();

            totalMinimumSets = 0;

            storageLimitReached = false;

            storeSolution();
        }

        // Another minimum solution is found
        else if (currentSize == minimumSize) {

            storeSolution();
        }

        return;
    }

    // All vertices have been processed
    if (index == n) {
        return;
    }

    // Current solution cannot improve the minimum
    if (minimumSize != -1 &&
        (int)currentSet.size() >= minimumSize) {

        return;
    }

    // Option 1: Do not remove the current vertex
    findMinimumFeedbackSet(index + 1);

    // Option 2: Remove the current vertex
    removed[index] = true;

    currentSet.push_back(index);

    findMinimumFeedbackSet(index + 1);

    // Backtracking
    currentSet.pop_back();

    removed[index] = false;
}

// Display graph edges
void displayGraph() {

    cout << "\n========== GRAPH EDGES ==========\n";

    if (m == 0) {

        cout << "The graph has no edges.\n";

        return;
    }

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (adj[i][j]) {

                cout << "(" << i << ", " << j << ") ";

            }
        }
    }

    cout << endl;
}

// Display the remaining graph
void displayRemainingGraph() {

    cout << "\nRemaining vertices: ";

    bool first = true;

    for (int i = 0; i < n; i++) {

        if (!removed[i]) {

            if (!first) {
                cout << ", ";
            }

            cout << i;

            first = false;
        }
    }

    if (first) {
        cout << "None";
    }

    cout << endl;
}

// Display one feedback vertex set
void displaySet(const vector<int>& solution) {

    cout << "{ ";

    for (int i = 0; i < (int)solution.size(); i++) {

        cout << solution[i];

        if (i != (int)solution.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display final results
void displayResults() {

    cout << "\n========== FEEDBACK VERTEX SET RESULTS ==========\n";

    cout << "\nMinimum feedback vertex set size: "
         << minimumSize << endl;

    cout << "\nStored minimum feedback vertex sets:\n";

    for (int i = 0;
         i < (int)minimumSets.size();
         i++) {

        cout << "\nSet " << i + 1 << ": ";

        displaySet(minimumSets[i]);

        cout << endl;
    }

    cout << "\nTotal minimum feedback vertex sets found: "
         << totalMinimumSets << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional optimal solutions were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== MINIMUM FEEDBACK VERTEX SET =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 20) {

        cout << "\nNumber of vertices must be between 1 and 20.\n";

        return 0;
    }

    cout << "\nEnter number of edges: ";
    cin >> m;

    if (m < 0 || m > n * (n - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return 0;
    }

    adj.assign(n, vector<bool>(n, false));

    removed.assign(n, false);

    cout << "\nEnter undirected edges using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {

        int u, v;

        cout << "Edge " << i + 1 << ": ";

        cin >> u >> v;

        // Validate vertices
        if (u < 0 || u >= n ||
            v < 0 || v >= n) {

            cout << "\nInvalid vertex number.\n";

            return 0;
        }

        // Self-loops are not allowed
        if (u == v) {

            cout << "\nSelf-loops are not allowed.\n";

            return 0;
        }

        // Duplicate edges are not allowed
        if (adj[u][v]) {

            cout << "\nDuplicate edge detected.\n";

            return 0;
        }

        // Insert undirected edge
        adj[u][v] = true;
        adj[v][u] = true;
    }

    cout << "\nEnter maximum minimum sets to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    cout << "\nSearching for minimum feedback vertex set...\n";

    findMinimumFeedbackSet(0);

    displayResults();

    displayRemainingGraph();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
