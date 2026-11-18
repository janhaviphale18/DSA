#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int verticesA;
int verticesB;

long long maxSolutions;
long long totalMappings = 0;
long long recursiveCalls = 0;

int maximumSize = 0;

bool storageLimitReached = false;

vector<vector<bool>> graphA;
vector<vector<bool>> graphB;

vector<int> degreeA;
vector<int> degreeB;

vector<int> mapping;
vector<bool> used;

vector<int> processingOrder;

vector<vector<int>> bestMappings;

// Calculate degrees of a graph
vector<int> calculateDegrees(
    const vector<vector<bool>>& graph,
    int vertices
) {

    vector<int> degree(vertices, 0);

    for (int i = 0; i < vertices; i++) {

        for (int j = 0; j < vertices; j++) {

            if (graph[i][j]) {
                degree[i]++;
            }
        }
    }

    return degree;
}

// Check whether a mapping preserves both edges and non-edges
bool isCompatible(int vertexA, int vertexB) {

    for (int previousA = 0;
         previousA < verticesA;
         previousA++) {

        if (mapping[previousA] == -1) {
            continue;
        }

        int previousB = mapping[previousA];

        // Induced subgraph condition:
        // Adjacency must be exactly preserved
        if (graphA[vertexA][previousA] !=
            graphB[vertexB][previousB]) {

            return false;
        }
    }

    return true;
}

// Store a new maximum solution
void storeSolution(int currentSize) {

    if (currentSize > maximumSize) {

        maximumSize = currentSize;

        totalMappings = 0;

        bestMappings.clear();

        storageLimitReached = false;
    }

    if (currentSize == maximumSize) {

        totalMappings++;

        if ((long long)bestMappings.size() < maxSolutions) {

            bestMappings.push_back(mapping);

        } else {

            storageLimitReached = true;
        }
    }
}

// Prepare vertex processing order
void prepareProcessingOrder() {

    processingOrder.resize(verticesA);

    for (int i = 0; i < verticesA; i++) {
        processingOrder[i] = i;
    }

    // Process higher-degree vertices first
    sort(
        processingOrder.begin(),
        processingOrder.end(),
        [](int a, int b) {

            if (degreeA[a] != degreeA[b]) {
                return degreeA[a] > degreeA[b];
            }

            return a < b;
        }
    );
}

// Recursive maximum common induced subgraph search
void findMaximumCommonSubgraph(
    int index,
    int currentSize
) {

    recursiveCalls++;

    // All vertices of Graph A have been considered
    if (index == verticesA) {

        storeSolution(currentSize);

        return;
    }

    // Branch and bound:
    // Even if all remaining vertices are mapped,
    // this branch cannot beat the current maximum
    int remaining = verticesA - index;

    if (currentSize + remaining < maximumSize) {
        return;
    }

    int u = processingOrder[index];

    // Option 1: Map the current vertex to Graph B
    for (int v = 0; v < verticesB; v++) {

        // Host vertex must not already be used
        if (used[v]) {
            continue;
        }

        // Check induced adjacency consistency
        if (!isCompatible(u, v)) {
            continue;
        }

        // Assign mapping
        mapping[u] = v;

        used[v] = true;

        // Explore the next vertex
        findMaximumCommonSubgraph(
            index + 1,
            currentSize + 1
        );

        // Backtracking
        mapping[u] = -1;

        used[v] = false;
    }

    // Option 2: Exclude the current vertex from
    // the common induced subgraph
    mapping[u] = -1;

    findMaximumCommonSubgraph(
        index + 1,
        currentSize
    );
}

// Read and validate a simple undirected graph
bool readGraph(
    vector<vector<bool>>& graph,
    int vertices,
    const string& graphName
) {

    int edgeCount;

    cout << "\nEnter number of edges in "
         << graphName << ": ";

    cin >> edgeCount;

    if (edgeCount < 0 ||
        edgeCount > vertices * (vertices - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return false;
    }

    graph.assign(
        vertices,
        vector<bool>(vertices, false)
    );

    cout << "\nEnter edges for " << graphName
         << " using vertices 0 to "
         << vertices - 1 << ":\n";

    for (int i = 0; i < edgeCount; i++) {

        int u, v;

        cout << "Edge " << i + 1 << ": ";

        cin >> u >> v;

        if (u < 0 || u >= vertices ||
            v < 0 || v >= vertices) {

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

// Display graph edges
void displayGraph(
    const vector<vector<bool>>& graph,
    int vertices,
    const string& graphName
) {

    cout << "\n========== " << graphName << " ==========\n";

    bool hasEdges = false;

    for (int i = 0; i < vertices; i++) {

        for (int j = i + 1; j < vertices; j++) {

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

// Display vertex degrees
void displayDegrees(
    const vector<int>& degree,
    int vertices,
    const string& graphName
) {

    cout << "\n" << graphName << " degrees:\n";

    for (int i = 0; i < vertices; i++) {

        cout << "Vertex " << i
             << " -> Degree " << degree[i] << endl;
    }
}

// Display one mapping
void displayMapping(const vector<int>& result) {

    cout << "{ ";

    for (int i = 0; i < verticesA; i++) {

        if (result[i] != -1) {

            cout << i << " -> " << result[i];

            cout << ", ";
        }
    }

    cout << "}";
}

// Display maximum common subgraph results
void displayResults() {

    cout << "\n========== MAXIMUM COMMON SUBGRAPH RESULTS ==========\n";

    cout << "\nMaximum common induced subgraph size: "
         << maximumSize << endl;

    cout << "\nMaximum mappings found:\n";

    for (int i = 0;
         i < (int)bestMappings.size();
         i++) {

        cout << "\nMapping " << i + 1 << ": ";

        displayMapping(bestMappings[i]);

        cout << endl;
    }

    cout << "\nTotal maximum mappings found: "
         << totalMappings << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached. "
             << "Some maximum mappings were not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== MAXIMUM COMMON INDUCED SUBGRAPH =====\n";

    cout << "\nEnter number of vertices in Graph A: ";
    cin >> verticesA;

    if (verticesA <= 0 || verticesA > 12) {

        cout << "\nGraph A must have between 1 and 12 vertices.\n";

        return 0;
    }

    cout << "\nEnter number of vertices in Graph B: ";
    cin >> verticesB;

    if (verticesB <= 0 || verticesB > 12) {

        cout << "\nGraph B must have between 1 and 12 vertices.\n";

        return 0;
    }

    if (!readGraph(graphA, verticesA, "Graph A")) {
        return 0;
    }

    if (!readGraph(graphB, verticesB, "Graph B")) {
        return 0;
    }

    cout << "\nEnter maximum mappings to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph(graphA, verticesA, "GRAPH A");

    displayGraph(graphB, verticesB, "GRAPH B");

    // Calculate degrees
    degreeA = calculateDegrees(graphA, verticesA);

    degreeB = calculateDegrees(graphB, verticesB);

    displayDegrees(degreeA, verticesA, "Graph A");

    displayDegrees(degreeB, verticesB, "Graph B");

    // Prepare search order
    prepareProcessingOrder();

    // Initialize mapping structures
    mapping.assign(verticesA, -1);

    used.assign(verticesB, false);

    cout << "\nSearching for the maximum common induced subgraph...\n";

    findMaximumCommonSubgraph(0, 0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
