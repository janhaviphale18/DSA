#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>
#include <map>
using namespace std;

const int MAX_VERTICES = 9;

using Graph = vector<vector<bool>>;

using Permutation = vector<int>;

using AutomorphismGroup = vector<Permutation>;

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

// Verify whether a permutation is an automorphism
bool isAutomorphism(
    const Graph& graph,
    const Permutation& permutation
) {

    int n = graph.size();

    vector<bool> used(n, false);

    // Verify that the permutation is bijective
    for (int vertex : permutation) {

        if (vertex < 0 || vertex >= n ||
            used[vertex]) {

            return false;
        }

        used[vertex] = true;
    }

    // Verify preservation of adjacency and non-adjacency
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (graph[i][j] !=
                graph[permutation[i]][permutation[j]]) {

                return false;
            }
        }
    }

    return true;
}

// Find all automorphisms using backtracking
AutomorphismGroup findAutomorphisms(
    const Graph& graph
) {

    int n = graph.size();

    vector<int> degree = calculateDegrees(graph);

    vector<int> order(n);

    iota(order.begin(), order.end(), 0);

    // Process higher-degree vertices first
    sort(order.begin(), order.end(),
        [&](int a, int b) {

            return degree[a] > degree[b];
        }
    );

    Permutation permutation(n, -1);

    vector<bool> used(n, false);

    AutomorphismGroup group;

    function<void(int)> search = [&](int index) {

        if (index == n) {

            if (isAutomorphism(graph, permutation)) {

                group.push_back(permutation);
            }

            return;
        }

        int u = order[index];

        for (int v = 0; v < n; v++) {

            if (used[v]) {
                continue;
            }

            // Automorphisms preserve vertex degrees
            if (degree[u] != degree[v]) {
                continue;
            }

            bool compatible = true;

            // Check relationships with previously mapped vertices
            for (int i = 0; i < index; i++) {

                int previousU = order[i];

                int previousV = permutation[previousU];

                if (graph[u][previousU] !=
                    graph[v][previousV]) {

                    compatible = false;
                    break;
                }
            }

            if (!compatible) {
                continue;
            }

            permutation[u] = v;

            used[v] = true;

            search(index + 1);

            // Backtracking
            permutation[u] = -1;

            used[v] = false;
        }
    };

    search(0);

    return group;
}

// Find the orbit of a vertex
set<int> findOrbit(
    int vertex,
    const AutomorphismGroup& group
) {

    set<int> orbit;

    for (const auto& automorphism : group) {

        orbit.insert(automorphism[vertex]);
    }

    return orbit;
}

// Find the stabilizer of a vertex
AutomorphismGroup findStabilizer(
    int vertex,
    const AutomorphismGroup& group
) {

    AutomorphismGroup stabilizer;

    for (const auto& automorphism : group) {

        if (automorphism[vertex] == vertex) {

            stabilizer.push_back(automorphism);
        }
    }

    return stabilizer;
}

// Display an automorphism
void displayPermutation(
    const Permutation& permutation
) {

    cout << "[ ";

    for (int value : permutation) {

        cout << value << " ";
    }

    cout << "]";
}

// Display all automorphisms
void displayAutomorphismGroup(
    const AutomorphismGroup& group,
    const string& name
) {

    cout << "\n========== " << name
         << " AUTOMORPHISM GROUP ==========\n";

    cout << "Total automorphisms: "
         << group.size() << endl;

    for (int i = 0; i < group.size(); i++) {

        cout << "Automorphism " << i + 1 << ": ";

        displayPermutation(group[i]);

        cout << endl;
    }
}

// Display the orbit
void displayOrbit(
    int vertex,
    const set<int>& orbit
) {

    cout << "\nOrbit of vertex " << vertex << ": { ";

    for (int value : orbit) {

        cout << value << " ";
    }

    cout << "}" << endl;
}

// Display the stabilizer
void displayStabilizer(
    int vertex,
    const AutomorphismGroup& stabilizer
) {

    cout << "\nStabilizer of vertex "
         << vertex << ":\n";

    cout << "Total stabilizing automorphisms: "
         << stabilizer.size() << endl;

    for (int i = 0; i < stabilizer.size(); i++) {

        cout << "Stabilizer " << i + 1 << ": ";

        displayPermutation(stabilizer[i]);

        cout << endl;
    }
}

// Verify Orbit-Stabilizer theorem
bool verifyOrbitStabilizer(
    const AutomorphismGroup& group,
    const set<int>& orbit,
    const AutomorphismGroup& stabilizer
) {

    unsigned long long groupSize = group.size();

    unsigned long long orbitSize = orbit.size();

    unsigned long long stabilizerSize =
        stabilizer.size();

    cout << "\n========== ORBIT-STABILIZER THEOREM ==========\n";

    cout << "|Aut(G)| = " << groupSize << endl;

    cout << "|Orbit(v)| = " << orbitSize << endl;

    cout << "|Stab(v)| = " << stabilizerSize << endl;

    cout << "\nChecking:\n";

    cout << groupSize << " = "
         << orbitSize << " x "
         << stabilizerSize << endl;

    bool valid =
        groupSize == orbitSize * stabilizerSize;

    if (valid) {

        cout << "\nOrbit-Stabilizer Theorem VERIFIED.\n";
    }

    else {

        cout << "\nOrbit-Stabilizer Theorem FAILED.\n";
    }

    return valid;
}

// Calculate all vertex orbits
vector<set<int>> findAllOrbits(
    int n,
    const AutomorphismGroup& group
) {

    vector<set<int>> orbits;

    vector<bool> visited(n, false);

    for (int vertex = 0; vertex < n; vertex++) {

        if (visited[vertex]) {
            continue;
        }

        set<int> orbit = findOrbit(vertex, group);

        for (int member : orbit) {

            visited[member] = true;
        }

        orbits.push_back(orbit);
    }

    return orbits;
}

// Display all vertex orbits
void displayAllOrbits(
    const vector<set<int>>& orbits
) {

    cout << "\n========== VERTEX ORBITS ==========\n";

    for (int i = 0; i < orbits.size(); i++) {

        cout << "Orbit " << i + 1 << ": { ";

        for (int vertex : orbits[i]) {

            cout << vertex << " ";
        }

        cout << "}" << endl;
    }
}

// Find an exact isomorphism between two graphs
bool findIsomorphism(
    const Graph& graphA,
    const Graph& graphB,
    Permutation& mapping
) {

    int n = graphA.size();

    vector<int> degreeA = calculateDegrees(graphA);

    vector<int> degreeB = calculateDegrees(graphB);

    vector<int> order(n);

    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(),
        [&](int a, int b) {

            return degreeA[a] > degreeA[b];
        }
    );

    mapping.assign(n, -1);

    vector<bool> used(n, false);

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

            bool compatible = true;

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

            mapping[u] = -1;

            used[v] = false;
        }

        return false;
    };

    return search(0);
}

// Display graph isomorphism mapping
void displayMapping(const Permutation& mapping) {

    cout << "\n========== ISOMORPHISM MAPPING ==========\n";

    for (int i = 0; i < mapping.size(); i++) {

        cout << "Graph A Vertex " << i
             << " -> Graph B Vertex "
             << mapping[i] << endl;
    }
}

// Analyze automorphism group of one graph
void analyzeGraph(
    const Graph& graph,
    const string& name
) {

    int n = graph.size();

    cout << "\n\n########################################\n";

    cout << "ANALYSIS OF " << name << endl;

    cout << "########################################\n";

    // Find automorphism group
    AutomorphismGroup group =
        findAutomorphisms(graph);

    displayAutomorphismGroup(group, name);

    // Find all vertex orbits
    vector<set<int>> orbits =
        findAllOrbits(n, group);

    displayAllOrbits(orbits);

    // Analyze every vertex
    cout << "\n========== VERTEX STABILIZER ANALYSIS ==========\n";

    for (int vertex = 0; vertex < n; vertex++) {

        set<int> orbit = findOrbit(vertex, group);

        AutomorphismGroup stabilizer =
            findStabilizer(vertex, group);

        cout << "\n--------------------------------\n";

        cout << "Vertex: " << vertex << endl;

        cout << "Orbit size: " << orbit.size() << endl;

        cout << "Stabilizer size: "
             << stabilizer.size() << endl;

        bool valid = verifyOrbitStabilizer(
            group,
            orbit,
            stabilizer
        );

        if (!valid) {

            cout << "Unexpected group calculation error.\n";
        }
    }
}

// Main function
int main() {

    cout << "===== GRAPH AUTOMORPHISM GROUP AND ORBIT-STABILIZER =====\n";

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

    // Analyze Graph A
    analyzeGraph(graphA, "GRAPH A");

    // Analyze Graph B
    analyzeGraph(graphB, "GRAPH B");

    // Check graph isomorphism
    cout << "\n\n========== GRAPH ISOMORPHISM CHECK ==========\n";

    Permutation mapping;

    if (findIsomorphism(graphA, graphB, mapping)) {

        cout << "\nThe graphs ARE isomorphic.\n";

        displayMapping(mapping);
    }

    else {

        cout << "\nThe graphs are NOT isomorphic.\n";
    }

    return 0;
}
