#include <iostream>
#include <vector>
using namespace std;

int n;
int m;
int half;

long long maxSolutions;

vector<vector<bool>> adj;

vector<int> group;

vector<vector<int>> bestGroupA;
vector<vector<int>> bestGroupB;

int minimumCut = -1;

long long totalMinimumBisections = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// Store one optimal bisection
void storeBisection() {

    vector<int> groupA;
    vector<int> groupB;

    for (int i = 0; i < n; i++) {

        if (group[i] == 0) {
            groupA.push_back(i);
        } else {
            groupB.push_back(i);
        }
    }

    totalMinimumBisections++;

    if ((long long)bestGroupA.size() < maxSolutions) {

        bestGroupA.push_back(groupA);
        bestGroupB.push_back(groupB);

    } else {

        storageLimitReached = true;
    }
}

// Calculate additional crossing edges
// when assigning the current vertex to a group
int calculateAdditionalCut(int vertex, int selectedGroup) {

    int additionalCut = 0;

    // Only previously assigned vertices are checked
    for (int i = 0; i < vertex; i++) {

        if (adj[vertex][i] &&
            group[i] != selectedGroup) {

            additionalCut++;
        }
    }

    return additionalCut;
}

// Recursive minimum bisection
void findMinimumBisection(
    int index,
    int groupACount,
    int groupBCount,
    int currentCut
) {

    recursiveCalls++;

    // Branch and bound
    if (minimumCut != -1 &&
        currentCut > minimumCut) {

        return;
    }

    // All vertices have been assigned
    if (index == n) {

        // Both groups must contain exactly half the vertices
        if (groupACount != half ||
            groupBCount != half) {

            return;
        }

        // A better bisection is found
        if (minimumCut == -1 ||
            currentCut < minimumCut) {

            minimumCut = currentCut;

            bestGroupA.clear();
            bestGroupB.clear();

            totalMinimumBisections = 0;

            storageLimitReached = false;

            storeBisection();
        }

        // Another optimal bisection is found
        else if (currentCut == minimumCut) {

            storeBisection();
        }

        return;
    }

    // Option 1: Assign the current vertex to Group A
    if (groupACount < half) {

        int additionalCut =
            calculateAdditionalCut(index, 0);

        group[index] = 0;

        findMinimumBisection(
            index + 1,
            groupACount + 1,
            groupBCount,
            currentCut + additionalCut
        );

        // Backtracking
        group[index] = -1;
    }

    // Option 2: Assign the current vertex to Group B
    if (groupBCount < half) {

        int additionalCut =
            calculateAdditionalCut(index, 1);

        group[index] = 1;

        findMinimumBisection(
            index + 1,
            groupACount,
            groupBCount + 1,
            currentCut + additionalCut
        );

        // Backtracking
        group[index] = -1;
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

// Display one group
void displayGroup(const vector<int>& vertices) {

    cout << "{ ";

    for (int i = 0; i < (int)vertices.size(); i++) {

        cout << vertices[i];

        if (i != (int)vertices.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display crossing edges for a partition
void displayCrossingEdges(
    const vector<int>& groupA,
    const vector<int>& groupB
) {

    cout << "\nCrossing edges: ";

    int count = 0;

    for (int u : groupA) {

        for (int v : groupB) {

            if (adj[u][v]) {

                cout << "(" << u << ", " << v << ") ";

                count++;
            }
        }
    }

    if (count == 0) {
        cout << "None";
    }

    cout << endl;
}

// Display final results
void displayResults() {

    cout << "\n========== MINIMUM BISECTION RESULTS ==========\n";

    cout << "\nMinimum cut size: "
         << minimumCut << endl;

    cout << "\nStored minimum bisections:\n";

    for (int i = 0;
         i < (int)bestGroupA.size();
         i++) {

        cout << "\nBisection " << i + 1 << ":\n";

        cout << "Group A: ";

        displayGroup(bestGroupA[i]);

        cout << "\nGroup B: ";

        displayGroup(bestGroupB[i]);

        cout << endl;

        displayCrossingEdges(
            bestGroupA[i],
            bestGroupB[i]
        );
    }

    cout << "\nTotal minimum bisections found: "
         << totalMinimumBisections << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional optimal bisections were found "
             << "but not stored.\n";
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;
}

// Main function
int main() {

    cout << "===== MINIMUM GRAPH BISECTION =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n < 2 || n > 20 || n % 2 != 0) {

        cout << "\nNumber of vertices must be even "
             << "and between 2 and 20.\n";

        return 0;
    }

    half = n / 2;

    cout << "\nEnter number of edges: ";
    cin >> m;

    if (m < 0 || m > n * (n - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return 0;
    }

    adj.assign(n, vector<bool>(n, false));

    group.assign(n, -1);

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

    cout << "\nEnter maximum minimum bisections to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    displayMatrix();

    // Fix vertex 0 in Group A.
    // This avoids counting a partition and its reverse twice.
    group[0] = 0;

    cout << "\nEach group must contain "
         << half << " vertices.\n";

    cout << "\nSearching for minimum bisection...\n";

    findMinimumBisection(1, 1, 0, 0);

    displayResults();

    return 0;
}
