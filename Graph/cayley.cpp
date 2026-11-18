#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <queue>
#include <limits>
using namespace std;

using Permutation = vector<int>;

class CayleyGraph {
private:
    int n;
    vector<vector<int>> original;
    vector<int> degree;

    Permutation mapping;
    vector<bool> used;

    vector<Permutation> automorphisms;
    map<Permutation, int> indexOf;

    vector<vector<int>> cayley;
    vector<vector<int>> matrix;

    set<int> generators;
    set<int> symmetricGenerators;

    int identityIndex = -1;

    bool compatible(int vertex, int candidate) {
        if (degree[vertex] != degree[candidate]) {
            return false;
        }

        for (int previous = 0; previous < vertex; previous++) {
            if (original[vertex][previous] !=
                original[candidate][mapping[previous]]) {
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

    Permutation compose(const Permutation& p,
                        const Permutation& q) const {
        Permutation result(n);

        // p o q: apply q first, then p.
        for (int i = 0; i < n; i++) {
            result[i] = p[q[i]];
        }

        return result;
    }

    Permutation inverse(const Permutation& p) const {
        Permutation result(n);

        for (int i = 0; i < n; i++) {
            result[p[i]] = i;
        }

        return result;
    }

    void printPermutation(const Permutation& p) const {
        cout << "[";

        for (int i = 0; i < n; i++) {
            if (i > 0) {
                cout << " ";
            }

            cout << p[i];
        }

        cout << "]";
    }

public:
    CayleyGraph(int vertices) : n(vertices) {
        original.assign(n, vector<int>(n, 0));
        degree.assign(n, 0);

        mapping.assign(n, -1);
        used.assign(n, false);
    }

    bool addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        if (u == v || original[u][v] == 1) {
            return false;
        }

        original[u][v] = 1;
        original[v][u] = 1;

        degree[u]++;
        degree[v]++;

        return true;
    }

    void findAutomorphisms() {
        automorphisms.clear();
        indexOf.clear();

        backtrack(0);

        sort(automorphisms.begin(), automorphisms.end());

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            indexOf[automorphisms[i]] = i;
        }

        Permutation identity(n);
        iota(identity.begin(), identity.end(), 0);

        identityIndex = indexOf.at(identity);
    }

    void displayAutomorphisms() const {
        cout << "\nAUTOMORPHISM GROUP\n";

        cout << "Group order: "
             << automorphisms.size() << "\n";

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            cout << "G" << i << " = ";
            printPermutation(automorphisms[i]);

            if (i == identityIndex) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    int groupSize() const {
        return (int)automorphisms.size();
    }

    bool selectGenerators(const vector<int>& selected) {
        generators.clear();
        symmetricGenerators.clear();

        for (int id : selected) {
            if (id < 0 || id >= groupSize()) {
                return false;
            }

            if (id == identityIndex) {
                return false;
            }

            generators.insert(id);
        }

        for (int id : generators) {
            symmetricGenerators.insert(id);

            Permutation inv = inverse(automorphisms[id]);
            int inverseId = indexOf.at(inv);

            if (inverseId != identityIndex) {
                symmetricGenerators.insert(inverseId);
            }
        }

        return true;
    }

    void displayGenerators() const {
        cout << "\nSELECTED GENERATORS\n";

        if (generators.empty()) {
            cout << "No generators selected.\n";
        } else {
            for (int id : generators) {
                cout << "G" << id << " ";
            }
            cout << "\n";
        }

        cout << "Generators including inverses: ";

        if (symmetricGenerators.empty()) {
            cout << "(empty)";
        } else {
            for (int id : symmetricGenerators) {
                cout << "G" << id << " ";
            }
        }

        cout << "\n";
    }

    void constructCayleyGraph() {
        int size = groupSize();

        cayley.assign(size, vector<int>());
        matrix.assign(size, vector<int>(size, 0));

        for (int g = 0; g < size; g++) {
            for (int s : symmetricGenerators) {
                Permutation result =
                    compose(automorphisms[g], automorphisms[s]);

                int destination = indexOf.at(result);

                // The identity generator was excluded,
                // so no self-loop should be created.
                if (destination != g) {
                    matrix[g][destination] = 1;
                    matrix[destination][g] = 1;
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] == 1) {
                    cayley[i].push_back(j);
                }
            }
        }
    }

    void displayAdjacencyList() const {
        cout << "\nCAYLEY GRAPH ADJACENCY LIST\n";

        for (int i = 0; i < groupSize(); i++) {
            cout << "G" << i << " -> ";

            if (cayley[i].empty()) {
                cout << "(none)";
            } else {
                for (int neighbor : cayley[i]) {
                    cout << "G" << neighbor << " ";
                }
            }

            cout << "\n";
        }
    }

    void displayAdjacencyMatrix() const {
        if (groupSize() > 15) {
            cout << "\nAdjacency matrix skipped "
                 << "(more than 15 group elements).\n";
            return;
        }

        cout << "\nCAYLEY GRAPH ADJACENCY MATRIX\n";

        for (const auto& row : matrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << "\n";
        }
    }

    void analyzeUsingBFS() const {
        int size = groupSize();

        vector<int> distance(size, -1);
        vector<int> parent(size, -1);

        queue<int> q;

        distance[identityIndex] = 0;
        q.push(identityIndex);

        int reached = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            reached++;

            for (int neighbor : cayley[current]) {
                if (distance[neighbor] != -1) {
                    continue;
                }

                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;

                q.push(neighbor);
            }
        }

        cout << "\nBFS FROM IDENTITY\n";

        cout << "Identity: G" << identityIndex << "\n";

        for (int i = 0; i < size; i++) {
            cout << "G" << i << " : ";

            if (distance[i] == -1) {
                cout << "Unreachable";
            } else {
                cout << "Distance = " << distance[i];
            }

            cout << "\n";
        }

        cout << "\nGROUP GENERATION ANALYSIS\n";

        cout << "Reachable elements: "
             << reached << " / " << size << "\n";

        if (reached == size) {
            cout << "Cayley graph is connected.\n";
            cout << "Selected generators generate "
                 << "the entire automorphism group.\n";
        } else {
            cout << "Cayley graph is disconnected.\n";
            cout << "Selected generators generate "
                 << "a proper subgroup.\n";
        }

        int diameterFromIdentity = 0;

        for (int d : distance) {
            if (d > diameterFromIdentity) {
                diameterFromIdentity = d;
            }
        }

        cout << "Maximum distance from identity "
             << "among reachable elements: "
             << diameterFromIdentity << "\n";
    }

    void displayStatistics() const {
        int size = groupSize();
        long long edgeCount = 0;

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                edgeCount += matrix[i][j];
            }
        }

        cout << "\nCAYLEY GRAPH STATISTICS\n";

        cout << "Vertices: " << size << "\n";
        cout << "Edges: " << edgeCount << "\n";

        if (size > 0) {
            cout << "Degree of each vertex: "
                 << cayley[0].size() << "\n";
        }
    }
};

int main() {
    int n, m;

    cout << "CAYLEY GRAPH OF AN AUTOMORPHISM GROUP\n";

    cout << "Enter number of vertices (1 to 6): ";
    if (!(cin >> n) || n < 1 || n > 6) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "Enter number of edges: ";
    if (!(cin >> m) || m < 0 || m > n * (n - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 1;
    }

    CayleyGraph graph(n);

    cout << "Enter edges (u v):\n";

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

    int count;

    cout << "\nEnter number of generators: ";

    if (!(cin >> count) ||
        count < 0 ||
        count > graph.groupSize() - 1) {
        cout << "Invalid generator count.\n";
        return 1;
    }

    vector<int> selected(count);

    cout << "Enter generator IDs (without G):\n";

    for (int i = 0; i < count; i++) {
        if (!(cin >> selected[i])) {
            cout << "Invalid generator input.\n";
            return 1;
        }
    }

    if (!graph.selectGenerators(selected)) {
        cout << "Invalid generator selection.\n";
        return 1;
    }

    graph.displayGenerators();

    graph.constructCayleyGraph();

    graph.displayAdjacencyList();
    graph.displayAdjacencyMatrix();
    graph.displayStatistics();
    graph.analyzeUsingBFS();

    return 0;
}
