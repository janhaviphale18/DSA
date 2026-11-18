#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <functional>
using namespace std;

const int MAX_VERTICES = 10;

// Read a simple undirected graph
bool readGraph(
    vector<vector<bool>>& graph,
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

// Calculate the degree of every vertex
vector<int> calculateDegrees(
    const vector<vector<bool>>& graph
) {

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
void assignColors(
    const vector<vector<int>>& signaturesA,
    const vector<vector<int>>& signaturesB,
    vector<int>& colorsA,
    vector<int>& colorsB
) {

    map<vector<int>, int> colorIDs;

    // Collect signatures from Graph A
    for (const auto& signature : signaturesA) {

        colorIDs[signature] = 0;
    }

    // Collect signatures from Graph B
    for (const auto& signature : signaturesB) {

        colorIDs[signature] = 0;
    }

    // Give every unique signature a unique color
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
int countColors(
    const vector<int>& colorsA,
    const vector<int>& colorsB
) {

    int maximumColor = -1;

    for (int color : colorsA) {
        maximumColor = max(maximumColor, color);
    }

    for (int color : colorsB) {
        maximumColor = max(maximumColor, color);
    }

    return maximumColor + 1;
}

// Initialize colors using vertex degrees
void initializeColors(
    const vector<vector<bool>>& graphA,
    const vector<vector<bool>>& graphB,
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

    assignColors(
        signaturesA,
        signaturesB,
        colorsA,
        colorsB
    );
}

// Perform one round of color refinement
void refineOneRound(
    const vector<vector<bool>>& graphA,
    const vector<vector<bool>>& graphB,
    const vector<int>& oldColorsA,
    const vector<int>& oldColorsB,
    vector<int>& newColorsA,
    vector<int>& newColorsB
) {

    int n = graphA.size();

    vector<vector<int>> signaturesA(n);
    vector<vector<int>> signaturesB(n);

    // Build signatures for Graph A
    for (int i = 0; i < n; i++) {

        vector<int> signature;

        // Include the current vertex color
        signature.push_back(oldColorsA[i]);

        vector<int> neighborColors;

        // Collect colors of neighboring vertices
        for (int j = 0; j < n; j++) {

            if (graphA[i][j]) {

                neighborColors.push_back(oldColorsA[j]);
            }
        }

        sort(
            neighborColors.begin(),
            neighborColors.end()
        );

        // Append sorted neighbor colors
        for (int color : neighborColors) {

            signature.push_back(color);
        }

        signaturesA[i] = signature;
    }

    // Build signatures for Graph B
    for (int i = 0; i < n; i++) {

        vector<int> signature;

        signature.push_back(oldColorsB[i]);

        vector<int> neighborColors;

        for (int j = 0; j < n; j++) {

            if (graphB[i][j]) {

                neighborColors.push_back(oldColorsB[j]);
            }
        }

        sort(
            neighborColors.begin(),
            neighborColors.end()
        );

        for (int color : neighborColors) {

            signature.push_back(color);
        }

        signaturesB[i] = signature;
    }

    // Assign colors jointly to both graphs
    assignColors(
        signaturesA,
        signaturesB,
        newColorsA,
        newColorsB
    );
}

// Display colors
void displayColors(
    const vector<int>& colors,
    const string& name
) {

    cout << "\n" << name << " vertex colors:\n";

    for (int i = 0; i < colors.size(); i++) {

        cout << "Vertex " << i
             << " -> Color " << colors[i] << endl;
    }
}

// Display color frequency
vector<int> getColorHistogram(
    const vector<int>& colors,
    int totalColors
) {

    vector<int> histogram(totalColors, 0);

    for (int color : colors) {

        histogram[color]++;
    }

    return histogram;
}

// Compare color distributions
bool compareColorHistograms(
    const vector<int>& colorsA,
    const vector<int>& colorsB,
    int totalColors
) {

    vector<int> histogramA =
        getColorHistogram(colorsA, totalColors);

    vector<int> histogramB =
        getColorHistogram(colorsB, totalColors);

    cout << "\n========== COLOR DISTRIBUTIONS ==========\n";

    for (int i = 0; i < totalColors; i++) {

        cout << "Color " << i
             << " | Graph A: " << histogramA[i]
             << " | Graph B: " << histogramB[i]
             << endl;
    }

    return histogramA == histogramB;
}

// Exact graph isomorphism verification
bool verifyIsomorphism(
    const vector<vector<bool>>& graphA,
    const vector<vector<bool>>& graphB,
    const vector<int>& colorsA,
    const vector<int>& colorsB,
    vector<int>& mapping
) {

    int n = graphA.size();

    vector<int> degreeA = calculateDegrees(graphA);

    vector<int> degreeB = calculateDegrees(graphB);

    vector<bool> used(n, false);

    mapping.assign(n, -1);

    // Process the most structurally constrained vertices first
    vector<int> order(n);

    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(),
        [&](int a, int b) {

            if (colorsA[a] != colorsA[b]) {

                return colorsA[a] < colorsA[b];
            }

            return degreeA[a] > degreeA[b];
        }
    );

    function<bool(int)> search = [&](int index) {

        if (index == n) {
            return true;
        }

        int u = order[index];

        for (int v = 0; v < n; v++) {

            if (used[v]) {
                continue;
            }

            // Candidate vertices must have the same refined color
            if (colorsA[u] != colorsB[v]) {
                continue;
            }

            // Candidate vertices must have the same degree
            if (degreeA[u] != degreeB[v]) {
                continue;
            }

            bool compatible = true;

            // Check adjacency with already mapped vertices
            for (int i = 0; i < index; i++) {

                int previousU = order[i];

                int previousV = mapping[previousU];

                if (graphA[u][previousU] !=
                    graphB[v][previousV]) {

                    compatible = false;

                    break;
                }
            }

            if (!compatible) {
                continue;
            }

            mapping[u] = v;

            used[v] = true;

            if (search(index + 1)) {
                return true;
            }

            // Backtrack
            mapping[u] = -1;

            used[v] = false;
        }

        return false;
    };

    return search(0);
}

// Display final mapping
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

    cout << "===== WEISFEILER-LEMAN GRAPH ISOMORPHISM =====\n";

    int n;

    cout << "\nEnter number of vertices in both graphs: ";

    cin >> n;

    if (n <= 0 || n > MAX_VERTICES) {

        cout << "Vertices must be between 1 and "
             << MAX_VERTICES << ".\n";

        return 0;
    }

    vector<vector<bool>> graphA;
    vector<vector<bool>> graphB;

    if (!readGraph(graphA, n, "Graph A")) {
        return 0;
    }

    if (!readGraph(graphB, n, "Graph B")) {
        return 0;
    }

    vector<int> colorsA;
    vector<int> colorsB;

    // Step 1: Initialize colors using degrees
    initializeColors(
        graphA,
        graphB,
        colorsA,
        colorsB
    );

    int totalColors = countColors(colorsA, colorsB);

    cout << "\nInitial color refinement:\n";

    displayColors(colorsA, "Graph A");
    displayColors(colorsB, "Graph B");

    // Step 2: Iterative refinement
    int rounds = 0;

    while (rounds < n) {

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

        int newTotalColors =
            countColors(newColorsA, newColorsB);

        rounds++;

        cout << "\n========== ROUND "
             << rounds << " ==========\n";

        displayColors(newColorsA, "Graph A");
        displayColors(newColorsB, "Graph B");

        colorsA = newColorsA;
        colorsB = newColorsB;

        // No additional color classes were created
        if (newTotalColors == totalColors) {

            cout << "\nColor partition has stabilized.\n";

            totalColors = newTotalColors;

            break;
        }

        totalColors = newTotalColors;
    }

    cout << "\nTotal refinement rounds: "
         << rounds << endl;

    // Step 3: Compare color distributions
    bool distributionsMatch =
        compareColorHistograms(
            colorsA,
            colorsB,
            totalColors
        );

    if (!distributionsMatch) {

        cout << "\nColor distributions differ.\n";

        cout << "The graphs are NOT isomorphic.\n";

        return 0;
    }

    cout << "\nColor distributions match.\n";

    cout << "WL refinement alone cannot confirm isomorphism.\n";

    // Step 4: Exact verification
    cout << "\nPerforming exact backtracking verification...\n";

    vector<int> mapping;

    bool isomorphic = verifyIsomorphism(
        graphA,
        graphB,
        colorsA,
        colorsB,
        mapping
    );

    if (isomorphic) {

        cout << "\nThe graphs ARE isomorphic.\n";

        displayMapping(mapping);
    }

    else {

        cout << "\nThe graphs are NOT isomorphic.\n";
    }

    return 0;
}
