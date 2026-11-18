#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
#include <string>
using namespace std;

const int MAX_VERTICES = 9;

using Graph = vector<vector<bool>>;

struct CanonicalResult {

    string canonicalForm;

    vector<int> canonicalOrder;

    unsigned long long leafCount = 0;

    bool initialized = false;
};

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

// Count distinct color classes
int countColorClasses(const vector<int>& colors) {

    map<int, int> frequency;

    for (int color : colors) {
        frequency[color]++;
    }

    return frequency.size();
}

// Assign canonical color IDs based on signatures
vector<int> assignColors(
    const vector<vector<int>>& signatures
) {

    map<vector<int>, int> colorIDs;

    for (const auto& signature : signatures) {

        colorIDs[signature] = 0;
    }

    int nextColor = 0;

    for (auto& entry : colorIDs) {

        entry.second = nextColor++;
    }

    vector<int> newColors(signatures.size());

    for (int i = 0; i < signatures.size(); i++) {

        newColors[i] = colorIDs[signatures[i]];
    }

    return newColors;
}

// Initialize colors using vertex degrees
vector<int> initializeColors(const Graph& graph) {

    vector<int> degree = calculateDegrees(graph);

    vector<vector<int>> signatures;

    for (int value : degree) {

        signatures.push_back({value});
    }

    return assignColors(signatures);
}

// Perform one round of color refinement
vector<int> refineOneRound(
    const Graph& graph,
    const vector<int>& oldColors
) {

    int n = graph.size();

    int colorCount = countColorClasses(oldColors);

    vector<vector<int>> signatures(n);

    for (int u = 0; u < n; u++) {

        vector<int> neighborCounts(colorCount, 0);

        // Count neighbors belonging to each color class
        for (int v = 0; v < n; v++) {

            if (graph[u][v]) {

                neighborCounts[oldColors[v]]++;
            }
        }

        // Preserve the current color
        signatures[u].push_back(oldColors[u]);

        // Append neighbor counts
        for (int count : neighborCounts) {

            signatures[u].push_back(count);
        }
    }

    return assignColors(signatures);
}

// Refine until the partition stops splitting
vector<int> refineUntilStable(
    const Graph& graph,
    vector<int> colors
) {

    while (true) {

        int oldCount = countColorClasses(colors);

        vector<int> newColors =
            refineOneRound(graph, colors);

        int newCount = countColorClasses(newColors);

        colors = newColors;

        if (newCount == oldCount) {
            break;
        }
    }

    return colors;
}

// Find the smallest non-singleton color class
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

        int currentSize = entry.second.size();

        if (currentSize > 1 &&
            currentSize < smallestSize) {

            smallestSize = currentSize;

            selectedColor = entry.first;
        }
    }

    return selectedColor;
}

// Generate canonical adjacency representation
string generateCanonicalForm(
    const Graph& graph,
    const vector<int>& order
) {

    int n = graph.size();

    string representation;

    // Read the upper triangle in canonical order
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

// Display a search branch
void displayBranch(
    int depth,
    int selectedVertex,
    int selectedColor
) {

    cout << string(depth * 2, ' ')
         << "Branch: individualize vertex "
         << selectedVertex
         << " from color class "
         << selectedColor << endl;
}

// Recursively explore the canonical search tree
void buildCanonicalSearchTree(
    const Graph& graph,
    vector<int> colors,
    CanonicalResult& result,
    int depth = 0
) {

    int n = graph.size();

    // Step 1: Refine the current partition
    colors = refineUntilStable(graph, colors);

    // Step 2: Find a non-singleton color class
    int selectedColor = selectBranchColor(colors);

    // Step 3: All color classes are singletons
    if (selectedColor == -1) {

        vector<pair<int, int>> orderedVertices;

        for (int i = 0; i < n; i++) {

            orderedVertices.push_back({colors[i], i});
        }

        sort(
            orderedVertices.begin(),
            orderedVertices.end()
        );

        vector<int> order;

        for (const auto& entry : orderedVertices) {

            order.push_back(entry.second);
        }

        string currentForm =
            generateCanonicalForm(graph, order);

        result.leafCount++;

        cout << string(depth * 2, ' ')
             << "Leaf reached. Canonical form: "
             << currentForm << endl;

        // Keep the lexicographically smallest representation
        if (!result.initialized ||
            currentForm < result.canonicalForm) {

            result.canonicalForm = currentForm;

            result.canonicalOrder = order;

            result.initialized = true;
        }

        return;
    }

    // Step 4: Collect vertices in the selected class
    vector<int> candidates;

    for (int i = 0; i < n; i++) {

        if (colors[i] == selectedColor) {

            candidates.push_back(i);
        }
    }

    // Step 5: Generate a new unique color
    int newColor = 0;

    for (int color : colors) {

        newColor = max(newColor, color + 1);
    }

    // Step 6: Explore every possible individualization
    for (int vertex : candidates) {

        displayBranch(
            depth,
            vertex,
            selectedColor
        );

        vector<int> childColors = colors;

        childColors[vertex] = newColor;

        // Recursively explore the child branch
        buildCanonicalSearchTree(
            graph,
            childColors,
            result,
            depth + 1
        );
    }
}

// Display graph edges
void displayGraph(
    const Graph& graph,
    const string& name
) {

    int n = graph.size();

    cout << "\n========== " << name << " ==========\n";

    bool found = false;

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (graph[i][j]) {

                cout << "(" << i << ", " << j << ") ";

                found = true;
            }
        }
    }

    if (!found) {
        cout << "No edges";
    }

    cout << endl;
}

// Display canonical order
void displayOrder(
    const vector<int>& order,
    const string& name
) {

    cout << "\n" << name
         << " canonical order: ";

    for (int vertex : order) {

        cout << vertex << " ";
    }

    cout << endl;
}

// Display canonical form
void displayCanonicalForm(
    const string& form,
    const string& name
) {

    cout << "\n" << name
         << " canonical form: "
         << form << endl;
}

// Generate an isomorphism mapping
vector<int> generateMapping(
    const vector<int>& orderA,
    const vector<int>& orderB
) {

    int n = orderA.size();

    vector<int> mapping(n, -1);

    for (int i = 0; i < n; i++) {

        mapping[orderA[i]] = orderB[i];
    }

    return mapping;
}

// Display mapping
void displayMapping(
    const vector<int>& mapping
) {

    cout << "\n========== ISOMORPHISM MAPPING ==========\n";

    for (int i = 0; i < mapping.size(); i++) {

        cout << "Graph A Vertex " << i
             << " -> Graph B Vertex "
             << mapping[i] << endl;
    }
}

// Main function
int main() {

    cout << "===== GRAPH ISOMORPHISM USING CANONICAL SEARCH TREES =====\n";

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

    displayGraph(graphA, "GRAPH A");
    displayGraph(graphB, "GRAPH B");

    // Generate initial degree-based colors
    vector<int> initialA = initializeColors(graphA);

    vector<int> initialB = initializeColors(graphB);

    cout << "\n========== GRAPH A SEARCH TREE ==========\n";

    CanonicalResult resultA;

    buildCanonicalSearchTree(
        graphA,
        initialA,
        resultA
    );

    cout << "\n========== GRAPH B SEARCH TREE ==========\n";

    CanonicalResult resultB;

    buildCanonicalSearchTree(
        graphB,
        initialB,
        resultB
    );

    // Display canonical results
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

    cout << "\nGraph A search tree leaves: "
         << resultA.leafCount << endl;

    cout << "Graph B search tree leaves: "
         << resultB.leafCount << endl;

    // Compare canonical forms
    cout << "\n========== FINAL RESULT ==========\n";

    if (resultA.canonicalForm == resultB.canonicalForm) {

        cout << "\nThe graphs ARE isomorphic.\n";

        vector<int> mapping = generateMapping(
            resultA.canonicalOrder,
            resultB.canonicalOrder
        );

        displayMapping(mapping);
    }

    else {

        cout << "\nThe graphs are NOT isomorphic.\n";
    }

    return 0;
}
