#include <iostream>
#include <vector>
using namespace std;

int n;
int m;

long long maxSolutions;

vector<vector<bool>> adj;

vector<vector<int>> currentClusters;

vector<vector<vector<int>>> minimumPartitions;

int minimumClusters = -1;

long long totalMinimumPartitions = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// Check whether a vertex can join an existing cluster
bool canJoinCluster(int vertex, int clusterIndex) {

    for (int member : currentClusters[clusterIndex]) {

        // Every pair of vertices in a clique
        // must have a connecting edge
        if (!adj[vertex][member]) {
            return false;
        }
    }

    return true;
}

// Store a minimum clique partition
void storePartition() {

    totalMinimumPartitions++;

    if ((long long)minimumPartitions.size() < maxSolutions) {

        minimumPartitions.push_back(currentClusters);

    } else {

        storageLimitReached = true;
    }
}

// Recursive minimum clique partition
void findMinimumPartition(int vertex) {

    recursiveCalls++;

    // Every vertex has been assigned
    if (vertex == n) {

        int currentSize = (int)currentClusters.size();

        // A better partition has been found
        if (minimumClusters == -1 ||
            currentSize < minimumClusters) {

            minimumClusters = currentSize;

            minimumPartitions.clear();

            totalMinimumPartitions = 0;

            storageLimitReached = false;

            storePartition();
        }

        // Another minimum partition has been found
        else if (currentSize == minimumClusters) {

            storePartition();
        }

        return;
    }

    // Prune if the current number of clusters
    // is already greater than the best solution
    if (minimumClusters != -1 &&
        (int)currentClusters.size() > minimumClusters) {

        return;
    }

    // Option 1: Place the vertex into an existing cluster
    for (int i = 0;
         i < (int)currentClusters.size();
         i++) {

        if (canJoinCluster(vertex, i)) {

            // Select the existing cluster
            currentClusters[i].push_back(vertex);

            // Explore the next vertex
            findMinimumPartition(vertex + 1);

            // Backtracking
            currentClusters[i].pop_back();
        }
    }

    // Option 2: Create a new cluster
    if (minimumClusters == -1 ||
        (int)currentClusters.size() < minimumClusters) {

        currentClusters.push_back({vertex});

        findMinimumPartition(vertex + 1);

        // Backtracking
        currentClusters.pop_back();
    }
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

// Display adjacency matrix
void displayMatrix() {

    cout << "\n========== ADJACENCY MATRIX ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cout << adj[i][j] << " ";
        }

        cout << endl;
    }
}

// Display one clique partition
void displayPartition(
    const vector<vector<int>>& partition
) {

    for (int i = 0; i < (int)partition.size(); i++) {

        cout << "\nCluster " << i + 1 << ": { ";

        for (int j = 0;
             j < (int)partition[i].size();
             j++) {

            cout << partition[i][j];

            if (j != (int)partition[i].size() - 1) {
                cout << ", ";
            }
        }

        cout << " }";
    }
}

// Display final results
void displayResults() {

    cout << "\n========== GRAPH CLUSTERING RESULTS ==========\n";

    cout << "\nMinimum number of clusters: "
         << minimumClusters << endl;

    cout << "\nStored minimum clique partitions:\n";

    for (int i = 0;
         i < (int)minimumPartitions.size();
         i++) {

        cout << "\nPartition " << i + 1 << ":\n";

        displayPartition(minimumPartitions[i]);

        cout << endl;
    }

    cout << "\nTotal minimum partitions found: "
         << totalMinimumPartitions << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional optimal partitions were found "
             << "but not stored.\n";
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;
}

// Main function
int main() {

    cout << "===== GRAPH CLUSTERING USING BACKTRACKING =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 15) {

        cout << "\nNumber of vertices must be between 1 and 15.\n";

        return 0;
    }

    cout << "\nEnter number of edges: ";
    cin >> m;

    if (m < 0 || m > n * (n - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return 0;
    }

    adj.assign(n, vector<bool>(n, false));

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

    cout << "\nEnter maximum minimum partitions to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    displayMatrix();

    cout << "\nSearching for minimum clique partition...\n";

    findMinimumPartition(0);

    displayResults();

    return 0;
}
