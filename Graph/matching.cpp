#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;

long long maxSolutions;
long long maximumMatchingCount = 0;

vector<vector<bool>> adj;

vector<bool> matched;

vector<pair<int, int>> currentMatching;

vector<vector<pair<int, int>>> maximumMatchings;

int maximumSize = -1;

bool storageLimitReached = false;

long long recursiveCalls = 0;

// Display one matching
void displayMatching(
    const vector<pair<int, int>>& matching
) {

    if (matching.empty()) {
        cout << "Empty matching";
        return;
    }

    for (int i = 0; i < (int)matching.size(); i++) {

        cout << "("
             << matching[i].first
             << ", "
             << matching[i].second
             << ")";

        if (i != (int)matching.size() - 1) {
            cout << ", ";
        }
    }
}

// Store a maximum matching
void storeMatching() {

    maximumMatchingCount++;

    if ((long long)maximumMatchings.size() < maxSolutions) {

        maximumMatchings.push_back(currentMatching);

    } else {

        storageLimitReached = true;
    }
}

// Find the first unmatched vertex
int findFirstUnmatched() {

    for (int i = 0; i < n; i++) {

        if (!matched[i]) {
            return i;
        }
    }

    return -1;
}

// Count unmatched vertices
int countUnmatched() {

    int count = 0;

    for (int i = 0; i < n; i++) {

        if (!matched[i]) {
            count++;
        }
    }

    return count;
}

// Recursive maximum matching
void findMaximumMatching() {

    recursiveCalls++;

    int remaining = countUnmatched();

    // Branch and bound
    int upperBound =
        (int)currentMatching.size() + remaining / 2;

    if (upperBound < maximumSize) {
        return;
    }

    // Find the first unmatched vertex
    int vertex = findFirstUnmatched();

    // All vertices have been processed
    if (vertex == -1) {

        int currentSize =
            (int)currentMatching.size();

        // A better matching is found
        if (currentSize > maximumSize) {

            maximumSize = currentSize;

            maximumMatchings.clear();

            maximumMatchingCount = 0;

            storageLimitReached = false;

            storeMatching();
        }

        // Another maximum matching is found
        else if (currentSize == maximumSize) {

            storeMatching();
        }

        return;
    }

    // Option 1: Leave this vertex unmatched
    matched[vertex] = true;

    findMaximumMatching();

    matched[vertex] = false;

    // Option 2: Match this vertex with an available neighbor
    for (int neighbor = vertex + 1;
         neighbor < n;
         neighbor++) {

        // Check whether the edge exists
        if (!adj[vertex][neighbor]) {
            continue;
        }

        // The neighbor must also be unmatched
        if (matched[neighbor]) {
            continue;
        }

        // Select the edge
        matched[vertex] = true;
        matched[neighbor] = true;

        currentMatching.push_back(
            {vertex, neighbor}
        );

        // Explore the remaining graph
        findMaximumMatching();

        // Backtrack
        currentMatching.pop_back();

        matched[vertex] = false;
        matched[neighbor] = false;
    }
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

// Display final results
void displayResults() {

    cout << "\n========== MAXIMUM MATCHING RESULTS ==========\n";

    cout << "\nMaximum matching size: "
         << maximumSize << endl;

    cout << "\nStored maximum matchings:\n";

    for (int i = 0;
         i < (int)maximumMatchings.size();
         i++) {

        cout << "\nMatching " << i + 1 << ": ";

        displayMatching(maximumMatchings[i]);

        cout << endl;
    }

    cout << "\nTotal maximum matchings found: "
         << maximumMatchingCount << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional maximum matchings were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== MAXIMUM GRAPH MATCHING =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 20) {

        cout << "\nNumber of vertices must be between 1 and 20.\n";

        return 0;
    }

    adj.assign(n, vector<bool>(n, false));

    matched.assign(n, false);

    int m;

    cout << "\nEnter number of edges: ";
    cin >> m;

    if (m < 0 || m > n * (n - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return 0;
    }

    cout << "\nEnter edges using vertex numbers 0 to "
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

        // Undirected graph
        adj[u][v] = true;
        adj[v][u] = true;
    }

    cout << "\nEnter maximum matchings to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    cout << "\nSearching for maximum matching...\n";

    findMaximumMatching();

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
