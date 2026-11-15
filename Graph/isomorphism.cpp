#include <iostream>
#include <vector>
using namespace std;

int n1, n2;

vector<vector<int>> graph1;
vector<vector<int>> graph2;

vector<int> degree1;
vector<int> degree2;

// Mapping from vertices of graph 1 to graph 2
vector<int> mapping;

// Track vertices already assigned in graph 2
vector<bool> assigned;

// Count recursive calls
long long recursiveCalls = 0;

// Calculate degree of every vertex
void calculateDegrees(
    const vector<vector<int>>& graph,
    vector<int>& degree
) {

    int n = graph.size();

    degree.resize(n);

    for (int i = 0; i < n; i++) {

        int count = 0;

        for (int j = 0; j < n; j++) {

            if (graph[i][j] == 1) {
                count++;
            }
        }

        degree[i] = count;
    }
}

// Check whether the partial mapping preserves adjacency
bool isCompatible(int vertex1, int vertex2) {

    for (int i = 0; i < vertex1; i++) {

        int mappedVertex = mapping[i];

        if (graph1[vertex1][i] !=
            graph2[vertex2][mappedVertex]) {

            return false;
        }
    }

    return true;
}

// Recursive backtracking function
bool findIsomorphism(int vertex) {

    recursiveCalls++;

    // All vertices have been mapped
    if (vertex == n1) {
        return true;
    }

    // Try every possible vertex in graph 2
    for (int candidate = 0; candidate < n2; candidate++) {

        // Candidate must not already be assigned
        if (assigned[candidate]) {
            continue;
        }

        // Corresponding vertices must have equal degrees
        if (degree1[vertex] != degree2[candidate]) {
            continue;
        }

        // Check adjacency with previously mapped vertices
        if (!isCompatible(vertex, candidate)) {
            continue;
        }

        // Make the mapping
        mapping[vertex] = candidate;
        assigned[candidate] = true;

        // Explore the next vertex
        if (findIsomorphism(vertex + 1)) {
            return true;
        }

        // Backtrack
        mapping[vertex] = -1;
        assigned[candidate] = false;
    }

    return false;
}

// Check whether two graphs are isomorphic
bool areIsomorphic() {

    // Different vertex counts
    if (n1 != n2) {
        return false;
    }

    // Different edge counts
    long long edges1 = 0;
    long long edges2 = 0;

    for (int i = 0; i < n1; i++) {

        for (int j = i + 1; j < n1; j++) {

            edges1 += graph1[i][j];
            edges2 += graph2[i][j];
        }
    }

    if (edges1 != edges2) {
        return false;
    }

    // Calculate vertex degrees
    calculateDegrees(graph1, degree1);
    calculateDegrees(graph2, degree2);

    // Compare sorted degree sequences
    vector<int> sortedDegree1 = degree1;
    vector<int> sortedDegree2 = degree2;

    for (int i = 0; i < n1; i++) {

        for (int j = i + 1; j < n1; j++) {

            if (sortedDegree1[i] > sortedDegree1[j]) {
                swap(sortedDegree1[i], sortedDegree1[j]);
            }

            if (sortedDegree2[i] > sortedDegree2[j]) {
                swap(sortedDegree2[i], sortedDegree2[j]);
            }
        }
    }

    if (sortedDegree1 != sortedDegree2) {
        return false;
    }

    // Initialize mapping structures
    mapping.assign(n1, -1);
    assigned.assign(n2, false);

    // Start backtracking
    return findIsomorphism(0);
}

// Display adjacency matrix
void displayGraph(
    const vector<vector<int>>& graph,
    const string& name
) {

    cout << "\n" << name << ":\n";

    for (int i = 0; i < (int)graph.size(); i++) {

        for (int j = 0; j < (int)graph.size(); j++) {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }
}

// Display vertex mapping
void displayMapping() {

    cout << "\n========== VERTEX MAPPING ==========\n";

    for (int i = 0; i < n1; i++) {

        cout << "Vertex " << i
             << " in Graph 1 -> Vertex "
             << mapping[i] << " in Graph 2\n";
    }
}

int main() {

    cout << "===== GRAPH ISOMORPHISM CHECKING =====\n";

    cout << "\nEnter number of vertices in Graph 1: ";
    cin >> n1;

    cout << "Enter number of vertices in Graph 2: ";
    cin >> n2;

    if (n1 <= 0 || n2 <= 0) {

        cout << "\nNumber of vertices must be positive.\n";
        return 0;
    }

    if (n1 > 10 || n2 > 10) {

        cout << "\nGraph size is too large for this basic implementation.\n";
        cout << "Please enter at most 10 vertices per graph.\n";
        return 0;
    }

    graph1.resize(n1, vector<int>(n1));
    graph2.resize(n2, vector<int>(n2));

    cout << "\nEnter adjacency matrix of Graph 1:\n";

    for (int i = 0; i < n1; i++) {

        for (int j = 0; j < n1; j++) {

            cin >> graph1[i][j];

            if (graph1[i][j] != 0 && graph1[i][j] != 1) {

                cout << "\nInvalid adjacency matrix value.\n";
                return 0;
            }
        }
    }

    cout << "\nEnter adjacency matrix of Graph 2:\n";

    for (int i = 0; i < n2; i++) {

        for (int j = 0; j < n2; j++) {

            cin >> graph2[i][j];

            if (graph2[i][j] != 0 && graph2[i][j] != 1) {

                cout << "\nInvalid adjacency matrix value.\n";
                return 0;
            }
        }
    }

    // Validate simple undirected graph matrices
    for (int i = 0; i < n1; i++) {

        if (graph1[i][i] != 0) {

            cout << "\nGraph 1 must not contain self-loops.\n";
            return 0;
        }

        for (int j = 0; j < n1; j++) {

            if (graph1[i][j] != graph1[j][i]) {

                cout << "\nGraph 1 must be undirected.\n";
                return 0;
            }
        }
    }

    for (int i = 0; i < n2; i++) {

        if (graph2[i][i] != 0) {

            cout << "\nGraph 2 must not contain self-loops.\n";
            return 0;
        }

        for (int j = 0; j < n2; j++) {

            if (graph2[i][j] != graph2[j][i]) {

                cout << "\nGraph 2 must be undirected.\n";
                return 0;
            }
        }
    }

    displayGraph(graph1, "GRAPH 1");
    displayGraph(graph2, "GRAPH 2");

    cout << "\nChecking graph isomorphism...\n";

    if (areIsomorphic()) {

        cout << "\nThe graphs are ISOMORPHIC.\n";

        displayMapping();

    } else {

        cout << "\nThe graphs are NOT ISOMORPHIC.\n";
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
