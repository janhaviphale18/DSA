#include <iostream>
#include <vector>
using namespace std;

int n;
int m;

long long maxSolutions;

vector<pair<int, int>> edges;

vector<int> coverageCount;

vector<int> currentCover;

vector<vector<int>> minimumCovers;

int minimumSize = -1;

long long totalMinimumCovers = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// Check whether every vertex is covered
bool isFullyCovered() {

    for (int i = 0; i < n; i++) {

        if (coverageCount[i] == 0) {
            return false;
        }
    }

    return true;
}

// Check whether every uncovered vertex
// can still be covered by the remaining edges
bool canStillCover(int index) {

    for (int vertex = 0; vertex < n; vertex++) {

        if (coverageCount[vertex] > 0) {
            continue;
        }

        bool possible = false;

        for (int i = index; i < m; i++) {

            int u = edges[i].first;
            int v = edges[i].second;

            if (u == vertex || v == vertex) {

                possible = true;
                break;
            }
        }

        if (!possible) {
            return false;
        }
    }

    return true;
}

// Count uncovered vertices
int countUncovered() {

    int count = 0;

    for (int i = 0; i < n; i++) {

        if (coverageCount[i] == 0) {
            count++;
        }
    }

    return count;
}

// Add an edge to the current edge cover
void addEdge(int edgeIndex) {

    int u = edges[edgeIndex].first;
    int v = edges[edgeIndex].second;

    currentCover.push_back(edgeIndex);

    coverageCount[u]++;
    coverageCount[v]++;
}

// Remove an edge during backtracking
void removeEdge(int edgeIndex) {

    int u = edges[edgeIndex].first;
    int v = edges[edgeIndex].second;

    coverageCount[u]--;
    coverageCount[v]--;

    currentCover.pop_back();
}

// Store a minimum edge cover
void storeCover() {

    totalMinimumCovers++;

    if ((long long)minimumCovers.size() < maxSolutions) {

        minimumCovers.push_back(currentCover);

    } else {

        storageLimitReached = true;
    }
}

// Recursive minimum edge cover
void findMinimumEdgeCover(int index) {

    recursiveCalls++;

    // Check whether all vertices are covered
    if (isFullyCovered()) {

        int currentSize = (int)currentCover.size();

        // A better solution has been found
        if (minimumSize == -1 ||
            currentSize < minimumSize) {

            minimumSize = currentSize;

            minimumCovers.clear();

            totalMinimumCovers = 0;

            storageLimitReached = false;

            storeCover();
        }

        // Another minimum solution has been found
        else if (currentSize == minimumSize) {

            storeCover();
        }

        return;
    }

    // All edges have been processed
    if (index == m) {
        return;
    }

    int currentSize = (int)currentCover.size();

    // Prune if the current solution is already too large
    if (minimumSize != -1 &&
        currentSize >= minimumSize) {

        return;
    }

    // Check whether remaining edges can cover
    // all currently uncovered vertices
    if (!canStillCover(index)) {
        return;
    }

    // Calculate a lower bound:
    // One edge can cover at most two new vertices
    int uncovered = countUncovered();

    int lowerBound = (uncovered + 1) / 2;

    // Prune if no better solution is possible
    if (minimumSize != -1 &&
        currentSize + lowerBound > minimumSize) {

        return;
    }

    // Option 1: Include the current edge
    addEdge(index);

    findMinimumEdgeCover(index + 1);

    // Backtracking
    removeEdge(index);

    // Option 2: Exclude the current edge
    findMinimumEdgeCover(index + 1);
}

// Display graph edges
void displayGraph() {

    cout << "\n========== GRAPH EDGES ==========\n";

    if (edges.empty()) {

        cout << "The graph has no edges.\n";

        return;
    }

    for (int i = 0; i < m; i++) {

        cout << "Edge " << i
             << ": ("
             << edges[i].first
             << ", "
             << edges[i].second
             << ")\n";
    }
}

// Display isolated vertices
void displayIsolatedVertices() {

    cout << "\n========== ISOLATED VERTICES ==========\n";

    bool found = false;

    for (int i = 0; i < n; i++) {

        if (coverageCount[i] == 0) {

            cout << i << " ";

            found = true;
        }
    }

    if (!found) {
        cout << "None";
    }

    cout << endl;
}

// Display one edge cover
void displayCover(const vector<int>& cover) {

    cout << "{ ";

    for (int i = 0; i < (int)cover.size(); i++) {

        int edgeIndex = cover[i];

        cout << "("
             << edges[edgeIndex].first
             << ", "
             << edges[edgeIndex].second
             << ")";

        if (i != (int)cover.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display final results
void displayResults() {

    cout << "\n========== MINIMUM EDGE COVER RESULTS ==========\n";

    cout << "\nMinimum edge cover size: "
         << minimumSize << endl;

    cout << "\nStored minimum edge covers:\n";

    for (int i = 0;
         i < (int)minimumCovers.size();
         i++) {

        cout << "\nCover " << i + 1 << ": ";

        displayCover(minimumCovers[i]);

        cout << endl;
    }

    cout << "\nTotal minimum edge covers found: "
         << totalMinimumCovers << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional minimum edge covers were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== MINIMUM EDGE COVER USING BACKTRACKING =====\n";

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

    vector<vector<bool>> adj(
        n, vector<bool>(n, false)
    );

    coverageCount.assign(n, 0);

    cout << "\nEnter undirected edges using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {

        int u, v;

        cout << "Edge " << i + 1 << ": ";

        cin >> u >> v;

        // Validate vertex numbers
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

    // Calculate vertex degrees
    for (int i = 0; i < m; i++) {

        int u = edges[i].first;
        int v = edges[i].second;

        coverageCount[u]++;
        coverageCount[v]++;
    }

    displayIsolatedVertices();

    // An isolated vertex cannot be covered by any edge
    for (int i = 0; i < n; i++) {

        if (coverageCount[i] == 0) {

            cout << "\nAn edge cover does not exist.\n";

            cout << "Vertex " << i
                 << " is isolated and has no incident edge.\n";

            return 0;
        }
    }

    // Reset coverage before starting backtracking
    coverageCount.assign(n, 0);

    cout << "\nSearching for minimum edge cover...\n";

    findMinimumEdgeCover(0);

    if (minimumSize == -1) {

        cout << "\nNo edge cover exists.\n";

        return 0;
    }

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
