#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int verticesA;
int verticesB;

int bestDistance = INT_MAX;

long long totalMappings = 0;
long long recursiveCalls = 0;
long long maxSolutions;

bool storageLimitReached = false;

vector<vector<bool>> graphA;
vector<vector<bool>> graphB;

vector<int> mapping;
vector<int> reverseMapping;

vector<int> degreeA;
vector<int> degreeB;

vector<int> processingOrder;

struct Solution {

    vector<int> mapping;

    int vertexDeletions;
    int vertexInsertions;

    int edgeDeletions;
    int edgeInsertions;

    int totalCost;
};

vector<Solution> bestMappings;

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

// Evaluate the complete mapping and calculate edit operations
Solution evaluateMapping() {

    Solution result;

    result.mapping = mapping;

    int matchedVertices = 0;

    for (int i = 0; i < verticesA; i++) {

        if (mapping[i] != -1) {
            matchedVertices++;
        }
    }

    // Unmatched vertices require deletion or insertion
    result.vertexDeletions =
        verticesA - matchedVertices;

    result.vertexInsertions =
        verticesB - matchedVertices;

    result.edgeDeletions = 0;
    result.edgeInsertions = 0;

    // Check all pairs in Graph A
    for (int i = 0; i < verticesA; i++) {

        for (int j = i + 1; j < verticesA; j++) {

            // An edge involving an unmatched vertex
            // must be deleted
            if (mapping[i] == -1 ||
                mapping[j] == -1) {

                if (graphA[i][j]) {
                    result.edgeDeletions++;
                }

                continue;
            }

            // Compare corresponding mapped pairs
            bool edgeInA = graphA[i][j];

            bool edgeInB = graphB[mapping[i]][mapping[j]];

            if (edgeInA && !edgeInB) {

                result.edgeDeletions++;
            }
            else if (!edgeInA && edgeInB) {

                result.edgeInsertions++;
            }
        }
    }

    // Count edges in Graph B involving unmatched vertices
    for (int i = 0; i < verticesB; i++) {

        for (int j = i + 1; j < verticesB; j++) {

            if (reverseMapping[i] == -1 ||
                reverseMapping[j] == -1) {

                if (graphB[i][j]) {
                    result.edgeInsertions++;
                }
            }
        }
    }

    result.totalCost =
        result.vertexDeletions +
        result.vertexInsertions +
        result.edgeDeletions +
        result.edgeInsertions;

    return result;
}

// Store a minimum-cost solution
void storeSolution(const Solution& result) {

    if (result.totalCost < bestDistance) {

        bestDistance = result.totalCost;

        totalMappings = 0;

        bestMappings.clear();

        storageLimitReached = false;
    }

    if (result.totalCost == bestDistance) {

        totalMappings++;

        if ((long long)bestMappings.size() < maxSolutions) {

            bestMappings.push_back(result);

        } else {

            storageLimitReached = true;
        }
    }
}

// Calculate the minimum possible remaining vertex edit cost
int minimumRemainingVertexCost(
    int index,
    int matchedCount
) {

    int remainingA = verticesA - index;

    int unusedB = verticesB - matchedCount;

    int maximumAdditionalMatches =
        min(remainingA, unusedB);

    int maximumFinalMatches =
        matchedCount + maximumAdditionalMatches;

    return verticesA + verticesB -
           2 * maximumFinalMatches;
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

// Recursive graph edit distance search
void findEditDistance(
    int index,
    int matchedCount,
    int currentEdgeCost
) {

    recursiveCalls++;

    // Branch and bound
    int vertexLowerBound =
        minimumRemainingVertexCost(index, matchedCount);

    int lowerBound =
        currentEdgeCost + vertexLowerBound;

    if (lowerBound > bestDistance) {
        return;
    }

    // All vertices of Graph A have been considered
    if (index == verticesA) {

        Solution result = evaluateMapping();

        storeSolution(result);

        return;
    }

    int u = processingOrder[index];

    // Option 1: Match current vertex with a host vertex
    for (int v = 0; v < verticesB; v++) {

        if (reverseMapping[v] != -1) {
            continue;
        }

        // Calculate additional edge mismatches
        // caused by this new mapping
        int additionalEdgeCost = 0;

        for (int previous = 0;
             previous < verticesA;
             previous++) {

            if (mapping[previous] == -1) {
                continue;
            }

            int mappedVertex = mapping[previous];

            if (graphA[u][previous] !=
                graphB[v][mappedVertex]) {

                additionalEdgeCost++;
            }
        }

        // Make the mapping
        mapping[u] = v;

        reverseMapping[v] = u;

        // Explore this candidate
        findEditDistance(
            index + 1,
            matchedCount + 1,
            currentEdgeCost + additionalEdgeCost
        );

        // Backtracking
        mapping[u] = -1;

        reverseMapping[v] = -1;
    }

    // Option 2: Delete the current Graph A vertex
    mapping[u] = -1;

    findEditDistance(
        index + 1,
        matchedCount,
        currentEdgeCost
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

    cout << "\n" << graphName << " degrees: ";

    for (int value : degree) {
        cout << value << " ";
    }

    cout << endl;
}

// Display one solution
void displaySolution(
    const Solution& result,
    int solutionNumber
) {

    cout << "\nSolution " << solutionNumber << ":\n";

    cout << "Vertex mapping: { ";

    for (int i = 0; i < verticesA; i++) {

        if (result.mapping[i] != -1) {

            cout << i << " -> " << result.mapping[i] << ", ";
        }
        else {

            cout << i << " -> DELETED, ";
        }
    }

    cout << "}\n";

    cout << "Vertex deletions: "
         << result.vertexDeletions << endl;

    cout << "Vertex insertions: "
         << result.vertexInsertions << endl;

    cout << "Edge deletions: "
         << result.edgeDeletions << endl;

    cout << "Edge insertions: "
         << result.edgeInsertions << endl;

    cout << "Total edit cost: "
         << result.totalCost << endl;
}

// Display final results
void displayResults() {

    cout << "\n========== GRAPH EDIT DISTANCE RESULTS ==========\n";

    cout << "\nMinimum Graph Edit Distance: "
         << bestDistance << endl;

    cout << "\nOptimal mappings:\n";

    for (int i = 0;
         i < (int)bestMappings.size();
         i++) {

        displaySolution(bestMappings[i], i + 1);
    }

    cout << "\nTotal optimal mappings found: "
         << totalMappings << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached. "
             << "Some optimal mappings were not stored.\n";
    }
}

// Main function
int main() {

    cout << "===== GRAPH EDIT DISTANCE =====\n";

    cout << "\nEnter number of vertices in Graph A: ";
    cin >> verticesA;

    if (verticesA <= 0 || verticesA > 7) {

        cout << "\nGraph A must have between 1 and 7 vertices.\n";

        return 0;
    }

    cout << "\nEnter number of vertices in Graph B: ";
    cin >> verticesB;

    if (verticesB <= 0 || verticesB > 7) {

        cout << "\nGraph B must have between 1 and 7 vertices.\n";

        return 0;
    }

    if (!readGraph(graphA, verticesA, "Graph A")) {
        return 0;
    }

    if (!readGraph(graphB, verticesB, "Graph B")) {
        return 0;
    }

    cout << "\nEnter maximum optimal mappings to store: ";
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

    // Prepare vertex search order
    prepareProcessingOrder();

    // Initialize mapping structures
    mapping.assign(verticesA, -1);

    reverseMapping.assign(verticesB, -1);

    cout << "\nSearching for minimum graph edit distance...\n";

    findEditDistance(0, 0, 0);

    displayResults();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
