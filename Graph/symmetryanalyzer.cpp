#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

class Graph {
private:
    int V;
    int E;

    vector<vector<int>> adj;

    vector<int> degrees;
    vector<int> colors;

    vector<vector<int>> automorphisms;

    vector<set<int>> exactOrbits;

    int totalAutomorphisms = 0;

public:

    Graph(int vertices, int edges) {

        V = vertices;
        E = edges;

        adj.assign(V, vector<int>(V, 0));

        degrees.assign(V, 0);

        colors.assign(V, 0);
    }

    // Add an undirected edge.
    void addEdge(int u, int v) {

        adj[u][v] = 1;
        adj[v][u] = 1;

        degrees[u]++;
        degrees[v]++;
    }

    // Display the adjacency matrix.
    void displayGraph() {

        cout << "\n========== GRAPH REPRESENTATION ==========\n";

        cout << "Vertices: " << V << "\n";
        cout << "Edges: " << E << "\n";

        cout << "\nAdjacency Matrix:\n";

        cout << "    ";

        for (int i = 0; i < V; i++) {
            cout << setw(4) << i;
        }

        cout << "\n";

        for (int i = 0; i < V; i++) {

            cout << setw(4) << i;

            for (int j = 0; j < V; j++) {
                cout << setw(4) << adj[i][j];
            }

            cout << "\n";
        }
    }

    // Calculate and display vertex degrees.
    void analyzeDegrees() {

        cout << "\n========== VERTEX DEGREE ANALYSIS ==========\n";

        for (int i = 0; i < V; i++) {

            cout << "Vertex " << i
                 << " -> Degree: " << degrees[i] << "\n";
        }

        map<int, vector<int>> degreeGroups;

        for (int i = 0; i < V; i++) {
            degreeGroups[degrees[i]].push_back(i);
        }

        cout << "\nDegree-based groups:\n";

        for (const auto& group : degreeGroups) {

            cout << "Degree " << group.first << ": { ";

            for (int vertex : group.second) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    // Count distinct colors.
    int countColorClasses(const vector<int>& currentColors) {

        set<int> uniqueColors(
            currentColors.begin(),
            currentColors.end()
        );

        return uniqueColors.size();
    }

    // Display color groups.
    void displayColorGroups() {

        map<int, vector<int>> groups;

        for (int i = 0; i < V; i++) {
            groups[colors[i]].push_back(i);
        }

        for (const auto& group : groups) {

            cout << "Color " << group.first << ": { ";

            for (int vertex : group.second) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    // Perform 1-WL color refinement.
    void performWLRefinement() {

        cout << "\n========== 1-WL COLOR REFINEMENT ==========\n";

        // Initially all vertices receive color 0.
        colors.assign(V, 0);

        cout << "\nInitial colors:\n";

        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " -> Color 0\n";
        }

        int iteration = 1;

        while (iteration <= V) {

            vector<pair<int, vector<int>>> signatures(V);

            // Construct a signature for every vertex.
            for (int i = 0; i < V; i++) {

                vector<int> neighbourColors;

                for (int j = 0; j < V; j++) {

                    if (adj[i][j] == 1) {
                        neighbourColors.push_back(colors[j]);
                    }
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

            int oldClasses = countColorClasses(colors);

            int newClasses = countColorClasses(newColors);

            colors = newColors;

            cout << "\nIteration " << iteration << ":\n";

            for (int i = 0; i < V; i++) {

                cout << "Vertex " << i
                     << " -> Color " << colors[i] << "\n";
            }

            cout << "Color classes: " << newClasses << "\n";

            if (oldClasses == newClasses) {

                cout << "\nStable color partition reached.\n";

                break;
            }

            iteration++;
        }

        cout << "\nFinal WL color groups:\n";

        displayColorGroups();
    }

    // Verify whether a permutation is an automorphism.
    bool isAutomorphism(const vector<int>& permutation) {

        for (int u = 0; u < V; u++) {

            for (int v = 0; v < V; v++) {

                if (
                    adj[u][v] !=
                    adj[permutation[u]][permutation[v]]
                ) {
                    return false;
                }
            }
        }

        return true;
    }

    // Find every graph automorphism.
    void findAutomorphisms() {

        cout << "\n========== GRAPH AUTOMORPHISM ANALYSIS ==========\n";

        vector<int> permutation(V);

        iota(
            permutation.begin(),
            permutation.end(),
            0
        );

        do {

            if (isAutomorphism(permutation)) {

                automorphisms.push_back(permutation);
            }

        } while (
            next_permutation(
                permutation.begin(),
                permutation.end()
            )
        );

        totalAutomorphisms = automorphisms.size();

        cout << "Total graph automorphisms: "
             << totalAutomorphisms << "\n";

        cout << "\nValid automorphism mappings:\n";

        for (int i = 0; i < totalAutomorphisms; i++) {

            cout << "Automorphism " << i + 1 << ": ";

            for (int vertex = 0; vertex < V; vertex++) {

                cout << vertex << "->"
                     << automorphisms[i][vertex] << " ";
            }

            cout << "\n";
        }
    }

    // Calculate exact automorphism orbits.
    void calculateOrbits() {

        cout << "\n========== AUTOMORPHISM ORBITS ==========\n";

        vector<bool> visited(V, false);

        exactOrbits.clear();

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

        for (int i = 0; i < (int)exactOrbits.size(); i++) {

            cout << "Orbit " << i + 1 << ": { ";

            for (int vertex : exactOrbits[i]) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    // Calculate stabilizer size using Orbit-Stabilizer Theorem.
    void calculateStabilizers() {

        cout << "\n========== STABILIZER ANALYSIS ==========\n";

        for (int vertex = 0; vertex < V; vertex++) {

            int orbitSize = 0;

            for (const auto& orbit : exactOrbits) {

                if (orbit.count(vertex)) {
                    orbitSize = orbit.size();
                    break;
                }
            }

            int stabilizerSize =
                totalAutomorphisms / orbitSize;

            cout << "Vertex " << vertex
                 << ":\n";

            cout << "  Orbit size: "
                 << orbitSize << "\n";

            cout << "  Stabilizer size: "
                 << stabilizerSize << "\n";

            cout << "  Verification: "
                 << orbitSize << " x "
                 << stabilizerSize << " = "
                 << totalAutomorphisms << "\n";
        }
    }

    // Construct quotient graph using final WL color classes.
    void constructQuotientGraph() {

        cout << "\n========== QUOTIENT GRAPH ==========\n";

        map<int, vector<int>> groups;

        for (int i = 0; i < V; i++) {
            groups[colors[i]].push_back(i);
        }

        int K = groups.size();

        vector<vector<int>> quotient(
            K,
            vector<int>(K, 0)
        );

        vector<int> representative(K, -1);

        for (const auto& group : groups) {

            int color = group.first;

            representative[color] = group.second[0];
        }

        // Count neighbours in each color class.
        for (int i = 0; i < K; i++) {

            int vertex = representative[i];

            for (int j = 0; j < K; j++) {

                for (int neighbour = 0; neighbour < V; neighbour++) {

                    if (
                        adj[vertex][neighbour] == 1 &&
                        colors[neighbour] == j
                    ) {
                        quotient[i][j]++;
                    }
                }
            }
        }

        cout << "Number of quotient vertices: " << K << "\n";

        cout << "\nQuotient adjacency matrix:\n";

        cout << "    ";

        for (int j = 0; j < K; j++) {
            cout << setw(4) << j;
        }

        cout << "\n";

        for (int i = 0; i < K; i++) {

            cout << setw(4) << i;

            for (int j = 0; j < K; j++) {
                cout << setw(4) << quotient[i][j];
            }

            cout << "\n";
        }

        cout << "\nQuotient vertices represent:\n";

        for (const auto& group : groups) {

            cout << "Quotient vertex " << group.first
                 << " -> { ";

            for (int vertex : group.second) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    // Compare exact automorphism orbits and WL color classes.
    void compareSymmetryResults() {

        cout << "\n========== SYMMETRY COMPARISON ==========\n";

        bool valid = true;

        for (const auto& orbit : exactOrbits) {

            int expectedColor = -1;

            for (int vertex : orbit) {

                if (expectedColor == -1) {
                    expectedColor = colors[vertex];
                }
                else if (colors[vertex] != expectedColor) {
                    valid = false;
                }
            }
        }

        if (valid) {

            cout << "Every exact automorphism orbit "
                 << "is contained in a WL color class.\n";
        }
        else {

            cout << "Unexpected inconsistency detected.\n";
        }

        cout << "\nWL color classes: "
             << countColorClasses(colors) << "\n";

        cout << "Exact automorphism orbits: "
             << exactOrbits.size() << "\n";

        if (
            countColorClasses(colors) ==
            (int)exactOrbits.size()
        ) {

            cout << "\nThe two partitions have the same "
                 << "number of classes.\n";

            cout << "Check the displayed groups to confirm "
                 << "whether they are identical.\n";
        }
        else {

            cout << "\nThe WL partition and exact orbit "
                 << "partition have different numbers of classes.\n";
        }

        cout << "\nRemember: identical WL colors do not "
             << "necessarily imply an exact automorphism.\n";
    }

    // Display a consolidated report.
    void displayFinalReport() {

        cout << "\n========== COMPLETE SYMMETRY REPORT ==========\n";

        cout << "Number of vertices: "
             << V << "\n";

        cout << "Number of edges: "
             << E << "\n";

        cout << "Total automorphisms: "
             << totalAutomorphisms << "\n";

        cout << "WL color classes: "
             << countColorClasses(colors) << "\n";

        cout << "Exact automorphism orbits: "
             << exactOrbits.size() << "\n";

        cout << "\nGraph symmetry analysis completed.\n";
    }
};

int main() {

    int V, E;

    cout << "============================================\n";
    cout << "       COMPLETE GRAPH SYMMETRY ANALYZER\n";
    cout << "============================================\n";

    cout << "\nEnter number of vertices (maximum 8): ";
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

    Graph graph(V, E);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter edges (u v):\n";

    for (int i = 0; i < E; i++) {

        int u, v;

        cin >> u >> v;

        if (
            u < 0 || u >= V ||
            v < 0 || v >= V
        ) {

            cout << "Invalid vertex. Enter edge again.\n";

            i--;

            continue;
        }

        if (u == v) {

            cout << "Self-loops are not allowed.\n";

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

    // Execute all graph symmetry analyses.
    graph.displayGraph();

    graph.analyzeDegrees();

    graph.performWLRefinement();

    graph.findAutomorphisms();

    graph.calculateOrbits();

    graph.calculateStabilizers();

    graph.constructQuotientGraph();

    graph.compareSymmetryResults();

    graph.displayFinalReport();

    cout << "\nProgram completed successfully.\n";

    return 0;
}
