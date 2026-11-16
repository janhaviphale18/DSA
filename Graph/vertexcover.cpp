#include <iostream>
#include <vector>
using namespace std;

int n;
int m;

long long maxSolutions;

vector<pair<int, int>> edges;

vector<bool> selected;

vector<int> currentCover;

vector<vector<int>> minimumCovers;

int minimumSize = -1;

long long totalMinimumCovers = 0;

long long recursiveCalls = 0;

bool storageLimitReached = false;

// Check whether every edge is covered
bool isVertexCover() {

    for (int i = 0; i < m; i++) {

        int u = edges[i].first;
        int v = edges[i].second;

        if (!selected[u] && !selected[v]) {
            return false;
        }
    }

    return true;
}

// Check whether an uncovered edge has become impossible to cover
bool isImpossible(int processedCount) {

    for (int i = 0; i < m; i++) {

        int u = edges[i].first;
        int v = edges[i].second;

        // Both endpoints have already been processed
        if (u < processedCount && v < processedCount) {

            // Neither endpoint was selected
            if (!selected[u] && !selected[v]) {
                return true;
            }
        }
    }

    return false;
}

// Store a minimum vertex cover
void storeCover() {

    totalMinimumCovers++;

    if ((long long)minimumCovers.size() < maxSolutions) {

        minimumCovers.push_back(currentCover);

    } else {

        storageLimitReached = true;
    }
}

// Recursive backtracking
void findMinimumVertexCover(int index) {

    recursiveCalls++;

    // Prune if the current cover is already too large
    if (minimumSize != -1 &&
        (int)currentCover.size() > minimumSize) {

        return;
    }

    // Prune if an edge can no longer be covered
    if (isImpossible(index)) {
        return;
    }

    // All vertices have been processed
    if (index == n) {

        if (!isVertexCover()) {
            return;
        }

        int currentSize = (int)currentCover.size();

        // A smaller vertex cover has been found
        if (minimumSize == -1 ||
            currentSize < minimumSize) {

            minimumSize = currentSize;

            minimumCovers.clear();

            totalMinimumCovers = 0;

            storageLimitReached = false;

            storeCover();
        }

        // Another minimum vertex cover
        else if (currentSize == minimumSize) {

            storeCover();
        }

        return;
    }

    // Option 1: Do not select the current vertex
    selected[index] = false;

    findMinimumVertexCover(index + 1);

    // Option 2: Select the current vertex
    selected[index] = true;

    currentCover.push_back(index);

    findMinimumVertexCover(index + 1);

    // Backtracking
    currentCover.pop_back();

    selected[index] = false;
}

// Display graph edges
void displayGraph() {

    cout << "\n========== GRAPH EDGES ==========\n";

    if (edges.empty()) {

        cout << "The graph has no edges.\n";

        return;
    }

    for (int i = 0; i < m; i++) {

        cout << "("
             << edges[i].first
             << ", "
             << edges[i].second
             << ")";

        if (i != m - 1) {
            cout << ", ";
        }
    }

    cout << endl;
}

// Display one vertex cover
void displayCover(const vector<int>& cover) {

    cout << "{ ";

    for (int i = 0; i < (int)cover.size(); i++) {

        cout << cover[i];

        if (i != (int)cover.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display final results
void displayResults() {

    cout << "\n========== MINIMUM VERTEX COVER RESULTS ==========\n";

    cout << "\nMinimum vertex cover size: "
         << minimumSize << endl;

    cout << "\nStored minimum vertex covers:\n";

    for (int i = 0;
         i < (int)minimumCovers.size();
         i++) {

        cout << "\nCover " << i + 1 << ": ";

        displayCover(minimumCovers[i]);

        cout << endl;
    }

    cout << "\nTotal minimum vertex covers found: "
         << totalMinimumCovers << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional minimum vertex covers were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== MINIMUM VERTEX COVER =====\n";

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

    edges.reserve(m);

    selected.assign(n, false);

    cout << "\nEnter edges using vertex numbers 0 to "
         << n - 1 << ":\n";

    vector<vector<bool>> adj(
        n, vector<bool>(n, false)
    );

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

        // Store the undirected edge
        adj[u][v] = true;
        adj[v][u] = true;

        edges.push_back({u, v});
    }

    cout << "\nEnter maximum minimum covers to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    cout << "\nSearching for minimum vertex cover...\n";

    findMinimumVertexCover(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
