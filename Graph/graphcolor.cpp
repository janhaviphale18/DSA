#include <iostream>
#include <vector>
using namespace std;

class GraphColoring {
private:
    int vertices;
    int maxColors;

    vector<vector<int>> adjMatrix;
    vector<int> color;

    // Check whether a color can safely be assigned.
    bool isSafe(int vertex, int selectedColor) {
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[vertex][i] == 1 &&
                color[i] == selectedColor) {
                return false;
            }
        }

        return true;
    }

    // Backtracking function to color all vertices.
    bool solve(int vertex) {

        // Every vertex has been assigned a color.
        if (vertex == vertices) {
            return true;
        }

        // Try every available color.
        for (int selectedColor = 1;
             selectedColor <= maxColors;
             selectedColor++) {

            if (isSafe(vertex, selectedColor)) {

                // Assign the selected color.
                color[vertex] = selectedColor;

                // Recursively color the next vertex.
                if (solve(vertex + 1)) {
                    return true;
                }

                // Backtrack if the choice fails.
                color[vertex] = 0;
            }
        }

        return false;
    }

public:
    GraphColoring(int v, int m) {
        vertices = v;
        maxColors = m;

        adjMatrix.assign(
            vertices,
            vector<int>(vertices, 0)
        );

        color.assign(vertices, 0);
    }

    // Add an undirected edge.
    bool addEdge(int u, int v) {
        if (u < 0 || u >= vertices ||
            v < 0 || v >= vertices) {
            return false;
        }

        if (u == v) {
            return false;
        }

        if (adjMatrix[u][v] == 1) {
            return false;
        }

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        return true;
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

    // Start the graph coloring algorithm.
    bool colorGraph() {
        return solve(0);
    }

    // Display the assigned colors.
    void displayColoring() {
        cout << "\nGraph Coloring Result:\n";

        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i
                 << " -> Color " << color[i] << "\n";
        }

        cout << "\nColor Assignment:\n";

        for (int i = 0; i < vertices; i++) {
            cout << color[i] << " ";

        }

        cout << "\n";
    }

    // Display vertices grouped by color.
    void displayColorGroups() {
        cout << "\nVertices Grouped by Color:\n";

        for (int c = 1; c <= maxColors; c++) {
            cout << "Color " << c << ": ";

            bool found = false;

            for (int i = 0; i < vertices; i++) {
                if (color[i] == c) {
                    cout << i << " ";
                    found = true;
                }
            }

            if (!found) {
                cout << "No vertices";
            }

            cout << "\n";
        }
    }

    // Verify that the final coloring is valid.
    bool verifyColoring() {
        for (int u = 0; u < vertices; u++) {

            if (color[u] < 1 || color[u] > maxColors) {
                return false;
            }

            for (int v = u + 1; v < vertices; v++) {
                if (adjMatrix[u][v] == 1 &&
                    color[u] == color[v]) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    int V, E, M;

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

    long long maxEdges = 1LL * V * (V - 1) / 2;

    if (E > maxEdges) {
        cout << "Too many edges for a simple undirected graph.\n";
        return 0;
    }

    cout << "Enter number of available colors: ";
    cin >> M;

    if (M <= 0) {
        cout << "Number of colors must be positive.\n";
        return 0;
    }

    GraphColoring graph(V, M);

    cout << "\nEnter undirected edges using vertices from 0 to "
         << V - 1 << ":\n";

    for (int i = 1; i <= E; i++) {
        int u, v;

        cout << "Edge " << i << ": ";
        cin >> u >> v;

        if (!graph.addEdge(u, v)) {
            cout << "Invalid or duplicate edge.\n";
            return 0;
        }
    }

    graph.displayGraph();

    cout << "\nChecking whether the graph can be colored "
         << "using " << M << " colors...\n";

    if (graph.colorGraph()) {
        cout << "\nValid graph coloring exists.\n";

        graph.displayColoring();

        graph.displayColorGroups();

        if (graph.verifyColoring()) {
            cout << "\nColoring verification successful.\n";
        }
        else {
            cout << "\nColoring verification failed.\n";
        }
    }
    else {
        cout << "\nNo valid coloring exists using "
             << M << " colors.\n";
    }

    return 0;
}
