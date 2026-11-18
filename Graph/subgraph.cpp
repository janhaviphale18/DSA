#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int patternVertices;
int hostVertices;

long long maxSolutions;
long long totalMappings = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

vector<vector<bool>> patternGraph;
vector<vector<bool>> hostGraph;

vector<int> patternDegree;
vector<int> hostDegree;

vector<int> mapping;
vector<bool> used;

vector<int> processingOrder;

vector<vector<int>> validMappings;

// Calculate vertex degrees
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

// Check whether a host vertex can be assigned to a pattern vertex
bool isCompatible(int patternVertex, int hostVertex) {

    // A host vertex must have enough incident edges
    if (hostDegree[hostVertex] <
        patternDegree[patternVertex]) {

        return false;
    }

    // Every edge to an already mapped pattern vertex
    // must also exist in the host graph
    for (int previous = 0;
         previous < patternVertices;
         previous++) {

        if (mapping[previous] == -1) {
            continue;
        }

        int mappedHost = mapping[previous];

        if (patternGraph[patternVertex][previous] &&
            !hostGraph[hostVertex][mappedHost]) {

            return false;
        }
    }

    return true;
}

// Forward checking:
// Every remaining pattern vertex must have
// at least one possible unused host candidate
bool forwardCheck() {

    for (int u = 0; u < patternVertices; u++) {

        if (mapping[u] != -1) {
            continue;
        }

        bool candidateExists = false;

        for (int v = 0; v < hostVertices; v++) {

            if (used[v]) {
                continue;
            }

            if (isCompatible(u, v)) {

                candidateExists = true;

                break;
            }
        }

        if (!candidateExists) {
            return false;
        }
    }

    return true;
}

// Prepare pattern vertex processing order
void prepareProcessingOrder() {

    processingOrder.resize(patternVertices);

    for (int i = 0; i < patternVertices; i++) {
        processingOrder[i] = i;
    }

    // Process vertices with higher degrees first
    sort(
        processingOrder.begin(),
        processingOrder.end(),
        [](int a, int b) {

            if (patternDegree[a] != patternDegree[b]) {

                return patternDegree[a] >
                       patternDegree[b];
            }

            return a < b;
        }
    );
}

// Store a valid mapping
void storeMapping() {

    totalMappings++;

    if ((long long)validMappings.size() < maxSolutions) {

        validMappings.push_back(mapping);

    } else {

        storageLimitReached = true;
    }
}

// Recursive subgraph isomorphism search
void findSubgraphMappings(int index) {

    recursiveCalls++;

    // All pattern vertices have been mapped
    if (index == patternVertices) {

        storeMapping();

        return;
    }

    int u = processingOrder[index];

    // Try every unused host vertex
    for (int v = 0; v < hostVertices; v++) {

        if (used[v]) {
            continue;
        }

        // Check structural compatibility
        if (!isCompatible(u, v)) {
            continue;
        }

        // Assign mapping
        mapping[u] = v;

        used[v] = true;

        // Check whether remaining vertices
        // still have possible candidates
        if (forwardCheck()) {

            findSubgraphMappings(index + 1);
        }

        // Backtracking
        mapping[u] = -1;

        used[v] = false;
    }
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

    graph.assign(vertices, vector<bool>(vertices, false));

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

    for (int i = 0; i < patternVertices; i++) {

        cout << i << " -> " << result[i];

        if (i != patternVertices - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display all valid mappings
void displayResults() {

    cout << "\n========== SUBGRAPH ISOMORPHISM RESULTS ==========\n";

    if (totalMappings == 0) {

        cout << "\nGraph A is NOT a subgraph of Graph B.\n";

        return;
    }

    cout << "\nGraph A IS a subgraph of Graph B.\n";

    cout << "\nValid vertex mappings:\n";

    for (int i = 0;
         i < (int)validMappings.size();
         i++) {

        cout << "\nMapping " << i + 1 << ": ";

        displayMapping(validMappings[i]);

        cout << endl;
    }

    cout << "\nTotal valid mappings found: "
         << totalMappings << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached. "
             << "Some mappings were not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== SUBGRAPH ISOMORPHISM =====\n";

    cout << "\nEnter number of vertices in Pattern Graph A: ";
    cin >> patternVertices;

    if (patternVertices <= 0 || patternVertices > 12) {

        cout << "\nPattern graph vertices must be between 1 and 12.\n";

        return 0;
    }

    cout << "\nEnter number of vertices in Host Graph B: ";
    cin >> hostVertices;

    if (hostVertices < patternVertices ||
        hostVertices > 12) {

        cout << "\nHost graph must have at least "
             << patternVertices
             << " vertices and at most 12 vertices.\n";

        return 0;
    }

    if (!readGraph(
            patternGraph,
            patternVertices,
            "Pattern Graph A")) {

        return 0;
    }

    if (!readGraph(
            hostGraph,
            hostVertices,
            "Host Graph B")) {

        return 0;
    }

    cout << "\nEnter maximum mappings to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph(
        patternGraph,
        patternVertices,
        "PATTERN GRAPH A"
    );

    displayGraph(
        hostGraph,
        hostVertices,
        "HOST GRAPH B"
    );

    // Calculate degrees
    patternDegree = calculateDegrees(
        patternGraph,
        patternVertices
    );

    hostDegree = calculateDegrees(
        hostGraph,
        hostVertices
    );

    displayDegrees(
        patternDegree,
        patternVertices,
        "Pattern Graph A"
    );

    displayDegrees(
        hostDegree,
        hostVertices,
        "Host Graph B"
    );

    // A pattern cannot have more edges than the host
    int patternEdgeCount = 0;
    int hostEdgeCount = 0;

    for (int degree : patternDegree) {
        patternEdgeCount += degree;
    }

    for (int degree : hostDegree) {
        hostEdgeCount += degree;
    }

    if (patternEdgeCount > hostEdgeCount) {

        cout << "\nPattern graph has more edges than "
             << "the host graph.\n";

        cout << "No subgraph mapping is possible.\n";

        return 0;
    }

    // Prepare vertex search order
    prepareProcessingOrder();

    mapping.assign(patternVertices, -1);

    used.assign(hostVertices, false);

    cout << "\nStarting backtracking with structural pruning...\n";

    findSubgraphMappings(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
