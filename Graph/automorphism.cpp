#include <iostream>
#include <vector>
using namespace std;

int n;
long long maxSolutions;

vector<vector<int>> graph;
vector<int> degree;

vector<int> mapping;
vector<bool> assigned;

vector<vector<int>> automorphisms;

long long recursiveCalls = 0;
bool limitReached = false;

// Calculate the degree of every vertex
void calculateDegrees() {

    degree.resize(n, 0);

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (graph[i][j] == 1) {
                degree[i]++;
            }
        }
    }
}

// Check whether a partial mapping preserves adjacency
bool isCompatible(int vertex, int candidate) {

    for (int i = 0; i < vertex; i++) {

        int mappedVertex = mapping[i];

        if (graph[vertex][i] !=
            graph[candidate][mappedVertex]) {

            return false;
        }
    }

    return true;
}

// Recursive function to find automorphisms
void findAutomorphisms(int vertex) {

    recursiveCalls++;

    // Stop if the solution limit is reached
    if ((long long)automorphisms.size() >= maxSolutions) {

        limitReached = true;
        return;
    }

    // All vertices have been mapped
    if (vertex == n) {

        automorphisms.push_back(mapping);
        return;
    }

    // Try every possible vertex as a mapping candidate
    for (int candidate = 0; candidate < n; candidate++) {

        // A vertex can be assigned only once
        if (assigned[candidate]) {
            continue;
        }

        // Corresponding vertices must have equal degrees
        if (degree[vertex] != degree[candidate]) {
            continue;
        }

        // Check adjacency with previously mapped vertices
        if (!isCompatible(vertex, candidate)) {
            continue;
        }

        // Assign the mapping
        mapping[vertex] = candidate;
        assigned[candidate] = true;

        // Explore the next vertex
        findAutomorphisms(vertex + 1);

        // Stop if the requested limit is reached
        if (limitReached) {
            return;
        }

        // Backtrack
        mapping[vertex] = -1;
        assigned[candidate] = false;
    }
}

// Start the automorphism search
void solveAutomorphism() {

    calculateDegrees();

    mapping.assign(n, -1);
    assigned.assign(n, false);

    findAutomorphisms(0);
}

// Display all automorphisms
void displayAutomorphisms() {

    cout << "\n========== GRAPH AUTOMORPHISMS ==========\n";

    for (int i = 0; i < (int)automorphisms.size(); i++) {

        cout << "\nAutomorphism " << i + 1 << ":\n";

        for (int j = 0; j < n; j++) {

            cout << "Vertex " << j
                 << " -> Vertex "
                 << automorphisms[i][j] << endl;
        }
    }

    cout << "\nTotal automorphisms found: "
         << automorphisms.size() << endl;

    if (limitReached) {

        cout << "Search stopped after reaching the solution limit.\n";

        cout << "Additional automorphisms, if any, "
             << "were not explored.\n";
    }
}

// Display the adjacency matrix
void displayGraph() {

    cout << "\n========== ADJACENCY MATRIX ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }
}

// Validate the graph
bool validateGraph() {

    for (int i = 0; i < n; i++) {

        // Self-loops are not allowed
        if (graph[i][i] != 0) {
            return false;
        }

        // Graph must be undirected
        for (int j = 0; j < n; j++) {

            if (graph[i][j] != graph[j][i]) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    cout << "===== GRAPH AUTOMORPHISM USING BACKTRACKING =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0) {

        cout << "\nNumber of vertices must be positive.\n";
        return 0;
    }

    if (n > 10) {

        cout << "\nGraph is too large for this basic implementation.\n";
        cout << "Please enter at most 10 vertices.\n";

        return 0;
    }

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
        cout << "Enter a simple undirected graph without self-loops.\n";

        return 0;
    }

    cout << "\nEnter maximum automorphisms to display: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nSolution limit must be positive.\n";
        return 0;
    }

    displayGraph();

    cout << "\nFinding graph automorphisms...\n";

    solveAutomorphism();

    if (automorphisms.empty()) {

        cout << "\nNo automorphism found.\n";

    } else {

        displayAutomorphisms();
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
