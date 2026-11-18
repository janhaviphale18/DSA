#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <functional>
using namespace std;

const int MAX_VERTICES = 10;

using Graph = vector<vector<bool>>;
using PairColors = vector<vector<int>>;

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

// Assign common color IDs to signatures from both graphs
void assignPairColors(
    const vector<vector<vector<int>>>& signaturesA,
    const vector<vector<vector<int>>>& signaturesB,
    PairColors& colorsA,
    PairColors& colorsB
) {

    map<vector<int>, int> colorIDs;

    int n = signaturesA.size();

    // Collect signatures from both graphs
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            colorIDs[signaturesA[i][j]] = 0;

            colorIDs[signaturesB[i][j]] = 0;
        }
    }

    // Assign unique IDs to signatures
    int nextColor = 0;

    for (auto& entry : colorIDs) {

        entry.second = nextColor++;
    }

    colorsA.assign(n, vector<int>(n));

    colorsB.assign(n, vector<int>(n));

    // Assign colors to Graph A
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            colorsA[i][j] =
                colorIDs[signaturesA[i][j]];
        }
    }

    // Assign colors to Graph B
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            colorsB[i][j] =
                colorIDs[signaturesB[i][j]];
        }
    }
}

// Count distinct colors across both pair-color matrices
int countColors(
    const PairColors& colorsA,
    const PairColors& colorsB
) {

    int maximumColor = -1;

    int n = colorsA.size();

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            maximumColor = max(
                maximumColor,
                colorsA[i][j]
            );

            maximumColor = max(
                maximumColor,
                colorsB[i][j]
            );
        }
    }

    return maximumColor + 1;
}

// Initialize ordered-pair colors
void initializePairColors(
    const Graph& graphA,
    const Graph& graphB,
    PairColors& colorsA,
    PairColors& colorsB
) {

    int n = graphA.size();

    vector<vector<vector<int>>> signaturesA(
        n, vector<vector<int>>(n)
    );

    vector<vector<vector<int>>> signaturesB(
        n, vector<vector<int>>(n)
    );

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            // Diagonal pair
            if (i == j) {

                signaturesA[i][j] = {0};
                signaturesB[i][j] = {0};
            }

            // Adjacent pair
            else if (graphA[i][j]) {

                signaturesA[i][j] = {1};
            }

            else {

                signaturesA[i][j] = {2};
            }

            if (i != j && graphB[i][j]) {

                signaturesB[i][j] = {1};
            }

            else if (i != j) {

                signaturesB[i][j] = {2};
            }
        }
    }

    assignPairColors(
        signaturesA,
        signaturesB,
        colorsA,
        colorsB
    );
}

// Perform one 2-WL refinement round
void refineOneRound(
    const Graph& graphA,
    const Graph& graphB,
    const PairColors& oldColorsA,
    const PairColors& oldColorsB,
    PairColors& newColorsA,
    PairColors& newColorsB
) {

    int n = graphA.size();

    vector<vector<vector<int>>> signaturesA(
        n, vector<vector<int>>(n)
    );

    vector<vector<vector<int>>> signaturesB(
        n, vector<vector<int>>(n)
    );

    // Build signatures for Graph A
    for (int u = 0; u < n; u++) {

        for (int v = 0; v < n; v++) {

            vector<pair<int, int>> relationships;

            // Examine every intermediate vertex
            for (int w = 0; w < n; w++) {

                relationships.push_back({
                    oldColorsA[u][w],
                    oldColorsA[w][v]
                });
            }

            // Sort the pair-color relationships
            sort(
                relationships.begin(),
                relationships.end()
            );

            vector<int> signature;

            // Preserve the current pair color
            signature.push_back(oldColorsA[u][v]);

            // Append sorted relationship pairs
            for (const auto& relationship : relationships) {

                signature.push_back(relationship.first);

                signature.push_back(relationship.second);
            }

            signaturesA[u][v] = signature;
        }
    }

    // Build signatures for Graph B
    for (int u = 0; u < n; u++) {

        for (int v = 0; v < n; v++) {

            vector<pair<int, int>> relationships;

            for (int w = 0; w < n; w++) {

                relationships.push_back({
                    oldColorsB[u][w],
                    oldColorsB[w][v]
                });
            }

            sort(
                relationships.begin(),
                relationships.end()
            );

            vector<int> signature;

            signature.push_back(oldColorsB[u][v]);

            for (const auto& relationship : relationships) {

                signature.push_back(relationship.first);

                signature.push_back(relationship.second);
            }

            signaturesB[u][v] = signature;
        }
    }

    // Assign common color IDs
    assignPairColors(
        signaturesA,
        signaturesB,
        newColorsA,
        newColorsB
    );
}

// Display ordered-pair colors
void displayPairColors(
    const PairColors& colors,
    const string& name
) {

    int n = colors.size();

    cout << "\n" << name
         << " pair-color matrix:\n\n";

    cout << "     ";

    for (int j = 0; j < n; j++) {

        cout << j << "   ";
    }

    cout << endl;

    for (int i = 0; i < n; i++) {

        cout << i << "    ";

        for (int j = 0; j < n; j++) {

            cout << colors[i][j] << "   ";
        }

        cout << endl;
    }
}

// Generate pair-color histogram
vector<int> getHistogram(
    const PairColors& colors,
    int totalColors
) {

    int n = colors.size();

    vector<int> histogram(totalColors, 0);

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            histogram[colors[i][j]]++;
        }
    }

    return histogram;
}

// Compare pair-color distributions
bool compareHistograms(
    const PairColors& colorsA,
    const PairColors& colorsB,
    int totalColors
) {

    vector<int> histogramA =
        getHistogram(colorsA, totalColors);

    vector<int> histogramB =
        getHistogram(colorsB, totalColors);

    cout << "\n========== PAIR-COLOR DISTRIBUTIONS ==========\n";

    for (int i = 0; i < totalColors; i++) {

        cout << "Color " << i
             << " | Graph A: " << histogramA[i]
             << " | Graph B: " << histogramB[i]
             << endl;
    }

    return histogramA == histogramB;
}

// Calculate vertex degrees
vector<int> calculateDegrees(
    const Graph& graph
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

// Exact graph isomorphism verification
bool verifyIsomorphism(
    const Graph& graphA,
    const Graph& graphB,
    const PairColors& colorsA,
    const PairColors& colorsB,
    vector<int>& mapping
) {

    int n = graphA.size();

    vector<int> degreeA = calculateDegrees(graphA);

    vector<int> degreeB = calculateDegrees(graphB);

    vector<bool> used(n, false);

    mapping.assign(n, -1);

    vector<int> order(n);

    iota(order.begin(), order.end(), 0);

    // Process vertices with higher degree first
    sort(order.begin(), order.end(),
        [&](int a, int b) {

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

            if (degreeA[u] != degreeB[v]) {
                continue;
            }

            // Diagonal pair colors must correspond
            if (colorsA[u][u] != colorsB[v][v]) {
                continue;
            }

            bool compatible = true;

            // Check both directed pair orientations
            // for every previously mapped vertex
            for (int i = 0; i < index; i++) {

                int previousU = order[i];

                int previousV = mapping[previousU];

                if (colorsA[u][previousU] !=
                    colorsB[v][previousV]) {

                    compatible = false;
                    break;
                }

                if (colorsA[previousU][u] !=
                    colorsB[previousV][v]) {

                    compatible = false;
                    break;
                }

                // Verify exact adjacency
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

    cout << "===== 2-WL GRAPH ISOMORPHISM =====\n";

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

    PairColors colorsA;
    PairColors colorsB;

    // Step 1: Initialize ordered-pair colors
    initializePairColors(
        graphA,
        graphB,
        colorsA,
        colorsB
    );

    int totalColors = countColors(
        colorsA,
        colorsB
    );

    cout << "\n========== INITIAL PAIR COLORS ==========\n";

    displayPairColors(colorsA, "Graph A");
    displayPairColors(colorsB, "Graph B");

    // Step 2: Perform iterative refinement
    int rounds = 0;

    // Each graph has n*n ordered pairs.
    // The combined partition can split at most 2*n*n times.
    while (rounds < 2 * n * n) {

        PairColors newColorsA;
        PairColors newColorsB;

        refineOneRound(
            graphA,
            graphB,
            colorsA,
            colorsB,
            newColorsA,
            newColorsB
        );

        int newTotalColors = countColors(
            newColorsA,
            newColorsB
        );

        rounds++;

        cout << "\n========== ROUND "
             << rounds << " ==========\n";

        displayPairColors(newColorsA, "Graph A");
        displayPairColors(newColorsB, "Graph B");

        colorsA = newColorsA;
        colorsB = newColorsB;

        if (newTotalColors == totalColors) {

            cout << "\n2-WL color partition has stabilized.\n";

            totalColors = newTotalColors;

            break;
        }

        totalColors = newTotalColors;
    }

    cout << "\nTotal refinement rounds: "
         << rounds << endl;

    // Step 3: Compare pair-color distributions
    bool distributionsMatch = compareHistograms(
        colorsA,
        colorsB,
        totalColors
    );

    if (!distributionsMatch) {

        cout << "\nPair-color distributions differ.\n";

        cout << "The graphs are NOT isomorphic.\n";

        return 0;
    }

    cout << "\nPair-color distributions match.\n";

    cout << "2-WL alone cannot guarantee isomorphism.\n";

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
