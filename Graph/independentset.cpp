#include <iostream>
#include <vector>
using namespace std;

int n;
long long maxSolutions;

vector<vector<int>> graph;

vector<int> currentSet;
vector<int> maximumSet;

vector<vector<int>> maximumSets;

long long recursiveCalls = 0;
bool limitReached = false;

// Check whether a vertex can be included
bool canInclude(int vertex) {

    for (int selectedVertex : currentSet) {

        if (graph[vertex][selectedVertex] == 1) {
            return false;
        }
    }

    return true;
}

// Recursive backtracking function
void findMaximumIndependentSet(int vertex) {

    recursiveCalls++;

    // Stop if the requested solution limit is reached
    if ((long long)maximumSets.size() >= maxSolutions) {
        limitReached = true;
        return;
    }

    // All vertices have been considered
    if (vertex == n) {

        if (currentSet.size() > maximumSet.size()) {

            maximumSet = currentSet;

            maximumSets.clear();
            maximumSets.push_back(currentSet);
        }

        else if (currentSet.size() == maximumSet.size()) {

            maximumSets.push_back(currentSet);
        }

        return;
    }

    // Choice 1: Include the current vertex
    if (canInclude(vertex)) {

        currentSet.push_back(vertex);

        findMaximumIndependentSet(vertex + 1);

        // Backtrack
        currentSet.pop_back();

        if (limitReached) {
            return;
        }
    }

    // Choice 2: Exclude the current vertex
    findMaximumIndependentSet(vertex + 1);
}

// Display a set of vertices
void displaySet(const vector<int>& selectedSet) {

    cout << "{ ";

    for (int i = 0; i < (int)selectedSet.size(); i++) {

        cout << selectedSet[i];

        if (i != (int)selectedSet.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display all maximum independent sets
void displayResults() {

    cout << "\n========== MAXIMUM INDEPENDENT SET ==========\n";

    cout << "\nMaximum independent set size: "
         << maximumSet.size() << endl;

    cout << "\nOne maximum independent set: ";

    displaySet(maximumSet);

    cout << "\n\nAll maximum independent sets:\n";

    for (int i = 0; i < (int)maximumSets.size(); i++) {

        cout << "Set " << i + 1 << ": ";

        displaySet(maximumSets[i]);

        cout << endl;
    }

    cout << "\nTotal maximum independent sets found: "
         << maximumSets.size() << endl;

    if (limitReached) {

        cout << "Search stopped after reaching the solution limit.\n";

        cout << "Additional maximum sets, if any, were not explored.\n";
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

// Validate simple undirected graph
bool validateGraph() {

    for (int i = 0; i < n; i++) {

        // Self-loops are not allowed
        if (graph[i][i] != 0) {
            return false;
        }

        // Check symmetry
        for (int j = 0; j < n; j++) {

            if (graph[i][j] != graph[j][i]) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    cout << "===== MAXIMUM INDEPENDENT SET USING BACKTRACKING =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0) {

        cout << "\nNumber of vertices must be positive.\n";
        return 0;
    }

    if (n > 25) {

        cout << "\nGraph is too large for this basic implementation.\n";
        cout << "Please enter at most 25 vertices.\n";

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
        cout << "Graph must be simple and undirected.\n";

        return 0;
    }

    cout << "\nEnter maximum solutions to display: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nSolution limit must be positive.\n";
        return 0;
    }

    displayGraph();

    cout << "\nSearching for maximum independent sets...\n";

    findMaximumIndependentSet(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
