#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <set>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    vector<vector<int>> refinementHistory;
    vector<vector<int>> automorphisms;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void displayGraph() {
        cout << "\nAdjacency List:\n";

        for (int i = 0; i < V; i++) {
            cout << i << " -> ";

            for (int neighbour : adj[i]) {
                cout << neighbour << " ";
            }

            cout << "\n";
        }
    }

    int countColors(const vector<int>& colors) {
        set<int> uniqueColors(
            colors.begin(), colors.end()
        );

        return uniqueColors.size();
    }

    void displayColors(const vector<int>& colors,
                       int iteration) {

        cout << "\nIteration " << iteration << ":\n";

        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i
                 << " -> Color " << colors[i] << "\n";
        }

        cout << "Number of color classes: "
             << countColors(colors) << "\n";
    }

    void colorRefinement() {
        cout << "\n========== WEISFEILER-LEMAN ==========\n";

        // Initially every vertex has the same color.
        vector<int> colors(V, 0);

        refinementHistory.push_back(colors);

        displayColors(colors, 0);

        int iteration = 1;

        while (iteration <= V) {

            vector<pair<int, vector<int>>> signatures(V);

            // Construct a signature for every vertex.
            for (int i = 0; i < V; i++) {

                vector<int> neighbourColors;

                for (int neighbour : adj[i]) {
                    neighbourColors.push_back(
                        colors[neighbour]
                    );
                }

                sort(
                    neighbourColors.begin(),
                    neighbourColors.end()
                );

                signatures[i] = {
                    colors[i],
                    neighbourColors
                };
            }

            // Assign canonical color IDs.
            map<pair<int, vector<int>>, int> colorMap;

            for (int i = 0; i < V; i++) {
                colorMap[signatures[i]] = 0;
            }

            int nextColor = 0;

            for (auto& entry : colorMap) {
                entry.second = nextColor++;
            }

            vector<int> newColors(V);

            for (int i = 0; i < V; i++) {
                newColors[i] = colorMap[signatures[i]];
            }

            int oldClasses = countColors(colors);
            int newClasses = countColors(newColors);

            colors = newColors;

            refinementHistory.push_back(colors);

            displayColors(colors, iteration);

            // If no new color class was created,
            // the partition has become stable.
            if (oldClasses == newClasses) {
                cout << "\nStable partition reached.\n";
                break;
            }

            iteration++;
        }

        displayColorClasses(colors);
    }

    void displayColorClasses(const vector<int>& colors) {

        cout << "\n========== FINAL WL COLOR CLASSES ==========\n";

        map<int, vector<int>> groups;

        for (int i = 0; i < V; i++) {
            groups[colors[i]].push_back(i);
        }

        for (auto& group : groups) {

            cout << "Color " << group.first << ": { ";

            for (int vertex : group.second) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    bool isValidAutomorphism(
        const vector<int>& permutation
    ) {

        for (int u = 0; u < V; u++) {

            for (int v = 0; v < V; v++) {

                bool originalEdge = false;
                bool mappedEdge = false;

                if (find(
                    adj[u].begin(),
                    adj[u].end(),
                    v
                ) != adj[u].end()) {
                    originalEdge = true;
                }

                int mappedU = permutation[u];
                int mappedV = permutation[v];

                if (find(
                    adj[mappedU].begin(),
                    adj[mappedU].end(),
                    mappedV
                ) != adj[mappedU].end()) {
                    mappedEdge = true;
                }

                if (originalEdge != mappedEdge) {
                    return false;
                }
            }
        }

        return true;
    }

    void findAutomorphisms() {

        cout << "\n========== EXACT AUTOMORPHISMS ==========\n";

        vector<int> permutation(V);

        iota(
            permutation.begin(),
            permutation.end(),
            0
        );

        do {

            if (isValidAutomorphism(permutation)) {
                automorphisms.push_back(permutation);
            }

        } while (
            next_permutation(
                permutation.begin(),
                permutation.end()
            )
        );

        cout << "Total automorphisms: "
             << automorphisms.size() << "\n";

        for (int i = 0; i < (int)automorphisms.size(); i++) {

            cout << "Automorphism " << i + 1 << ": ";

            for (int vertex = 0; vertex < V; vertex++) {
                cout << vertex << "->"
                     << automorphisms[i][vertex] << " ";
            }

            cout << "\n";
        }
    }

    void displayExactOrbits() {

        cout << "\n========== EXACT AUTOMORPHISM ORBITS ==========\n";

        vector<bool> visited(V, false);

        for (int vertex = 0; vertex < V; vertex++) {

            if (visited[vertex]) {
                continue;
            }

            set<int> orbit;

            for (const auto& permutation : automorphisms) {
                orbit.insert(permutation[vertex]);
            }

            cout << "Orbit of vertex " << vertex << ": { ";

            for (int member : orbit) {
                cout << member << " ";
                visited[member] = true;
            }

            cout << "}\n";
        }
    }

    void compareResults() {

        cout << "\n========== COMPARISON ==========\n";

        vector<int> finalColors = refinementHistory.back();

        map<int, set<int>> wlClasses;

        for (int i = 0; i < V; i++) {
            wlClasses[finalColors[i]].insert(i);
        }

        vector<set<int>> exactOrbits;
        vector<bool> visited(V, false);

        for (int vertex = 0; vertex < V; vertex++) {

            if (visited[vertex]) {
                continue;
            }

            set<int> orbit;

            for (const auto& permutation : automorphisms) {
                orbit.insert(permutation[vertex]);
            }

            for (int member : orbit) {
                visited[member] = true;
            }

            exactOrbits.push_back(orbit);
        }

        cout << "WL color classes: "
             << wlClasses.size() << "\n";

        cout << "Exact automorphism orbits: "
             << exactOrbits.size() << "\n";

        cout << "\nObservation:\n";

        cout << "Vertices in the same exact automorphism orbit "
             << "must have the same stable WL color.\n";

        cout << "However, the reverse is not always true.\n";

        bool matches = true;

        for (const auto& orbit : exactOrbits) {

            int expectedColor = -1;

            for (int vertex : orbit) {

                if (expectedColor == -1) {
                    expectedColor = finalColors[vertex];
                }
                else if (finalColors[vertex] != expectedColor) {
                    matches = false;
                }
            }
        }

        if (matches) {
            cout << "\nWL refinement did not split any "
                 << "exact automorphism orbit.\n";
        }
        else {
            cout << "\nUnexpected mismatch detected. "
                 << "Check the implementation.\n";
        }
    }
};

int main() {

    int V, E;

    cout << "WEISFEILER-LEMAN COLOR REFINEMENT\n";

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
            cout << "Invalid vertex. Enter this edge again.\n";
            i--;
            continue;
        }

        if (u == v) {
            cout << "Self-loops are not allowed. Try again.\n";
            i--;
            continue;
        }

        if (u > v) {
            swap(u, v);
        }

        if (existingEdges.count({u, v})) {
            cout << "Duplicate edge. Try again.\n";
            i--;
            continue;
        }

        existingEdges.insert({u, v});

        graph.addEdge(u, v);
    }

    graph.displayGraph();

    graph.colorRefinement();

    graph.findAutomorphisms();

    graph.displayExactOrbits();

    graph.compareResults();

    cout << "\nProgram completed successfully.\n";

    return 0;
}
