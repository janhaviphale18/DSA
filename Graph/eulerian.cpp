#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class EulerianGraph {
private:
    int vertices;
    int edges;

    vector<vector<pair<int, int>>> adj;
    vector<int> degree;

    vector<bool> edgeUsed;

    // Check connectivity among vertices having nonzero degree.
    bool isConnected() {
        int start = -1;

        for (int i = 0; i < vertices; i++) {
            if (degree[i] > 0) {
                start = i;
                break;
            }
        }

        // A graph without edges is considered connected
        // for Eulerian trail purposes.
        if (start == -1) {
            return true;
        }

        vector<bool> visited(vertices, false);
        stack<int> st;

        st.push(start);
        visited[start] = true;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            for (const auto& edge : adj[u]) {
                int v = edge.first;

                if (!visited[v]) {
                    visited[v] = true;
                    st.push(v);
                }
            }
        }

        // Every non-isolated vertex must be visited.
        for (int i = 0; i < vertices; i++) {
            if (degree[i] > 0 && !visited[i]) {
                return false;
            }
        }

        return true;
    }

    // Construct Eulerian path or circuit using Hierholzer's algorithm.
    bool constructTrail(
        int start,
        vector<int>& vertexTrail,
        vector<int>& edgeTrail
    ) {
        vector<int> nextIndex(vertices, 0);

        // Stores current vertex and the edge used to enter it.
        stack<pair<int, int>> st;

        st.push({start, -1});

        while (!st.empty()) {
            int u = st.top().first;

            // Skip already used edges.
            while (nextIndex[u] < (int)adj[u].size() &&
                   edgeUsed[adj[u][nextIndex[u]].second]) {
                nextIndex[u]++;
            }

            // No unused edges remain at this vertex.
            if (nextIndex[u] == (int)adj[u].size()) {
                int incomingEdge = st.top().second;

                vertexTrail.push_back(u);

                if (incomingEdge != -1) {
                    edgeTrail.push_back(incomingEdge);
                }

                st.pop();
            }
            else {
                // Select the next unused edge.
                int v = adj[u][nextIndex[u]].first;
                int edgeID = adj[u][nextIndex[u]].second;

                nextIndex[u]++;

                if (!edgeUsed[edgeID]) {
                    edgeUsed[edgeID] = true;

                    st.push({v, edgeID});
                }
            }
        }

        // Reverse the constructed trail.
        reverse(vertexTrail.begin(), vertexTrail.end());
        reverse(edgeTrail.begin(), edgeTrail.end());

        // Every original edge must be used exactly once.
        return (int)edgeTrail.size() == edges;
    }

public:
    EulerianGraph(int v, int e) {
        vertices = v;
        edges = e;

        adj.resize(vertices);
        degree.assign(vertices, 0);

        edgeUsed.assign(edges + 1, false);
    }

    // Add an undirected edge with a unique ID.
    void addEdge(int u, int v, int edgeID) {
        adj[u].push_back({v, edgeID});
        adj[v].push_back({u, edgeID});

        degree[u]++;
        degree[v]++;
    }

    // Display vertex degrees.
    void displayDegrees() {
        cout << "\nVertex Degrees:\n";

        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i
                 << ": " << degree[i] << "\n";
        }
    }

    // Determine and construct the Eulerian trail.
    void findEulerianTrail() {
        cout << "\nEulerian Analysis:\n";

        if (!isConnected()) {
            cout << "The graph is disconnected among "
                 << "vertices having nonzero degree.\n";

            cout << "Neither an Eulerian path nor "
                 << "an Eulerian circuit exists.\n";

            return;
        }

        vector<int> oddVertices;

        for (int i = 0; i < vertices; i++) {
            if (degree[i] % 2 != 0) {
                oddVertices.push_back(i);
            }
        }

        int start = 0;

        if (edges == 0) {
            cout << "The graph has no edges.\n";
            cout << "An empty Eulerian circuit exists.\n";

            cout << "Vertex trail: 0\n";
            return;
        }

        if (oddVertices.size() == 0) {
            cout << "Eulerian Circuit exists.\n";

            // Start from any vertex with nonzero degree.
            for (int i = 0; i < vertices; i++) {
                if (degree[i] > 0) {
                    start = i;
                    break;
                }
            }
        }
        else if (oddVertices.size() == 2) {
            cout << "Eulerian Path exists.\n";
            cout << "Eulerian Circuit does not exist.\n";

            cout << "Starting vertex: "
                 << oddVertices[0] << "\n";

            cout << "Ending vertex: "
                 << oddVertices[1] << "\n";

            // Start from one of the odd-degree vertices.
            start = oddVertices[0];
        }
        else {
            cout << "Number of odd-degree vertices: "
                 << oddVertices.size() << "\n";

            cout << "Neither an Eulerian path nor "
                 << "an Eulerian circuit exists.\n";

            return;
        }

        vector<int> vertexTrail;
        vector<int> edgeTrail;

        bool success = constructTrail(
            start,
            vertexTrail,
            edgeTrail
        );

        if (!success) {
            cout << "Unable to construct a complete Eulerian trail.\n";
            return;
        }

        cout << "\nEulerian Vertex Trail:\n";

        for (int i = 0; i < (int)vertexTrail.size(); i++) {
            cout << vertexTrail[i];

            if (i != (int)vertexTrail.size() - 1) {
                cout << " -> ";
            }
        }

        cout << "\n\nEdges Traversed:\n";

        for (int i = 0; i < (int)edgeTrail.size(); i++) {
            cout << "Edge " << edgeTrail[i] << ": "
                 << vertexTrail[i] << " - "
                 << vertexTrail[i + 1] << "\n";
        }

        cout << "\nTotal edges traversed: "
             << edgeTrail.size() << "\n";
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

    EulerianGraph graph(V, E);

    cout << "\nEnter undirected edges using vertices from 0 to "
         << V - 1 << ":\n";

    for (int i = 1; i <= E; i++) {
        int u, v;

        cout << "Edge " << i << ": ";
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertex.\n";
            return 0;
        }

        graph.addEdge(u, v, i);
    }

    graph.displayDegrees();

    graph.findEulerianTrail();

    return 0;
}
