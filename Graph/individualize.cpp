#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

const int MAX_VERTICES = 10;

using Graph = vector<vector<bool>>;

// Read a simple undirected graph
bool readGraph(
    Graph& graph,
    int n,
    const string& name
) {

    graph.assign(n, vector<bool>(n, false));

    int edges;

    cout << "\nEnter number of edges in "
         << name << ": ";

    cin >> edges;

    if (edges < 0 || edges > n * (n - 1) / 2) {

        cout << "Invalid number of edges.\n";

        return false;
    }

    cout << "\nEnter edges using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < edges; i++) {

        int u, v;

        cout << "Edge " << i + 1 << ": ";

        cin >> u >> v;

        if (u < 0 || u >= n ||
            v < 0 || v >= n ||
            u == v || graph[u][v]) {

            cout << "Invalid or duplicate edge.\n";

            return false;
        }

        graph[u][v] = true;
        graph[v][u] = true;
    }

    return true;
}

// Calculate vertex degrees
vector<int> calculateDegrees(const Graph& graph) {

    int n = graph.size();

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
void assignCommonColors(
    const vector<vector<int>>& signaturesA,
    const vector<vector<int>>& signaturesB,
    vector<int>& colorsA,
    vector<int>& colorsB
) {

    map<vector<int>, int> colorIDs;

    // Collect signatures from both graphs
    for (const auto& signature : signaturesA) {
        colorIDs[signature] = 0;
    }

    for (const auto& signature : signaturesB) {
        colorIDs[signature] = 0;
    }

    // Assign unique IDs
    int nextColor = 0;

    for (auto& entry : colorIDs) {
        entry.second = nextColor++;
    }

    colorsA.resize(signaturesA.size());
    colorsB.resize(signaturesB.size());

    // Assign colors to Graph A
    for (int i = 0; i < signaturesA.size(); i++) {

        colorsA[i] = colorIDs[signaturesA[i]];
    }

    // Assign colors to Graph B
    for (int i = 0; i < signaturesB.size(); i++) {

        colorsB[i] = colorIDs[signaturesB[i]];
    }
}

// Count distinct colors across both graphs
int countDistinctColors(
    const vector<int>& colorsA,
    const vector<int>& colorsB
) {

    set<int> distinctColors;

    for (int color : colorsA) {
        distinctColors.insert(color);
    }

    for (int color : colorsB) {
        distinctColors.insert(color);
    }

    return distinctColors.size();
}

// Initialize colors using vertex degrees
void initializeColors(
    const Graph& graphA,
    const Graph& graphB,
    vector<int>& colorsA,
    vector<int>& colorsB
) {

    vector<int> degreeA = calculateDegrees(graphA);
    vector<int> degreeB = calculateDegrees(graphB);

    vector<vector<int>> signaturesA;
    vector<vector<int>> signaturesB;

    for (int degree : degreeA) {
        signaturesA.push_back({degree});
    }

    for (int degree : degreeB) {
        signaturesB.push_back({degree});
    }

    assignCommonColors(
        signaturesA,
        signaturesB,
        colorsA,
        colorsB
    );
}

// Perform one round of color refinement
void refineOneRound(
    const Graph& graphA,
    const Graph& graphB,
    const vector<int>& oldColorsA,
    const vector<int>& oldColorsB,
    vector<int>& newColorsA,
    vector<int>& newColorsB
) {

    int n = graphA.size();

    int colorCount = countDistinctColors(
        oldColorsA,
        oldColorsB
    );

    vector<vector<int>> signaturesA(n);
    vector<vector<int>> signaturesB(n);

    // Construct signatures for Graph A
    for (int u = 0; u < n; u++) {

        vector<int> neighborCounts(colorCount, 0);

        for (int v = 0; v < n; v++) {

            if (graphA[u][v]) {

                neighborCounts[oldColorsA[v]]++;
            }
        }

        signaturesA[u].push_back(oldColorsA[u]);

        for (int count : neighborCounts) {

            signaturesA[u].push_back(count);
        }
    }

    // Construct signatures for Graph B
    for (int u = 0; u < n; u++) {

        vector<int> neighborCounts(colorCount, 0);

        for (int v = 0; v < n; v++) {

            if (graphB[u][v]) {

                neighborCounts[oldColorsB[v]]++;
            }
        }

        signaturesB[u].push_back(oldColorsB[u]);

        for (int count : neighborCounts) {

            signaturesB[u].push_back(count);
        }
    }

    assignCommonColors(
        signaturesA,
        signaturesB,
        newColorsA,
        newColorsB
    );
}

// Refine colors until the partition stabilizes
void refineUntilStable(
    const Graph& graphA,
    const Graph& graphB,
    vector<int>& colorsA,
    vector<int>& colorsB
) {

    while (true) {

        int oldCount = countDistinctColors(
            colorsA,
            colorsB
        );

        vector<int> newColorsA;
        vector<int> newColorsB;

        refineOneRound(
            graphA,
            graphB,
            colorsA,
            colorsB,
            newColorsA,
            newColorsB
        );

        int newCount = countDistinctColors(
            newColorsA,
            newColorsB
        );

        colorsA = newColorsA;
        colorsB = newColorsB;

        // No new color class was created
        if (newCount == oldCount) {
            break;
        }
    }
}

// Compare the number of vertices in each color class
bool compareColorDistributions(
    const vector<int>& colorsA,
    const vector<int>& colorsB
) {

    map<int, int> frequencyA;
    map<int, int> frequencyB;

    for (int color : colorsA) {
        frequencyA[color]++;
    }

    for (int color : colorsB) {
        frequencyB[color]++;
    }

    return frequencyA == frequencyB;
}

// Display color classes
void displayColors(
    const vector<int>& colors,
    const string& name
) {

    cout << "\n" << name << " color classes:\n";

    map<int, vector<int>> classes;

    for (int i = 0; i < colors.size(); i++) {

        classes[colors[i]].push_back(i);
    }

    for (const auto& entry : classes) {

        cout << "Color " << entry.first << ": ";

        for (int vertex : entry.second) {
            cout << vertex << " ";
        }

        cout << endl;
    }
}

// Find a non-singleton color class with the smallest size
int selectBranchColor(
    const vector<int>& colors
) {

    map<int, vector<int>> classes;

    for (int i = 0; i < colors.size(); i++) {

        classes[colors[i]].push_back(i);
    }

    int selectedColor = -1;

    int smallestSize = colors.size() + 1;

    for (const auto& entry : classes) {

        int size = entry.second.size();

        if (size > 1 && size < smallestSize) {

            smallestSize = size;

            selectedColor = entry.first;
        }
    }

    return selectedColor;
}

// Verify a complete mapping exactly
bool verifyMapping(
    const Graph& graphA,
    const Graph& graphB,
    const vector<int>& mapping
) {

    int n = graphA.size();

    vector<bool> used(n, false);

    // Check that the mapping is one-to-one
    for (int i = 0; i < n; i++) {

        int mappedVertex = mapping[i];

        if (mappedVertex < 0 || mappedVertex >= n) {
            return false;
        }

        if (used[mappedVertex]) {
            return false;
        }

        used[mappedVertex] = true;
    }

    // Check every pair of vertices
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (graphA[i][j] !=
                graphB[mapping[i]][mapping[j]]) {

                return false;
            }
        }
    }

    return true;
}

// Individualization and refinement
bool individualizeAndRefine(
    const Graph& graphA,
    const Graph& graphB,
    vector<int> colorsA,
    vector<int> colorsB,
    vector<int>& finalMapping,
    int depth = 0
) {

    int n = graphA.size();

    // Step 1: Refine both graphs
    refineUntilStable(
        graphA,
        graphB,
        colorsA,
        colorsB
    );

    // Step 2: Reject incompatible color distributions
    if (!compareColorDistributions(colorsA, colorsB)) {

        return false;
    }

    // Step 3: Select a non-singleton color class
    int selectedColor = selectBranchColor(colorsA);

    // Step 4: All classes are singletons
    if (selectedColor == -1) {

        map<int, int> vertexB;

        for (int i = 0; i < n; i++) {

            vertexB[colorsB[i]] = i;
        }

        vector<int> mapping(n, -1);

        for (int i = 0; i < n; i++) {

            mapping[i] = vertexB[colorsA[i]];
        }

        if (verifyMapping(graphA, graphB, mapping)) {

            finalMapping = mapping;

            return true;
        }

        return false;
    }

    // Step 5: Select a vertex from Graph A
    int selectedVertex = -1;

    for (int i = 0; i < n; i++) {

        if (colorsA[i] == selectedColor) {

            selectedVertex = i;

            break;
        }
    }

    // Step 6: Collect matching candidates from Graph B
    vector<int> candidates;

    for (int i = 0; i < n; i++) {

        if (colorsB[i] == selectedColor) {

            candidates.push_back(i);
        }
    }

    // Step 7: Create a new unique color
    int newColor = 0;

    for (int color : colorsA) {
        newColor = max(newColor, color + 1);
    }

    for (int color : colorsB) {
        newColor = max(newColor, color + 1);
    }

    // Step 8: Try every candidate
    for (int candidate : candidates) {

        vector<int> nextColorsA = colorsA;
        vector<int> nextColorsB = colorsB;

        // Individualize corresponding vertices
        nextColorsA[selectedVertex] = newColor;

        nextColorsB[candidate] = newColor;

        // Recursive refinement and branching
        if (individualizeAndRefine(
            graphA,
            graphB,
            nextColorsA,
            nextColorsB,
            finalMapping,
            depth + 1
        )) {

            return true;
        }
    }

    // All candidates failed
    return false;
}

// Main function
int main() {

    cout << "===== GRAPH ISOMORPHISM USING INDIVIDUALIZATION AND REFINEMENT =====\n";

    int n;

    cout << "\nEnter number of vertices in both graphs: ";

    cin >> n;

    if (n <= 0 || n > MAX_VERTICES) {

        cout << "Vertices must be between 1 and "
             << MAX_VERTICES << ".\n";

        return 0;
    }

    Graph graphA;
    Graph graphB;

    if (!readGraph(graphA, n, "Graph A")) {
        return 0;
    }

    if (!readGraph(graphB, n, "Graph B")) {
        return 0;
    }

    // Initial colors
    vector<int> colorsA;
    vector<int> colorsB;

    initializeColors(
        graphA,
        graphB,
        colorsA,
        colorsB
    );

    cout << "\n========== INITIAL COLORING ==========\n";

    displayColors(colorsA, "Graph A");
    displayColors(colorsB, "Graph B");

    // Find an exact isomorphism
    vector<int> mapping;

    bool isomorphic = individualizeAndRefine(
        graphA,
        graphB,
        colorsA,
        colorsB,
        mapping
    );

    cout << "\n========== FINAL RESULT ==========\n";

    if (isomorphic) {

        cout << "\nThe graphs ARE isomorphic.\n";

        cout << "\nIsomorphism mapping:\n";

        for (int i = 0; i < n; i++) {

            cout << "Graph A Vertex " << i
                 << " -> Graph B Vertex "
                 << mapping[i] << endl;
        }
    }

    else {

        cout << "\nThe graphs are NOT isomorphic.\n";
    }

    return 0;
}
