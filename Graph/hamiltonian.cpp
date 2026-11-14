#include <iostream>
#include <vector>
using namespace std;

class HamiltonianGraph {
private:
    int vertices;

    vector<vector<int>> adjMatrix;

    vector<bool> visited;

    vector<int> currentPath;
    vector<int> hamiltonianPath;
    vector<int> hamiltonianCircuit;

    bool pathFound;
    bool circuitFound;

    // Find a Hamiltonian path using backtracking.
    bool findPath(int current, int visitedCount) {
        // Every vertex has been visited.
        if (visitedCount == vertices) {
            hamiltonianPath = currentPath;
            return true;
        }

        // Explore every possible adjacent vertex.
        for (int next = 0; next < vertices; next++) {
            if (adjMatrix[current][next] == 1 &&
                !visited[next]) {

                visited[next] = true;
                currentPath.push_back(next);

                if (findPath(next, visitedCount + 1)) {
                    return true;
                }

                // Backtrack.
                currentPath.pop_back();
                visited[next] = false;
            }
        }

        return false;
    }

    // Find a Hamiltonian circuit using backtracking.
    bool findCircuit(int current, int visitedCount) {
        // Check whether all vertices have been visited.
        if (visitedCount == vertices) {

            // The last vertex must connect to the starting vertex.
            if (adjMatrix[current][0] == 1) {
                hamiltonianCircuit = currentPath;

                // Complete the circuit by returning to vertex 0.
                hamiltonianCircuit.push_back(0);

                return true;
            }

            return false;
        }

        // Explore all possible unvisited adjacent vertices.
        for (int next = 0; next < vertices; next++) {
            if (adjMatrix[current][next] == 1 &&
                !visited[next]) {

                visited[next] = true;
                currentPath.push_back(next);

                if (findCircuit(next, visitedCount + 1)) {
                    return true;
                }

                // Backtrack.
                currentPath.pop_back();
                visited[next] = false;
            }
        }

        return false;
    }

public:
    HamiltonianGraph(int v) {
        vertices = v;

        adjMatrix.assign(
            vertices,
            vector<int>(vertices, 0)
        );

        visited.assign(vertices, false);

        pathFound = false;
        circuitFound = false;
    }

    // Add an undirected edge.
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    // Display the adjacency matrix.
    void displayGraph() {
        cout << "\nAdjacency Matrix:\n";

        cout << "  ";

        for (int i = 0; i < vertices; i++) {
            cout << i << " ";
        }

        cout << "\n";

        for (int i = 0; i < vertices; i++) {
            cout << i << " ";

            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }

            cout << "\n";
        }
    }

    // Find a Hamiltonian path.
    void findHamiltonianPath() {
        pathFound = false;

        // Try every vertex as the starting vertex.
        for (int start = 0; start < vertices; start++) {

            fill(visited.begin(), visited.end(), false);
            currentPath.clear();

            visited[start] = true;
            currentPath.push_back(start);

            if (findPath(start, 1)) {
                pathFound = true;
                break;
            }
        }
    }

    // Find a Hamiltonian circuit.
    void findHamiltonianCircuit() {
        circuitFound = false;

        // A simple undirected graph needs at least 3 vertices
        // to contain a Hamiltonian circuit.
        if (vertices < 3) {
            return;
        }

        fill(visited.begin(), visited.end(), false);
        currentPath.clear();

        // Fix vertex 0 as the starting vertex.
        visited[0] = true;
        currentPath.push_back(0);

        if (findCircuit(0, 1)) {
            circuitFound = true;
        }
    }

    // Display Hamiltonian path.
    void displayHamiltonianPath() {
        cout << "\nHamiltonian Path:\n";

        if (!pathFound) {
            cout << "No Hamiltonian path exists.\n";
            return;
        }

        for (int i = 0; i < (int)hamiltonianPath.size(); i++) {
            cout << hamiltonianPath[i];

            if (i != (int)hamiltonianPath.size() - 1) {
                cout << " -> ";
            }
        }

        cout << "\nTotal vertices visited: "
             << hamiltonianPath.size() << "\n";
    }

    // Display Hamiltonian circuit.
    void displayHamiltonianCircuit() {
        cout << "\nHamiltonian Circuit:\n";

        if (!circuitFound) {
            cout << "No Hamiltonian circuit exists.\n";
            return;
        }

        for (int i = 0; i < (int)hamiltonianCircuit.size(); i++) {
            cout << hamiltonianCircuit[i];

            if (i != (int)hamiltonianCircuit.size() - 1) {
                cout << " -> ";
            }
        }

        cout << "\nTotal distinct vertices visited: "
             << vertices << "\n";
    }

    // Display the final analysis.
    void analyzeGraph() {
        findHamiltonianPath();
        findHamiltonianCircuit();

        displayHamiltonianPath();
        displayHamiltonianCircuit();
    }
};

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0) {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    // A simple undirected graph can have at most
    // V * (V - 1) / 2 distinct edges.
    long long maxEdges = 1LL * V * (V - 1) / 2;

    if (E > maxEdges) {
        cout << "Too many edges for a simple undirected graph.\n";
        return 0;
    }

    HamiltonianGraph graph(V);

    cout << "\nEnter undirected edges using vertices from 0 to "
         << V - 1 << ":\n";

    for (int i = 1; i <= E; i++) {
        int u, v;

        cout << "Edge " << i << ": ";
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V || u == v) {
            cout << "Invalid edge. Self-loops are not allowed.\n";
            return 0;
        }

        graph.addEdge(u, v);
    }

    graph.displayGraph();

    graph.analyzeGraph();

    return 0;
}
