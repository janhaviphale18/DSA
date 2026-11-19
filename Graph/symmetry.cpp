#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

using Permutation = vector<int>;

class GraphSymmetry {
private:
    int n;

    vector<vector<int>> adj;
    vector<int> degree;
    vector<int> color;

    vector<int> mapping;
    vector<bool> used;

    vector<Permutation> allAutomorphisms;
    vector<Permutation> coloredAutomorphisms;

    bool compatible(int vertex, int candidate,
                    bool preserveColors) const {

        // Degree must be preserved.
        if (degree[vertex] != degree[candidate]) {
            return false;
        }

        // Colors must match when color preservation is required.
        if (preserveColors &&
            color[vertex] != color[candidate]) {
            return false;
        }

        // Adjacency with previously mapped vertices must be preserved.
        for (int previous = 0; previous < vertex; previous++) {
            if (adj[vertex][previous] !=
                adj[candidate][mapping[previous]]) {
                return false;
            }
        }

        return true;
    }

    void backtrack(int vertex, bool preserveColors,
                   vector<Permutation>& result) {

        if (vertex == n) {
            result.push_back(mapping);
            return;
        }

        for (int candidate = 0; candidate < n; candidate++) {
            if (used[candidate]) {
                continue;
            }

            if (!compatible(vertex, candidate, preserveColors)) {
                continue;
            }

            mapping[vertex] = candidate;
            used[candidate] = true;

            backtrack(vertex + 1, preserveColors, result);

            used[candidate] = false;
            mapping[vertex] = -1;
        }
    }

    vector<vector<int>> calculateOrbits(
        const vector<Permutation>& group) const {

        vector<vector<int>> orbits;
        set<int> unseen;

        for (int i = 0; i < n; i++) {
            unseen.insert(i);
        }

        while (!unseen.empty()) {
            int representative = *unseen.begin();

            set<int> orbit;

            for (const auto& p : group) {
                orbit.insert(p[representative]);
            }

            vector<int> currentOrbit;

            for (int vertex : orbit) {
                currentOrbit.push_back(vertex);
                unseen.erase(vertex);
            }

            orbits.push_back(currentOrbit);
        }

        return orbits;
    }

    void displayOrbits(
        const vector<vector<int>>& orbits,
        const string& heading) const {

        cout << "\n" << heading << "\n";

        for (int i = 0; i < (int)orbits.size(); i++) {
            cout << "Orbit " << i + 1 << ": { ";

            for (int vertex : orbits[i]) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    void displayAutomorphisms(
        const vector<Permutation>& group,
        const string& heading) const {

        cout << "\n" << heading << "\n";

        cout << "Number of automorphisms: "
             << group.size() << "\n";

        for (int i = 0; i < (int)group.size(); i++) {
            cout << "G" << i << " = [ ";

            for (int value : group[i]) {
                cout << value << " ";
            }

            cout << "]\n";
        }
    }

public:
    GraphSymmetry(int vertices) {
        n = vertices;

        adj.assign(n, vector<int>(n, 0));
        degree.assign(n, 0);
        color.assign(n, 0);

        mapping.assign(n, -1);
        used.assign(n, false);
    }

    bool addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        if (u == v || adj[u][v] == 1) {
            return false;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;

        degree[u]++;
        degree[v]++;

        return true;
    }

    void setColor(int vertex, int assignedColor) {
        color[vertex] = assignedColor;
    }

    void displayColors() const {
        cout << "\nVERTEX COLORS\n";

        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i
                 << " -> Color " << color[i] << "\n";
        }
    }

    void findAutomorphisms() {
        allAutomorphisms.clear();
        coloredAutomorphisms.clear();

        fill(mapping.begin(), mapping.end(), -1);
        fill(used.begin(), used.end(), false);

        // Find all automorphisms without considering colors.
        backtrack(0, false, allAutomorphisms);

        // Reset backtracking state.
        fill(mapping.begin(), mapping.end(), -1);
        fill(used.begin(), used.end(), false);

        // Find only color-preserving automorphisms.
        backtrack(0, true, coloredAutomorphisms);

        sort(allAutomorphisms.begin(), allAutomorphisms.end());
        sort(coloredAutomorphisms.begin(),
             coloredAutomorphisms.end());
    }

    void analyze() const {
        displayAutomorphisms(
            allAutomorphisms,
            "ORIGINAL AUTOMORPHISM GROUP"
        );

        displayAutomorphisms(
            coloredAutomorphisms,
            "COLOR-PRESERVING AUTOMORPHISM GROUP"
        );

        vector<vector<int>> originalOrbits =
            calculateOrbits(allAutomorphisms);

        vector<vector<int>> coloredOrbits =
            calculateOrbits(coloredAutomorphisms);

        displayOrbits(
            originalOrbits,
            "ORIGINAL VERTEX ORBITS"
        );

        displayOrbits(
            coloredOrbits,
            "VERTEX ORBITS AFTER COLORING"
        );

        cout << "\nSYMMETRY BREAKING ANALYSIS\n";

        cout << "Original automorphism count: "
             << allAutomorphisms.size() << "\n";

        cout << "Color-preserving automorphism count: "
             << coloredAutomorphisms.size() << "\n";

        cout << "Original orbit count: "
             << originalOrbits.size() << "\n";

        cout << "Colored orbit count: "
             << coloredOrbits.size() << "\n";

        if (coloredAutomorphisms.size() <
            allAutomorphisms.size()) {

            cout << "Coloring reduced the number "
                 << "of graph symmetries.\n";
        } else {
            cout << "Coloring did not reduce the "
                 << "number of automorphisms.\n";
        }

        if (coloredOrbits.size() > originalOrbits.size()) {
            cout << "Some previously equivalent vertices "
                 << "are now distinguishable.\n";
        } else {
            cout << "The number of vertex orbits did not increase.\n";
        }
    }
};

int main() {
    int n, m;

    cout << "GRAPH SYMMETRY BREAKING USING VERTEX COLORING\n";

    cout << "Enter number of vertices (1 to 8): ";

    if (!(cin >> n) || n < 1 || n > 8) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "Enter number of edges: ";

    if (!(cin >> m) || m < 0 || m > n * (n - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 1;
    }

    GraphSymmetry graph(n);

    cout << "Enter edges (u v), using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {
        int u, v;

        if (!(cin >> u >> v)) {
            cout << "Invalid input.\n";
            return 1;
        }

        if (!graph.addEdge(u, v)) {
            cout << "Invalid or duplicate edge.\n";
            return 1;
        }
    }

    cout << "\nAssign a positive integer color to each vertex.\n";

    for (int i = 0; i < n; i++) {
        int assignedColor;

        cout << "Enter color of vertex " << i << ": ";

        if (!(cin >> assignedColor) || assignedColor < 1) {
            cout << "Invalid color. Use a positive integer.\n";
            return 1;
        }

        graph.setColor(i, assignedColor);
    }

    graph.displayColors();

    graph.findAutomorphisms();
    graph.analyze();

    cout << "\nGraph symmetry analysis completed.\n";

    return 0;
}
