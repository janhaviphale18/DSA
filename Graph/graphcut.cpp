#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
int m;

int sourceVertex;
int destinationVertex;

long long maxSolutions;

vector<pair<int, int>> edges;

vector<bool> removed;

vector<int> currentCut;

vector<vector<int>> minimumCuts;

int minimumCutSize = -1;

long long totalMinimumCuts = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// Check whether destination is reachable from source
bool isReachable() {

    vector<bool> visited(n, false);

    queue<int> q;

    visited[sourceVertex] = true;

    q.push(sourceVertex);

    while (!q.empty()) {

        int current = q.front();

        q.pop();

        if (current == destinationVertex) {
            return true;
        }

        for (int i = 0; i < m; i++) {

            if (removed[i]) {
                continue;
            }

            int u = edges[i].first;
            int v = edges[i].second;

            int neighbor = -1;

            if (u == current) {
                neighbor = v;
            }

            else if (v == current) {
                neighbor = u;
            }

            if (neighbor != -1 && !visited[neighbor]) {

                visited[neighbor] = true;

                q.push(neighbor);
            }
        }
    }

    return false;
}

// Store a minimum cut
void storeCut() {

    totalMinimumCuts++;

    if ((long long)minimumCuts.size() < maxSolutions) {

        minimumCuts.push_back(currentCut);

    } else {

        storageLimitReached = true;
    }
}

// Recursive minimum cut
void findMinimumCut(int index) {

    recursiveCalls++;

    // If source and destination are disconnected,
    // the current selection is a valid cut
    if (!isReachable()) {

        int currentSize = (int)currentCut.size();

        // A better cut has been found
        if (minimumCutSize == -1 ||
            currentSize < minimumCutSize) {

            minimumCutSize = currentSize;

            minimumCuts.clear();

            totalMinimumCuts = 0;

            storageLimitReached = false;

            storeCut();
        }

        // Another minimum cut is found
        else if (currentSize == minimumCutSize) {

            storeCut();
        }

        return;
    }

    // All edges have been processed
    if (index == m) {
        return;
    }

    // Prune branches that cannot improve the answer
    if (minimumCutSize != -1 &&
        (int)currentCut.size() >= minimumCutSize) {

        return;
    }

    // Option 1: Keep the current edge
    findMinimumCut(index + 1);

    // Option 2: Remove the current edge
    removed[index] = true;

    currentCut.push_back(index);

    findMinimumCut(index + 1);

    // Backtracking
    currentCut.pop_back();

    removed[index] = false;
}

// Display all graph edges
void displayGraph() {

    cout << "\n========== GRAPH EDGES ==========\n";

    if (edges.empty()) {

        cout << "No edges in the graph.\n";

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

// Display one cut
void displayCut(const vector<int>& cut) {

    cout << "{ ";

    for (int i = 0; i < (int)cut.size(); i++) {

        int edgeIndex = cut[i];

        cout << "("
             << edges[edgeIndex].first
             << ", "
             << edges[edgeIndex].second
             << ")";

        if (i != (int)cut.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display final results
void displayResults() {

    cout << "\n========== MINIMUM GRAPH CUT RESULTS ==========\n";

    cout << "\nSource vertex: "
         << sourceVertex << endl;

    cout << "Destination vertex: "
         << destinationVertex << endl;

    cout << "\nMinimum cut size: "
         << minimumCutSize << endl;

    cout << "\nStored minimum cuts:\n";

    for (int i = 0;
         i < (int)minimumCuts.size();
         i++) {

        cout << "\nCut " << i + 1 << ": ";

        displayCut(minimumCuts[i]);

        cout << endl;
    }

    cout << "\nTotal minimum cuts found: "
         << totalMinimumCuts << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional minimum cuts were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== MINIMUM GRAPH CUT USING BACKTRACKING =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n < 2 || n > 15) {

        cout << "\nNumber of vertices must be between 2 and 15.\n";

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

        adj[u][v] = true;
        adj[v][u] = true;

        edges.push_back({u, v});
    }

    cout << "\nEnter source vertex: ";
    cin >> sourceVertex;

    cout << "Enter destination vertex: ";
    cin >> destinationVertex;

    if (sourceVertex < 0 || sourceVertex >= n ||
        destinationVertex < 0 || destinationVertex >= n ||
        sourceVertex == destinationVertex) {

        cout << "\nInvalid source or destination.\n";

        return 0;
    }

    cout << "\nEnter maximum minimum cuts to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    removed.assign(m, false);

    displayGraph();

    // Check whether a path exists initially
    if (!isReachable()) {

        cout << "\nSource and destination are already disconnected.\n";

        cout << "Minimum cut size: 0\n";

        cout << "No edges need to be removed.\n";

        return 0;
    }

    cout << "\nSearching for minimum graph cut...\n";

    findMinimumCut(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
