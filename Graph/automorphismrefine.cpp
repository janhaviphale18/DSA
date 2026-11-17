#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int n;

long long maxSolutions;
long long totalAutomorphisms = 0;
long long recursiveCalls = 0;

bool storageLimitReached = false;

vector<vector<bool>> graph;

vector<int> colors;
vector<int> mapping;
vector<bool> used;

vector<int> processingOrder;

vector<vector<int>> automorphisms;

// Calculate degree of every vertex
vector<int> calculateDegrees() {

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

// Assign common color IDs to signatures
void assignColors(
    const vector<vector<int>>& signatures,
    vector<int>& newColors
) {

    map<vector<int>, int> colorIDs;

    newColors.resize(n);

    int nextID = 0;

    for (int i = 0; i < n; i++) {

        auto result = colorIDs.emplace(
            signatures[i],
            nextID
        );

        if (result.second) {
            nextID++;
        }

        newColors[i] = result.first->second;
    }
}

// Count distinct colors
int countColors(const vector<int>& values) {

    vector<int> uniqueValues = values;

    sort(uniqueValues.begin(), uniqueValues.end());

    uniqueValues.erase(
        unique(uniqueValues.begin(), uniqueValues.end()),
        uniqueValues.end()
    );

    return (int)uniqueValues.size();
}

// Perform initial degree-based classification
void initializeColors() {

    vector<int> degree = calculateDegrees();

    vector<vector<int>> signatures(n);

    for (int i = 0; i < n; i++) {

        signatures[i] = {degree[i]};
    }

    assignColors(signatures, colors);
}

// Perform iterative neighborhood refinement
void refineColors() {

    initializeColors();

    for (int iteration = 0; iteration < n; iteration++) {

        vector<vector<int>> signatures(n);

        for (int i = 0; i < n; i++) {

            vector<int> neighborColors;

            for (int j = 0; j < n; j++) {

                if (graph[i][j]) {
                    neighborColors.push_back(colors[j]);
                }
            }

            sort(
                neighborColors.begin(),
                neighborColors.end()
            );

            signatures[i].push_back(colors[i]);

            for (int color : neighborColors) {

                signatures[i].push_back(color);
            }
        }

        vector<int> newColors;

        assignColors(signatures, newColors);

        int oldCount = countColors(colors);

        int newCount = countColors(newColors);

        colors = newColors;

        // Stop when no additional color classes are created
        if (oldCount == newCount) {
            break;
        }
    }
}

// Prepare vertex processing order
void prepareProcessingOrder() {

    vector<int> frequency(n, 0);

    vector<int> degree = calculateDegrees();

    for (int color : colors) {
        frequency[color]++;
    }

    processingOrder.resize(n);

    for (int i = 0; i < n; i++) {
        processingOrder[i] = i;
    }

    // Process vertices from smaller color classes first
    sort(
        processingOrder.begin(),
        processingOrder.end(),
        [&](int a, int b) {

            if (frequency[colors[a]] != frequency[colors[b]]) {

                return frequency[colors[a]] <
                       frequency[colors[b]];
            }

            if (degree[a] != degree[b]) {

                return degree[a] > degree[b];
            }

            return a < b;
        }
    );
}

// Check whether a candidate mapping preserves adjacency
bool isCompatible(int vertexA, int vertexB) {

    for (int previousA = 0;
         previousA < n;
         previousA++) {

        if (mapping[previousA] == -1) {
            continue;
        }

        int previousB = mapping[previousA];

        if (graph[vertexA][previousA] !=
            graph[vertexB][previousB]) {

            return false;
        }
    }

    return true;
}

// Store a valid automorphism
void storeAutomorphism() {

    totalAutomorphisms++;

    if ((long long)automorphisms.size() < maxSolutions) {

        automorphisms.push_back(mapping);

    } else {

        storageLimitReached = true;
    }
}

// Find all graph automorphisms
void findAutomorphisms(int index) {

    recursiveCalls++;

    // Every vertex has been mapped
    if (index == n) {

        storeAutomorphism();

        return;
    }

    int vertex = processingOrder[index];

    // Try every unused candidate vertex
    for (int candidate = 0;
         candidate < n;
         candidate++) {

        // Refined colors must match
        if (colors[vertex] != colors[candidate]) {
            continue;
        }

        // Mapping must be one-to-one
        if (used[candidate]) {
            continue;
        }

        // Check adjacency with already mapped vertices
        if (!isCompatible(vertex, candidate)) {
            continue;
        }

        // Assign candidate
        mapping[vertex] = candidate;

        used[candidate] = true;

        // Explore next vertex
        findAutomorphisms(index + 1);

        // Backtracking
        mapping[vertex] = -1;

        used[candidate] = false;
    }
}

// Read graph
bool readGraph() {

    int edgeCount;

    cout << "\nEnter number of edges: ";
    cin >> edgeCount;

    if (edgeCount < 0 ||
        edgeCount > n * (n - 1) / 2) {

        cout << "\nInvalid number of edges.\n";

        return false;
    }

    graph.assign(n, vector<bool>(n, false));

    cout << "\nEnter edges using vertices 0 to "
         << n - 1 << ":\n";

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

// Display graph
void displayGraph() {

    cout << "\n========== GRAPH EDGES ==========\n";

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

// Display degree of every vertex
void displayDegrees() {

    vector<int> degree = calculateDegrees();

    cout << "\n========== VERTEX DEGREES ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "Vertex " << i
             << " -> Degree " << degree[i] << endl;
    }
}

// Display refined colors
void displayColors() {

    cout << "\n========== REFINED VERTEX CLASSES ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "Vertex " << i
             << " -> Color " << colors[i] << endl;
    }
}

// Display one automorphism
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

// Display all automorphisms
void displayResults() {

    cout << "\n========== AUTOMORPHISM RESULTS ==========\n";

    for (int i = 0;
         i < (int)automorphisms.size();
         i++) {

        cout << "\nAutomorphism " << i + 1 << ": ";

        displayMapping(automorphisms[i]);

        cout << endl;
    }

    cout << "\nTotal automorphisms found: "
         << totalAutomorphisms << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached. "
             << "Some mappings were not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== GRAPH AUTOMORPHISM DETECTION =====\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 12) {

        cout << "\nNumber of vertices must be between 1 and 12.\n";

        return 0;
    }

    if (!readGraph()) {
        return 0;
    }

    cout << "\nEnter maximum automorphisms to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";

        return 0;
    }

    displayGraph();

    displayDegrees();

    cout << "\nPerforming neighborhood refinement...\n";

    refineColors();

    displayColors();

    prepareProcessingOrder();

    mapping.assign(n, -1);

    used.assign(n, false);

    cout << "\nSearching for graph automorphisms...\n";

    findAutomorphisms(0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
