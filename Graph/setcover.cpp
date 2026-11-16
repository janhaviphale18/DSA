#include <iostream>
#include <vector>
using namespace std;

int n;
int m;

long long maxSolutions;
long long totalMinimumCovers = 0;

vector<vector<bool>> adj;

vector<int> coverageCount;

vector<int> currentCover;

vector<vector<int>> minimumCovers;

int minimumSize = -1;

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
// can still be covered by a remaining candidate
bool canStillCover(int index) {

    for (int vertex = 0; vertex < n; vertex++) {

        if (coverageCount[vertex] > 0) {
            continue;
        }

        bool possible = false;

        // Check all remaining candidate vertices
        for (int candidate = index;
             candidate < n;
             candidate++) {

            if (candidate == vertex ||
                adj[candidate][vertex]) {

                possible = true;
                break;
            }
        }

        // No remaining candidate can cover this vertex
        if (!possible) {
            return false;
        }
    }

    return true;
}

// Add a vertex and update its closed neighborhood
void addVertex(int vertex) {

    currentCover.push_back(vertex);

    // A selected vertex covers itself
    coverageCount[vertex]++;

    // It also covers all adjacent vertices
    for (int neighbor = 0; neighbor < n; neighbor++) {

        if (adj[vertex][neighbor]) {
            coverageCount[neighbor]++;
        }
    }
}

// Remove a vertex and restore coverage
void removeVertex(int vertex) {

    // Remove its coverage from neighboring vertices
    for (int neighbor = 0; neighbor < n; neighbor++) {

        if (adj[vertex][neighbor]) {
            coverageCount[neighbor]--;
        }
    }

    // Remove its self-coverage
    coverageCount[vertex]--;

    currentCover.pop_back();
}

// Store a minimum set cover
void storeCover() {

    totalMinimumCovers++;

    if ((long long)minimumCovers.size() < maxSolutions) {

        minimumCovers.push_back(currentCover);

    } else {

        storageLimitReached = true;
    }
}

// Recursive set cover using backtracking
void findMinimumCover(int index) {

    recursiveCalls++;

    // Check whether all vertices are covered
    if (isFullyCovered()) {

        int currentSize = (int)currentCover.size();

        // A smaller solution has been found
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

    // All candidate vertices have been processed
    if (index == n) {
        return;
    }

    // Prune branches that cannot improve the answer
    if (minimumSize != -1 &&
        (int)currentCover.size() >= minimumSize) {

        return;
    }

    // Prune if remaining vertices cannot cover
    // all currently uncovered vertices
    if (!canStillCover(index)) {
        return;
    }

    // Option 1: Exclude the current vertex
    findMinimumCover(index + 1);

    // Option 2: Include the current vertex
    addVertex(index);

    findMinimumCover(index + 1);

    // Backtracking
    removeVertex(index);
}

// Display the graph
void displayGraph() {

    cout << "\n========== ADJACENCY MATRIX ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cout << adj[i][j] << " ";
        }

        cout << endl;
    }
}

// Display the closed neighborhood of each vertex
void displayNeighborhoods() {

    cout << "\n========== CLOSED NEIGHBORHOODS ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "N[" << i << "] = { " << i;

        for (int j = 0; j < n; j++) {

            if (adj[i][j]) {
                cout << ", " << j;
            }
        }

        cout << " }\n";
    }
}

// Display one set cover
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

    cout << "\n========== GRAPH SET COVER RESULTS ==========\n";

    cout << "\nMinimum dominating set size: "
         << minimumSize << endl;

    cout << "\nStored minimum set covers:\n";

    for (int i = 0;
         i < (int)minimumCovers.size();
         i++) {

        cout << "\nCover " << i + 1 << ": ";

        displayCover(minimumCovers[i]);

        cout << endl;
    }

    cout << "\nTotal minimum set covers found: "
         << totalMinimumCovers << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional minimum covers were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== GRAPH SET COVER USING BACKTRACKING =====\n";

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

        // Insert undirected edge
        adj[u][v] = true;
        adj[v][u] = true;
    }

    cout << "\nEnter maximum minimum covers to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    displayNeighborhoods();

    cout << "\nSearching for minimum set cover...\n";

    findMinimumCover(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
