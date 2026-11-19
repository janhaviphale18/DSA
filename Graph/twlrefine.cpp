#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iomanip>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    // pairColors[u][v] stores the color of ordered pair (u, v).
    vector<vector<int>> pairColors;

    vector<vector<vector<int>>> colorHistory;

public:
    Graph(int vertices) {
        V = vertices;
        adj.assign(V, vector<int>(V, 0));
        pairColors.assign(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void displayGraph() {
        cout << "\nAdjacency Matrix:\n";

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
            }

            cout << "\n";
        }
    }

    void initializePairColors() {

        cout << "\n========== INITIAL 2-WL COLORS ==========\n";

        map<int, int> initialColorMap;

        // 0 = diagonal pair
        // 1 = adjacent pair
        // 2 = non-adjacent pair

        initialColorMap[0] = 0;
        initialColorMap[1] = 1;
        initialColorMap[2] = 2;

        for (int u = 0; u < V; u++) {

            for (int v = 0; v < V; v++) {

                if (u == v) {
                    pairColors[u][v] = 0;
                }
                else if (adj[u][v] == 1) {
                    pairColors[u][v] = 1;
                }
                else {
                    pairColors[u][v] = 2;
                }
            }
        }

        colorHistory.push_back(pairColors);

        displayPairColors(pairColors);
    }

    void displayPairColors(
        const vector<vector<int>>& colors
    ) {

        cout << "\nPair Color Matrix:\n";

        cout << "     ";

        for (int v = 0; v < V; v++) {
            cout << setw(4) << v;
        }

        cout << "\n";

        for (int u = 0; u < V; u++) {

            cout << setw(4) << u << " ";

            for (int v = 0; v < V; v++) {
                cout << setw(4) << colors[u][v];
            }

            cout << "\n";
        }
    }

    int countColorClasses(
        const vector<vector<int>>& colors
    ) {

        set<int> uniqueColors;

        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                uniqueColors.insert(colors[u][v]);
            }
        }

        return uniqueColors.size();
    }

    void refine2WL() {

        cout << "\n========== 2-WL REFINEMENT ==========\n";

        int iteration = 1;

        while (iteration <= V * V) {

            // A signature contains:
            // Current pair color and sorted multiset
            // of (color(u,w), color(w,v)) pairs.

            vector<vector<
                pair<int, vector<pair<int, int>>>
            >> signatures(
                V,
                vector<pair<int, vector<pair<int, int>>>>(V)
            );

            for (int u = 0; u < V; u++) {

                for (int v = 0; v < V; v++) {

                    vector<pair<int, int>> neighbourhood;

                    for (int w = 0; w < V; w++) {

                        neighbourhood.push_back({
                            pairColors[u][w],
                            pairColors[w][v]
                        });
                    }

                    sort(
                        neighbourhood.begin(),
                        neighbourhood.end()
                    );

                    signatures[u][v] = {
                        pairColors[u][v],
                        neighbourhood
                    };
                }
            }

            // Assign canonical color IDs to unique signatures.

            map<
                pair<int, vector<pair<int, int>>>,
                int
            > colorMap;

            for (int u = 0; u < V; u++) {

                for (int v = 0; v < V; v++) {
                    colorMap[signatures[u][v]] = 0;
                }
            }

            int nextColor = 0;

            for (auto& entry : colorMap) {
                entry.second = nextColor++;
            }

            vector<vector<int>> newColors(
                V,
                vector<int>(V)
            );

            for (int u = 0; u < V; u++) {

                for (int v = 0; v < V; v++) {

                    newColors[u][v] =
                        colorMap[signatures[u][v]];
                }
            }

            int oldClasses =
                countColorClasses(pairColors);

            int newClasses =
                countColorClasses(newColors);

            pairColors = newColors;

            colorHistory.push_back(pairColors);

            cout << "\nIteration " << iteration << "\n";

            displayPairColors(pairColors);

            cout << "Number of pair-color classes: "
                 << newClasses << "\n";

            if (oldClasses == newClasses) {

                cout << "\nStable pair-color partition reached.\n";
                break;
            }

            iteration++;
        }
    }

    void displayFinalClasses() {

        cout << "\n========== FINAL 2-WL COLOR CLASSES ==========\n";

        map<int, vector<pair<int, int>>> groups;

        for (int u = 0; u < V; u++) {

            for (int v = 0; v < V; v++) {

                groups[pairColors[u][v]].push_back({u, v});
            }
        }

        for (const auto& group : groups) {

            cout << "\nColor " << group.first << ": { ";

            for (const auto& p : group.second) {

                cout << "(" << p.first
                     << "," << p.second << ") ";
            }

            cout << "}\n";
        }
    }

    void compareTransposedPairs() {

        cout << "\n========== PAIR SYMMETRY CHECK ==========\n";

        bool symmetric = true;

        for (int u = 0; u < V; u++) {

            for (int v = 0; v < V; v++) {

                if (pairColors[u][v] != pairColors[v][u]) {
                    symmetric = false;
                }
            }
        }

        if (symmetric) {
            cout << "Every pair and its reverse have the same color.\n";
        }
        else {
            cout << "Some reversed pairs have different colors.\n";
        }
    }

    void displaySummary() {

        cout << "\n========== FINAL SUMMARY ==========\n";

        cout << "Number of vertices: " << V << "\n";

        cout << "Number of ordered pairs: "
             << V * V << "\n";

        cout << "Final pair-color classes: "
             << countColorClasses(pairColors) << "\n";

        cout << "Refinement iterations: "
             << colorHistory.size() - 1 << "\n";

        cout << "\n2-WL analyzes relationships between pairs "
             << "of vertices rather than individual vertices.\n";

        cout << "It is stronger than ordinary 1-WL refinement, "
             << "but it is not a complete graph-isomorphism test.\n";
    }
};

int main() {

    int V, E;

    cout << "2-DIMENSIONAL WEISFEILER-LEMAN REFINEMENT\n";

    cout << "Enter number of vertices (maximum 8): ";
    cin >> V;

    if (V <= 0 || V > 8) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0 || E > V * (V - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    Graph graph(V);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter edges (u v):\n";

    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertex. Enter again.\n";
            i--;
            continue;
        }

        if (u == v) {
            cout << "Self-loops are not allowed. Enter again.\n";
            i--;
            continue;
        }

        if (u > v) {
            swap(u, v);
        }

        if (existingEdges.count({u, v})) {
            cout << "Duplicate edge. Enter again.\n";
            i--;
            continue;
        }

        existingEdges.insert({u, v});

        graph.addEdge(u, v);
    }

    graph.displayGraph();

    graph.initializePairColors();

    graph.refine2WL();

    graph.displayFinalClasses();

    graph.compareTransposedPairs();

    graph.displaySummary();

    cout << "\nProgram completed successfully.\n";

    return 0;
}
