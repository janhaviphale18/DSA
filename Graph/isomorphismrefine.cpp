#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int n;

long long maxSolutions;
long long totalMappings = 0;

vector<vector<bool>> graphA;
vector<vector<bool>> graphB;

vector<int> colorA;
vector<int> colorB;

vector<int> mapping;
vector<bool> used;

vector<int> processingOrder;

vector<vector<int>> validMappings;

bool storageLimitReached = false;

long long recursiveCalls = 0;

// Calculate the degree of every vertex
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

// Assign common color IDs to signatures from both graphs
void compressSignatures(
    const vector<vector<int>>& signaturesA,
    const vector<vector<int>>& signaturesB,
    vector<int>& newColorA,
    vector<int>& newColorB
) {

    map<vector<int>, int> colorIDs;

    newColorA.resize(n);
    newColorB.resize(n);

    int nextID = 0;

    // Process signatures of the first graph
    for (int i = 0; i < n; i++) {

        auto result = colorIDs.emplace(
            signaturesA[i],
            nextID
        );

        if (result.second) {
            nextID++;
        }

        newColorA[i] = result.first->second;
    }

    // Process signatures of the second graph
    // using the same color ID mapping
    for (int i = 0; i < n; i++) {

        auto result = colorIDs.emplace(
            signaturesB[i],
            nextID
        );

        if (result.second) {
            nextID++;
        }

        newColorB[i] = result.first->second;
    }
}

// Count the number of distinct colors
int countColors(
    const vector<int>& colors
) {

    vector<int> uniqueColors = colors;

    sort(uniqueColors.begin(), uniqueColors.end());

    uniqueColors.erase(
        unique(uniqueColors.begin(), uniqueColors.end()),
        uniqueColors.end()
    );

    return (int)uniqueColors.size();
}

// Compare color class frequencies
bool sameColorDistribution() {

    vector<int> frequencyA(n, 0);
    vector<int> frequencyB(n, 0);

    for (int color : colorA) {
        frequencyA[color]++;
    }

    for (int color : colorB) {
        frequencyB[color]++;
    }

    return frequencyA == frequencyB;
}

// Perform degree-based initial classification
void initializeColors() {

    vector<int> degreeA = calculateDegrees(graphA);
    vector<int> degreeB = calculateDegrees(graphB);

    vector<vector<int>> signaturesA(n);
    vector<vector<int>> signaturesB(n);

    for (int i = 0; i < n; i++) {

        signaturesA[i] = {degreeA[i]};
        signaturesB[i] = {degreeB[i]};
    }

    compressSignatures(
        signaturesA,
        signaturesB,
        colorA,
        colorB
    );
}

// Perform iterative neighborhood refinement
bool refineNeighborhoods() {

    initializeColors();

    // Degree distributions must match
    if (!sameColorDistribution()) {
        return false;
    }

    for (int iteration = 0; iteration < n; iteration++) {

        vector<vector<int>> signaturesA(n);
        vector<vector<int>> signaturesB(n);

        // Construct signatures for Graph A
        for (int i = 0; i < n; i++) {

            vector<int> neighborColors;

            for (int j = 0; j < n; j++) {

                if (graphA[i][j]) {
                    neighborColors.push_back(colorA[j]);
                }
            }

            sort(neighborColors.begin(), neighborColors.end());

            signaturesA[i].push_back(colorA[i]);

            for (int color : neighborColors) {
                signaturesA[i].push_back(color);
            }
        }

        // Construct signatures for Graph B
        for (int i = 0; i < n; i++) {

            vector<int> neighborColors;

            for (int j = 0; j < n; j++) {

                if (graphB[i][j]) {
                    neighborColors.push_back(colorB[j]);
                }
            }

            sort(neighborColors.begin(), neighborColors.end());

            signaturesB[i].push_back(colorB[i]);

            for (int color : neighborColors) {
                signaturesB[i].push_back(color);
            }
        }

        vector<int> newColorA;
        vector<int> newColorB;

        compressSignatures(
            signaturesA,
            signaturesB,
            newColorA,
            newColorB
        );

        int oldColorCount = countColors(colorA);

        int newColorCount = countColors(newColorA);

        colorA = newColorA;
        colorB = newColorB;

        // A mismatch proves the graphs are not isomorphic
        if (!sameColorDistribution()) {
            return false;
        }

        // No additional classes were created.
        // Refinement has stabilized.
        if (newColorCount == oldColorCount) {
            break;
        }
    }

    return true;
}

// Prepare vertex processing order
void prepareProcessingOrder() {

    vector<int> frequency(n, 0);

    for (int color : colorA) {
        frequency[color]++;
    }

    vector<int> degree = calculateDegrees(graphA);

    processingOrder.resize(n);

    for (int i = 0; i < n; i++) {
        processingOrder[i] = i;
    }

    // Process vertices with rarer colors first
    // and higher degree first when frequencies tie
    sort(
        processingOrder.begin(),
        processingOrder.end(),
        [&](int a, int b) {

            if (frequency[colorA[a]] !=
                frequency[colorA[b]]) {

                return frequency[colorA[a]] <
                       frequency[colorA[b]];
            }

            if (degree[a] != degree[b]) {
                return degree[a] > degree[b];
            }

            return a < b;
        }
    );
}

// Check whether a candidate mapping is consistent
bool isCompatible(int vertexA, int vertexB) {

    // Compare adjacency with all previously mapped vertices
    for (int previousA = 0;
         previousA < n;
         previousA++) {

        if (mapping[previousA] == -1) {
            continue;
        }

        int previousB = mapping[previousA];

        // Both edges and non-edges must be preserved
        if (graphA[vertexA][previousA] !=
            graphB[vertexB][previousB]) {

            return false;
        }
    }

    return true;
}

// Store a valid isomorphism
void storeMapping() {

    totalMappings++;

    if ((long long)validMappings.size() < maxSolutions) {

        validMappings.push_back(mapping);

    } else {

        storageLimitReached = true;
    }
}

// Recursive graph isomorphism checking
void findIsomorphisms(int index) {

    recursiveCalls++;

    // All vertices have been mapped
    if (index == n) {

        storeMapping();

        return;
    }

    int vertexA = processingOrder[index];

    // Try every unused vertex in Graph B
    for (int vertexB = 0; vertexB < n; vertexB++) {

        // A vertex can only map to the same refined color
        if (colorA[vertexA] != colorB[vertexB]) {
            continue;
        }

        // Each vertex in Graph B can be used only once
        if (used[vertexB]) {
            continue;
        }

        // Check structural consistency
        if (!isCompatible(vertexA, vertexB)) {
            continue;
        }

        // Make the mapping
        mapping[vertexA] = vertexB;

        used[vertexB] = true;

        // Explore the next vertex
        findIsomorphisms(index + 1);

        // Backtracking
        mapping[vertexA] = -1;

        used[vertexB] = false;
    }
}

// Read and validate an undirected graph
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

// Display graph edges
void displayGraph(
    const vector<vector<bool>>& graph,
    const string& graphName
) {

    cout << "\n========== " << graphName << " ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (graph[i][j]) {

                cout << "(" << i << ", " << j << ") ";
            }
        }
    }

    cout << endl;
}

// Display degree sequence
void displayDegrees(
    const vector<vector<bool>>& graph,
    const string& graphName
) {

    vector<int> degree = calculateDegrees(graph);

    cout << "\n" << graphName << " degrees: ";

    for (int value : degree) {
        cout << value << " ";
    }

    cout << endl;
}

// Display refined colors
void displayColors() {

    cout << "\n========== REFINED VERTEX CLASSES ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "Graph A Vertex " << i
             << " -> Color " << colorA[i] << endl;
    }

    for (int i = 0; i < n; i++) {

        cout << "Graph B Vertex " << i
             << " -> Color " << colorB[i] << endl;
    }
}

// Display one mapping
void displayMapping(const vector<int>& result) {

    cout << "{ ";

    for (int i = 0; i < n; i++) {

        cout << i << " -> " << result[i];

        if (i != n - 1) {
            cout << ", ";
        }
    }

    cout << " }";
}

// Display all valid mappings
void displayResults() {

    cout << "\n========== GRAPH ISOMORPHISM RESULTS ==========\n";

    if (totalMappings == 0) {

        cout << "\nThe graphs are NOT isomorphic.\n";

        return;
    }

    cout << "\nThe graphs ARE isomorphic.\n";

    cout << "\nStored valid mappings:\n";

    for (int i = 0;
         i < (int)validMappings.size();
         i++) {

        cout << "\nMapping " << i + 1 << ": ";

        displayMapping(validMappings[i]);

        cout << endl;
    }

    cout << "\nTotal valid isomorphisms found: "
         << totalMappings << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional valid mappings were found "
             << "but not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== GRAPH ISOMORPHISM WITH REFINEMENT =====\n";

    cout << "\nEnter number of vertices in both graphs: ";
    cin >> n;

    if (n <= 0 || n > 12) {

        cout << "\nNumber of vertices must be between 1 and 12.\n";

        return 0;
    }

    if (!readGraph(graphA, "Graph A")) {
        return 0;
    }

    if (!readGraph(graphB, "Graph B")) {
        return 0;
    }

    cout << "\nEnter maximum isomorphisms to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph(graphA, "GRAPH A EDGES");

    displayGraph(graphB, "GRAPH B EDGES");

    displayDegrees(graphA, "Graph A");
    displayDegrees(graphB, "Graph B");

    cout << "\nPerforming degree and neighborhood refinement...\n";

    bool refinementPossible = refineNeighborhoods();

    if (!refinementPossible) {

        cout << "\nThe graphs are NOT isomorphic.\n";

        cout << "Their refined vertex class distributions differ.\n";

        return 0;
    }

    displayColors();

    prepareProcessingOrder();

    mapping.assign(n, -1);

    used.assign(n, false);

    cout << "\nStarting backtracking...\n";

    findIsomorphisms(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
