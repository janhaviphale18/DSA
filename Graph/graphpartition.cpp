#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n, k;

long long maxSolutions;

vector<vector<int>> graph;

vector<int> groupOf;
vector<int> groupSize;

vector<vector<vector<int>>> bestPartitions;

int minimumSize;
int maximumSize;

long long minimumCut = LLONG_MAX;
long long optimalCount = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

// Calculate the number of edges crossing different groups
long long calculateCut() {

    long long cut = 0;

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (graph[i][j] == 1 &&
                groupOf[i] != groupOf[j]) {

                cut++;
            }
        }
    }

    return cut;
}

// Check whether the current partition can still be completed
bool isFeasible(int index, int usedGroups) {

    int remaining = n - index;
    int missingGroups = k - usedGroups;

    // Every missing group needs at least one vertex
    if (remaining < missingGroups) {
        return false;
    }

    // No group can exceed the maximum allowed size
    for (int i = 0; i < usedGroups; i++) {

        if (groupSize[i] > maximumSize) {
            return false;
        }
    }

    return true;
}

// Store a partition if it is optimal
void storePartition() {

    vector<vector<int>> partition(k);

    for (int vertex = 0; vertex < n; vertex++) {

        partition[groupOf[vertex]].push_back(vertex);
    }

    optimalCount++;

    if ((long long)bestPartitions.size() < maxSolutions) {

        bestPartitions.push_back(partition);

    } else {

        storageLimitReached = true;
    }
}

// Recursive backtracking function
void partitionGraph(int index, int usedGroups) {

    recursiveCalls++;

    // Check whether the current assignment is feasible
    if (!isFeasible(index, usedGroups)) {
        return;
    }

    // All vertices have been assigned
    if (index == n) {

        // All groups must be non-empty
        if (usedGroups != k) {
            return;
        }

        // Check balanced group sizes
        for (int i = 0; i < k; i++) {

            if (groupSize[i] < minimumSize ||
                groupSize[i] > maximumSize) {

                return;
            }
        }

        // Calculate the number of crossing edges
        long long currentCut = calculateCut();

        // A better partition has been found
        if (currentCut < minimumCut) {

            minimumCut = currentCut;

            optimalCount = 0;
            bestPartitions.clear();

            storageLimitReached = false;

            storePartition();
        }

        // Another optimal partition has been found
        else if (currentCut == minimumCut) {

            storePartition();
        }

        return;
    }

    // Try existing groups and at most one new group.
    // This avoids generating equivalent group-label permutations.
    int lastGroup = usedGroups;

    if (usedGroups == k) {
        lastGroup = k - 1;
    }

    for (int group = 0; group <= lastGroup; group++) {

        // Do not exceed the maximum group size
        if (groupSize[group] >= maximumSize) {
            continue;
        }

        // A new group must be created in order
        if (group == usedGroups && usedGroups >= k) {
            continue;
        }

        // Assign current vertex
        groupOf[index] = group;
        groupSize[group]++;

        int newUsedGroups = usedGroups;

        if (group == usedGroups) {
            newUsedGroups++;
        }

        // Explore the next vertex
        partitionGraph(index + 1, newUsedGroups);

        // Backtrack
        groupSize[group]--;
        groupOf[index] = -1;
    }
}

// Display a partition
void displayPartition(
    const vector<vector<int>>& partition,
    int number
) {

    cout << "\nPartition " << number << ":\n";

    for (int i = 0; i < (int)partition.size(); i++) {

        cout << "Group " << i + 1 << ": { ";

        for (int j = 0;
             j < (int)partition[i].size();
             j++) {

            cout << partition[i][j];

            if (j != (int)partition[i].size() - 1) {
                cout << ", ";
            }
        }

        cout << " }\n";
    }
}

// Display all optimal partitions
void displayResults() {

    cout << "\n========== GRAPH PARTITIONING RESULTS ==========\n";

    cout << "\nMinimum number of crossing edges: "
         << minimumCut << endl;

    cout << "\nOptimal partitions stored: "
         << bestPartitions.size() << endl;

    cout << "Total optimal partitions found: "
         << optimalCount << endl;

    for (int i = 0; i < (int)bestPartitions.size(); i++) {

        displayPartition(bestPartitions[i], i + 1);
    }

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";
        cout << "Additional optimal partitions were found "
             << "but not stored.\n";
    }
}

// Display adjacency matrix
void displayGraph() {

    cout << "\n========== ADJACENCY MATRIX ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }
}

// Validate a simple undirected graph
bool validateGraph() {

    for (int i = 0; i < n; i++) {

        if (graph[i][i] != 0) {
            return false;
        }

        for (int j = 0; j < n; j++) {

            if (graph[i][j] != graph[j][i]) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    cout << "===== GRAPH PARTITIONING USING BACKTRACKING =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0) {

        cout << "\nNumber of vertices must be positive.\n";
        return 0;
    }

    if (n > 20) {

        cout << "\nGraph is too large for this basic implementation.\n";
        cout << "Please enter at most 20 vertices.\n";

        return 0;
    }

    cout << "Enter number of groups: ";
    cin >> k;

    if (k <= 0 || k > n) {

        cout << "\nInvalid number of groups.\n";
        cout << "Number of groups must be between 1 and N.\n";

        return 0;
    }

    // Calculate balanced group size limits
    minimumSize = n / k;
    maximumSize = (n + k - 1) / k;

    graph.resize(n, vector<int>(n));

    cout << "\nEnter adjacency matrix:\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cin >> graph[i][j];

            if (graph[i][j] != 0 && graph[i][j] != 1) {

                cout << "\nInvalid adjacency matrix value.\n";
                return 0;
            }
        }
    }

    if (!validateGraph()) {

        cout << "\nInvalid graph.\n";
        cout << "Graph must be simple and undirected.\n";

        return 0;
    }

    cout << "\nEnter maximum optimal partitions to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";
        return 0;
    }

    groupOf.assign(n, -1);
    groupSize.assign(k, 0);

    displayGraph();

    cout << "\nGroup size constraints:\n";
    cout << "Minimum group size: " << minimumSize << endl;
    cout << "Maximum group size: " << maximumSize << endl;

    cout << "\nSearching for optimal partitions...\n";

    partitionGraph(0, 0);

    if (bestPartitions.empty()) {

        cout << "\nNo valid partition exists.\n";

    } else {

        displayResults();
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
