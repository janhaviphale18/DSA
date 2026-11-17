#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

int n;
int m;

long long maxSolutions;

uint32_t fullMask = 0;

vector<uint32_t> coverage;

vector<int> currentSet;

vector<vector<int>> minimumSets;

int minimumSize = -1;

long long totalMinimumSets = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// Count the number of set bits
int countBits(uint32_t mask) {

    int count = 0;

    while (mask != 0) {

        count += mask & 1U;

        mask >>= 1;
    }

    return count;
}

// Store a minimum dominating set
void storeSolution() {

    totalMinimumSets++;

    if ((long long)minimumSets.size() < maxSolutions) {

        minimumSets.push_back(currentSet);

    } else {

        storageLimitReached = true;
    }
}

// Calculate a lower bound on the number of
// additional vertices required
int calculateLowerBound(
    int index,
    uint32_t uncoveredMask
) {

    int maximumGain = 0;

    // Find the maximum number of currently
    // uncovered vertices any remaining candidate covers
    for (int i = index; i < n; i++) {

        int gain = countBits(
            coverage[i] & uncoveredMask
        );

        if (gain > maximumGain) {
            maximumGain = gain;
        }
    }

    // No remaining candidate can cover an uncovered vertex
    if (maximumGain == 0) {
        return n + 1;
    }

    int uncoveredCount = countBits(uncoveredMask);

    // Ceiling division
    return (uncoveredCount + maximumGain - 1)
           / maximumGain;
}

// Recursive optimized backtracking
void findMinimumDominatingSet(
    int index,
    uint32_t coveredMask
) {

    recursiveCalls++;

    // Every vertex is dominated
    if (coveredMask == fullMask) {

        int currentSize = (int)currentSet.size();

        // A better solution is found
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

    // All candidate vertices have been processed
    if (index == n) {
        return;
    }

    int currentSize = (int)currentSet.size();

    // Current solution cannot improve the answer
    if (minimumSize != -1 &&
        currentSize >= minimumSize) {

        return;
    }

    // Find vertices that are still uncovered
    uint32_t uncoveredMask =
        fullMask & (~coveredMask);

    // Calculate the minimum additional selections required
    int lowerBound = calculateLowerBound(
        index,
        uncoveredMask
    );

    // Prune if even the lower-bound estimate
    // cannot produce a better solution
    if (minimumSize != -1 &&
        currentSize + lowerBound > minimumSize) {

        return;
    }

    // Option 1: Include the current vertex
    currentSet.push_back(index);

    findMinimumDominatingSet(
        index + 1,
        coveredMask | coverage[index]
    );

    // Backtracking
    currentSet.pop_back();

    // Option 2: Exclude the current vertex
    findMinimumDominatingSet(
        index + 1,
        coveredMask
    );
}

// Display a bitmask in binary
void displayMask(uint32_t mask) {

    for (int i = n - 1; i >= 0; i--) {

        cout << ((mask >> i) & 1U);
    }
}

// Display the graph coverage of each vertex
void displayCoverage() {

    cout << "\n========== VERTEX COVERAGE MASKS ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "Vertex " << i << ": ";

        displayMask(coverage[i]);

        cout << "  { ";

        bool first = true;

        for (int j = 0; j < n; j++) {

            if (coverage[i] & (1U << j)) {

                if (!first) {
                    cout << ", ";
                }

                cout << j;

                first = false;
            }
        }

        cout << " }\n";
    }
}

// Display one dominating set
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

    cout << "\n========== OPTIMIZED DOMINATING SET RESULTS ==========\n";

    cout << "\nMinimum dominating set size: "
         << minimumSize << endl;

    cout << "\nStored minimum dominating sets:\n";

    for (int i = 0;
         i < (int)minimumSets.size();
         i++) {

        cout << "\nSet " << i + 1 << ": ";

        displaySet(minimumSets[i]);

        cout << endl;
    }

    cout << "\nTotal minimum dominating sets found: "
         << totalMinimumSets << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional optimal solutions were found "
             << "but not stored.\n";
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;
}

// Main function
int main() {

    cout << "===== OPTIMIZED MINIMUM DOMINATING SET =====\n";

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
    }

    cout << "\nEnter maximum minimum sets to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    // Construct full vertex mask
    fullMask = (1U << n) - 1U;

    coverage.assign(n, 0);

    // Construct closed-neighborhood masks
    for (int i = 0; i < n; i++) {

        // Every vertex covers itself
        coverage[i] |= (1U << i);

        for (int j = 0; j < n; j++) {

            if (adj[i][j]) {

                coverage[i] |= (1U << j);
            }
        }
    }

    cout << "\n========== ADJACENCY MATRIX ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cout << adj[i][j] << " ";
        }

        cout << endl;
    }

    displayCoverage();

    cout << "\nSearching for minimum dominating sets...\n";

    findMinimumDominatingSet(0, 0);

    displayResults();

    return 0;
}
