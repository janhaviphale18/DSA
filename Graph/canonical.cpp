#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n;

struct CanonicalResult {

    string canonicalForm;

    vector<int> canonicalOrder;

    unsigned long long automorphismCount = 0;
};

// Read and validate a simple undirected graph
bool readGraph(
    vector<vector<bool>>& graph,
    const string& graphName
) {

    int edgeCount;

    cout << "\nEnter number of edges in "
         << graphName << ": ";

    cin >> edgeCount;

    if (edgeCount < 0 ||
        edgeCount > n * (n - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return false;
    }

    graph.assign(n, vector<bool>(n, false));

    cout << "\nEnter edges for " << graphName
         << " using vertices 0 to " << n - 1 << ":\n";

    for (int i = 0; i < edgeCount; i++) {

        int u, v;

        cout << "Edge " << i + 1 << ": ";

        cin >> u >> v;

        if (u < 0 || u >= n ||
            v < 0 || v >= n) {

            cout << "\nInvalid vertex number.\n";

            return false;
        }

        if (u == v) {

            cout << "\nSelf-loops are not allowed.\n";

            return false;
        }

        if (graph[u][v]) {

            cout << "\nDuplicate edge detected.\n";

            return false;
        }

        graph[u][v] = true;
        graph[v][u] = true;
    }

    return true;
}

// Generate a representation for a particular vertex ordering
string generateRepresentation(
    const vector<vector<bool>>& graph,
    const vector<int>& order
) {

    string representation = "";

    // Read the upper triangular part of the reordered matrix
    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (graph[order[i]][order[j]]) {

                representation += '1';
            }
            else {

                representation += '0';
            }
        }
    }

    return representation;
}

// Calculate canonical labeling by checking all permutations
CanonicalResult findCanonicalLabeling(
    const vector<vector<bool>>& graph
) {

    CanonicalResult result;

    vector<int> order(n);

    for (int i = 0; i < n; i++) {
        order[i] = i;
    }

    bool firstPermutation = true;

    // Generate every possible vertex ordering
    do {

        string currentForm =
            generateRepresentation(graph, order);

        // First permutation initializes the canonical form
        if (firstPermutation ||
            currentForm < result.canonicalForm) {

            result.canonicalForm = currentForm;

            result.canonicalOrder = order;

            result.automorphismCount = 1;

            firstPermutation = false;
        }

        // Another ordering produces the same minimum form
        else if (currentForm == result.canonicalForm) {

            result.automorphismCount++;
        }

    } while (next_permutation(order.begin(), order.end()));

    return result;
}

// Calculate vertex degrees
vector<int> calculateDegrees(
    const vector<vector<bool>>& graph
) {

    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (graph[i][j]) {
                degree[i]++;
            }
        }
    }

    return degree;
}

// Display graph edges
void displayGraph(
    const vector<vector<bool>>& graph,
    const string& graphName
) {

    cout << "\n========== " << graphName << " ==========\n";

    bool hasEdges = false;

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (graph[i][j]) {

                cout << "(" << i << ", " << j << ") ";

                hasEdges = true;
            }
        }
    }

    if (!hasEdges) {
        cout << "No edges";
    }

    cout << endl;
}

// Display degree sequence
void displayDegrees(
    const vector<int>& degree,
    const string& graphName
) {

    cout << "\n" << graphName << " degrees: ";

    for (int value : degree) {
        cout << value << " ";
    }

    cout << endl;
}

// Display canonical ordering
void displayOrder(
    const vector<int>& order,
    const string& graphName
) {

    cout << "\n" << graphName
         << " canonical vertex order: ";

    for (int vertex : order) {
        cout << vertex << " ";
    }

    cout << endl;
}

// Display canonical adjacency representation
void displayCanonicalForm(
    const string& canonicalForm,
    const string& graphName
) {

    cout << "\n" << graphName
         << " canonical form: ";

    cout << canonicalForm << endl;
}

// Display the canonical adjacency matrix
void displayCanonicalMatrix(
    const vector<vector<bool>>& graph,
    const vector<int>& order,
    const string& graphName
) {

    cout << "\n" << graphName
         << " canonical adjacency matrix:\n\n";

    cout << "    ";

    for (int vertex : order) {
        cout << vertex << " ";
    }

    cout << endl;

    for (int i = 0; i < n; i++) {

        cout << order[i] << "   ";

        for (int j = 0; j < n; j++) {

            cout << graph[order[i]][order[j]] << " ";
        }

        cout << endl;
    }
}

// Derive an isomorphism from canonical vertex orders
vector<int> generateMapping(
    const vector<int>& orderA,
    const vector<int>& orderB
) {

    vector<int> mapping(n, -1);

    for (int i = 0; i < n; i++) {

        // Vertices occupying the same canonical position
        // must correspond to each other
        mapping[orderA[i]] = orderB[i];
    }

    return mapping;
}

// Display mapping
void displayMapping(
    const vector<int>& mapping
) {

    cout << "\n========== ISOMORPHISM MAPPING ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "Graph A Vertex " << i
             << " -> Graph B Vertex "
             << mapping[i] << endl;
    }
}

// Display final results
void displayResults(
    const CanonicalResult& resultA,
    const CanonicalResult& resultB
) {

    cout << "\n========== CANONICAL LABELING RESULTS ==========\n";

    if (resultA.canonicalForm == resultB.canonicalForm) {

        cout << "\nThe graphs ARE isomorphic.\n";

        vector<int> mapping = generateMapping(
            resultA.canonicalOrder,
            resultB.canonicalOrder
        );

        displayMapping(mapping);

    } else {

        cout << "\nThe graphs are NOT isomorphic.\n";
    }

    cout << "\nGraph A automorphisms: "
         << resultA.automorphismCount << endl;

    cout << "Graph B automorphisms: "
         << resultB.automorphismCount << endl;
}

// Main function
int main() {

    cout << "===== GRAPH ISOMORPHISM USING CANONICAL LABELING =====\n";

    cout << "\nEnter number of vertices in both graphs: ";
    cin >> n;

    if (n <= 0 || n > 9) {

        cout << "\nNumber of vertices must be between 1 and 9.\n";

        return 0;
    }

    vector<vector<bool>> graphA;
    vector<vector<bool>> graphB;

    if (!readGraph(graphA, "Graph A")) {
        return 0;
    }

    if (!readGraph(graphB, "Graph B")) {
        return 0;
    }

    // Display original graphs
    displayGraph(graphA, "GRAPH A");
    displayGraph(graphB, "GRAPH B");

    // Calculate and display degrees
    vector<int> degreeA = calculateDegrees(graphA);
    vector<int> degreeB = calculateDegrees(graphB);

    displayDegrees(degreeA, "Graph A");
    displayDegrees(degreeB, "Graph B");

    cout << "\nGenerating canonical labeling for Graph A...\n";

    CanonicalResult resultA =
        findCanonicalLabeling(graphA);

    cout << "\nGenerating canonical labeling for Graph B...\n";

    CanonicalResult resultB =
        findCanonicalLabeling(graphB);

    // Display canonical representations
    displayOrder(
        resultA.canonicalOrder,
        "Graph A"
    );

    displayOrder(
        resultB.canonicalOrder,
        "Graph B"
    );

    displayCanonicalForm(
        resultA.canonicalForm,
        "Graph A"
    );

    displayCanonicalForm(
        resultB.canonicalForm,
        "Graph B"
    );

    displayCanonicalMatrix(
        graphA,
        resultA.canonicalOrder,
        "Graph A"
    );

    displayCanonicalMatrix(
        graphB,
        resultB.canonicalOrder,
        "Graph B"
    );

    // Display isomorphism result
    displayResults(resultA, resultB);

    return 0;
}
