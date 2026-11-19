#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

using Permutation = vector<int>;
using Edge = pair<int, int>;

class GraphGroupAction {
private:
    int n;

    vector<vector<int>> adj;
    vector<int> degree;

    vector<int> mapping;
    vector<bool> used;

    vector<Permutation> automorphisms;

    vector<vector<int>> vertexOrbits;
    vector<vector<Edge>> edgeOrbits;
    vector<vector<Edge>> nonedgeOrbits;

    bool compatible(int vertex, int candidate) const {
        if (degree[vertex] != degree[candidate]) {
            return false;
        }

        for (int previous = 0; previous < vertex; previous++) {
            if (adj[vertex][previous] !=
                adj[candidate][mapping[previous]]) {
                return false;
            }
        }

        return true;
    }

    void backtrack(int vertex) {
        if (vertex == n) {
            automorphisms.push_back(mapping);
            return;
        }

        for (int candidate = 0; candidate < n; candidate++) {
            if (used[candidate]) {
                continue;
            }

            if (!compatible(vertex, candidate)) {
                continue;
            }

            mapping[vertex] = candidate;
            used[candidate] = true;

            backtrack(vertex + 1);

            used[candidate] = false;
            mapping[vertex] = -1;
        }
    }

    Edge transformEdge(const Permutation& p, Edge e) const {
        int u = p[e.first];
        int v = p[e.second];

        if (u > v) {
            swap(u, v);
        }

        return {u, v};
    }

    void printEdge(Edge e) const {
        cout << "(" << e.first << ", " << e.second << ")";
    }

    void printEdges(const vector<Edge>& objects) const {
        cout << "{ ";

        for (Edge e : objects) {
            printEdge(e);
            cout << " ";
        }

        cout << "}";
    }

    int vertexStabilizerSize(int vertex) const {
        int count = 0;

        for (const auto& p : automorphisms) {
            if (p[vertex] == vertex) {
                count++;
            }
        }

        return count;
    }

    int edgeStabilizerSize(Edge edge) const {
        int count = 0;

        for (const auto& p : automorphisms) {
            Edge transformed = transformEdge(p, edge);

            if (transformed == edge) {
                count++;
            }
        }

        return count;
    }

public:
    GraphGroupAction(int vertices) {
        n = vertices;

        adj.assign(n, vector<int>(n, 0));
        degree.assign(n, 0);

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

    void findAutomorphisms() {
        automorphisms.clear();
        backtrack(0);

        sort(automorphisms.begin(), automorphisms.end());
    }

    int groupSize() const {
        return (int)automorphisms.size();
    }

    void displayAutomorphisms() const {
        cout << "\nAUTOMORPHISM GROUP\n";
        cout << "Group order: " << groupSize() << "\n";

        for (int i = 0; i < groupSize(); i++) {
            cout << "G" << i << " = [ ";

            for (int value : automorphisms[i]) {
                cout << value << " ";
            }

            cout << "]\n";
        }
    }

    void calculateVertexOrbits() {
        vertexOrbits.clear();

        set<int> unseen;

        for (int i = 0; i < n; i++) {
            unseen.insert(i);
        }

        while (!unseen.empty()) {
            int representative = *unseen.begin();

            set<int> orbit;

            for (const auto& p : automorphisms) {
                orbit.insert(p[representative]);
            }

            vector<int> currentOrbit;

            for (int vertex : orbit) {
                currentOrbit.push_back(vertex);
                unseen.erase(vertex);
            }

            vertexOrbits.push_back(currentOrbit);
        }
    }

    void calculatePairOrbits() {
        edgeOrbits.clear();
        nonedgeOrbits.clear();

        set<Edge> unseenEdges;
        set<Edge> unseenNonedges;

        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                if (adj[u][v] == 1) {
                    unseenEdges.insert({u, v});
                } else {
                    unseenNonedges.insert({u, v});
                }
            }
        }

        // Calculate edge orbits.
        while (!unseenEdges.empty()) {
            Edge representative = *unseenEdges.begin();

            set<Edge> orbit;

            for (const auto& p : automorphisms) {
                orbit.insert(transformEdge(p, representative));
            }

            vector<Edge> currentOrbit;

            for (Edge e : orbit) {
                currentOrbit.push_back(e);
                unseenEdges.erase(e);
            }

            edgeOrbits.push_back(currentOrbit);
        }

        // Calculate nonedge orbits.
        while (!unseenNonedges.empty()) {
            Edge representative = *unseenNonedges.begin();

            set<Edge> orbit;

            for (const auto& p : automorphisms) {
                orbit.insert(transformEdge(p, representative));
            }

            vector<Edge> currentOrbit;

            for (Edge e : orbit) {
                currentOrbit.push_back(e);
                unseenNonedges.erase(e);
            }

            nonedgeOrbits.push_back(currentOrbit);
        }
    }

    void displayVertexOrbits() const {
        cout << "\nVERTEX ORBITS\n";

        for (int i = 0; i < (int)vertexOrbits.size(); i++) {
            cout << "Orbit " << i + 1 << ": { ";

            for (int vertex : vertexOrbits[i]) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    void displayEdgeOrbits() const {
        cout << "\nEDGE ORBITS\n";

        for (int i = 0; i < (int)edgeOrbits.size(); i++) {
            cout << "Orbit " << i + 1 << ": ";
            printEdges(edgeOrbits[i]);
            cout << "\n";
        }
    }

    void displayNonedgeOrbits() const {
        cout << "\nNONEDGE ORBITS\n";

        for (int i = 0; i < (int)nonedgeOrbits.size(); i++) {
            cout << "Orbit " << i + 1 << ": ";
            printEdges(nonedgeOrbits[i]);
            cout << "\n";
        }
    }

    void verifyVertexOrbitStabilizer() const {
        cout << "\nVERTEX ORBIT-STABILIZER VERIFICATION\n";

        bool allValid = true;

        for (int i = 0; i < (int)vertexOrbits.size(); i++) {
            int representative = vertexOrbits[i][0];

            int orbitSize = (int)vertexOrbits[i].size();
            int stabilizerSize =
                vertexStabilizerSize(representative);

            cout << "Representative: " << representative << "\n";

            cout << "Orbit size: " << orbitSize << "\n";
            cout << "Stabilizer size: " << stabilizerSize << "\n";

            cout << "Product: " << orbitSize
                 << " x " << stabilizerSize
                 << " = " << orbitSize * stabilizerSize << "\n";

            if (orbitSize * stabilizerSize != groupSize()) {
                allValid = false;
            }

            cout << "\n";
        }

        cout << (allValid
                 ? "All vertex checks passed.\n"
                 : "A vertex check failed.\n");
    }

    void verifyPairOrbitStabilizer(
        const vector<vector<Edge>>& orbits,
        const string& type) const {

        cout << "\n" << type
             << " ORBIT-STABILIZER VERIFICATION\n";

        bool allValid = true;

        for (int i = 0; i < (int)orbits.size(); i++) {
            Edge representative = orbits[i][0];

            int orbitSize = (int)orbits[i].size();
            int stabilizerSize =
                edgeStabilizerSize(representative);

            cout << "Representative: ";
            printEdge(representative);
            cout << "\n";

            cout << "Orbit size: " << orbitSize << "\n";
            cout << "Stabilizer size: " << stabilizerSize << "\n";

            cout << "Product: " << orbitSize
                 << " x " << stabilizerSize
                 << " = " << orbitSize * stabilizerSize << "\n";

            if (orbitSize * stabilizerSize != groupSize()) {
                allValid = false;
            }

            cout << "\n";
        }

        cout << (allValid
                 ? "All " + type + " checks passed.\n"
                 : type + " check failed.\n");
    }

    void displaySummary() const {
        cout << "\nGROUP ACTION SUMMARY\n";

        cout << "Automorphism group order: "
             << groupSize() << "\n";

        cout << "Number of vertex orbits: "
             << vertexOrbits.size() << "\n";

        cout << "Number of edge orbits: "
             << edgeOrbits.size() << "\n";

        cout << "Number of nonedge orbits: "
             << nonedgeOrbits.size() << "\n";
    }
};

int main() {
    int n, m;

    cout << "GRAPH GROUP ACTIONS AND ORBITS\n";

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

    GraphGroupAction graph(n);

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

    graph.findAutomorphisms();

    graph.displayAutomorphisms();

    graph.calculateVertexOrbits();
    graph.calculatePairOrbits();

    graph.displayVertexOrbits();
    graph.displayEdgeOrbits();
    graph.displayNonedgeOrbits();

    graph.verifyVertexOrbitStabilizer();

    graph.verifyPairOrbitStabilizer(
        vector<vector<Edge>>{}, "EMPTY"
    );

    graph.verifyPairOrbitStabilizer(
        vector<vector<Edge>>{}, "EMPTY"
    );

    graph.displaySummary();

    cout << "\nGroup action analysis completed.\n";

    return 0;
}
