#include <iostream>
#include <vector>
using namespace std;

int n;

vector<vector<int>> graph;

vector<int> currentClique;
vector<int> maximumClique;

vector<vector<int>> maximumCliques;

long long recursiveCalls = 0;

// Check whether a vertex is connected to every vertex
// already present in the current clique
bool canAddVertex(int vertex) {

    for (int existingVertex : currentClique) {

        if (graph[vertex][existingVertex] == 0) {
            return false;
        }
    }

    return true;
}

// Recursive backtracking function
void findMaximumClique(int start) {

    recursiveCalls++;

    // A larger clique has been found
    if (currentClique.size() > maximumClique.size()) {

        maximumClique = currentClique;

        maximumCliques.clear();
        maximumCliques.push_back(currentClique);
    }

    // Another maximum clique of the same size
    else if (currentClique.size() == maximumClique.size()) {

        // Avoid storing duplicate cliques
        if (maximumCliques.empty() ||
            maximumCliques.back() != currentClique) {

            maximumCliques.push_back(currentClique);
        }
    }

    // Try remaining vertices
    for (int vertex = start; vertex < n; vertex++) {

        // A clique cannot contain a vertex that
        // is not adjacent to every existing member
        if (canAddVertex(vertex)) {

            // Include the vertex
            currentClique.push_back(vertex);

            // Explore the next vertices
            findMaximumClique(vertex + 1);

            // Backtrack
            currentClique.pop_back();
        }
    }
}

// Display a clique
void displayClique(const vector<int>& clique) {

    cout << "{ ";

    for (int i = 0; i < (int)clique.size(); i++) {

        cout << clique[i];

        if (i != (int)clique.size() - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display all maximum cliques
void displayResults() {

    cout << "\n========== MAXIMUM CLIQUE ==========\n";

    cout << "\nMaximum clique size: "
         << maximumClique.size() << endl;

    cout << "\nOne maximum clique: ";

    displayClique(maximumClique);

    cout << "\n\nAll maximum cliques:\n";

    for (int i = 0; i < (int)maximumCliques.size(); i++) {

        cout << "Clique " << i + 1 << ": ";

        displayClique(maximumCliques[i]);

        cout << endl;
    }

    cout << "\nTotal maximum cliques found: "
         << maximumCliques.size() << endl;
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

        // Self-loops are not allowed
        if (graph[i][i] != 0) {
            return false;
        }

        // Matrix must be symmetric
        for (int j = 0; j < n; j++) {

            if (graph[i][j] != graph[j][i]) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    cout << "===== MAXIMUM CLIQUE USING BACKTRACKING =====\n";

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

    displayGraph();

    cout << "\nSearching for maximum clique...\n";

    findMaximumClique(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
