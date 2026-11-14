
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

class ArticulationFinder {
private:
    int vertices;
    int timer;

    vector<vector<pair<int, int>>> adj;

    vector<int> disc;
    vector<int> low;
    vector<int> parent;

    vector<bool> isArticulation;

    // DFS traversal to identify articulation points.
    void dfs(int u, int parentEdge) {
        disc[u] = low[u] = timer++;

        int children = 0;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int edgeID = edge.second;

            // Skip only the exact edge used to enter this vertex.
            if (edgeID == parentEdge) {
                continue;
            }

            // Explore an unvisited adjacent vertex.
            if (disc[v] == -1) {
                parent[v] = u;
                children++;

                dfs(v, edgeID);

                // Update low-link value after DFS returns.
                low[u] = min(low[u], low[v]);

                // Articulation condition for non-root vertices.
                if (parent[u] != -1 &&
                    low[v] >= disc[u]) {
                    isArticulation[u] = true;
                }
            }
            else {
                // Update low-link value using a back edge.
                low[u] = min(low[u], disc[v]);
            }
        }

        // Special condition for a DFS root.
        if (parent[u] == -1 && children > 1) {
            isArticulation[u] = true;
        }
    }

public:
    ArticulationFinder(int v) {
        vertices = v;
        timer = 0;

        adj.resize(vertices);

        disc.assign(vertices, -1);
        low.assign(vertices, -1);
        parent.assign(vertices, -1);

        isArticulation.assign(vertices, false);
    }

    // Add an undirected edge with a unique ID.
    void addEdge(int u, int v, int edgeID) {
        adj[u].push_back({v, edgeID});
        adj[v].push_back({u, edgeID});
    }

    // Find articulation points in all components.
    void findArticulationPoints() {
        for (int i = 0; i < vertices; i++) {
            if (disc[i] == -1) {
                dfs(i, -1);
            }
        }
    }

    // Display discovery and low-link values.
    void displayValues() {
        cout << "\nVertex Information:\n";

        cout << "Vertex\tDiscovery\tLow-Link\tParent\n";

        for (int i = 0; i < vertices; i++) {
            cout << i << "\t"
                 << disc[i] << "\t\t"
                 << low[i] << "\t\t"
                 << parent[i] << "\n";
        }
    }

    // Display articulation points.
    void displayArticulationPoints() {
        cout << "\nArticulation Points:\n";

        int count = 0;

        for (int i = 0; i < vertices; i++) {
            if (isArticulation[i]) {
                cout << "Vertex " << i << "\n";
                count++;
            }
        }

        if (count == 0) {
            cout << "No articulation points found.\n";
        }

        cout << "Total articulation points: "
             << count << "\n";
    }

    // Display components after removing articulation points.
    void displayRemainingComponents() {
        vector<bool> visited(vertices, false);

        cout << "\nComponents After Removing Articulation Points:\n";

        int componentCount = 0;

        for (int start = 0; start < vertices; start++) {
            if (visited[start] || isArticulation[start]) {
                continue;
            }

            vector<int> component;
            vector<int> st;

            st.push_back(start);
            visited[start] = true;

            while (!st.empty()) {
                int u = st.back();
                st.pop_back();

                component.push_back(u);

                for (const auto& edge : adj[u]) {
                    int v = edge.first;

                    if (!visited[v] && !isArticulation[v]) {
                        visited[v] = true;
                        st.push_back(v);
                    }
                }
            }

            componentCount++;

            cout << "Component " << componentCount << ": ";

            for (int vertex : component) {
                cout << vertex << " ";
            }

            cout << "\n";
        }

        // Each removed articulation vertex is also an isolated
        // remaining vertex if considered without its incident edges.
        for (int i = 0; i < vertices; i++) {
            if (isArticulation[i]) {
                cout << "Removed articulation vertex: "
                     << i << "\n";
            }
        }

        cout << "Remaining connected components: "
             << componentCount << "\n";
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

    ArticulationFinder graph(V);

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

    graph.findArticulationPoints();

    graph.displayValues();

    graph.displayArticulationPoints();

    graph.displayRemainingComponents();

    return 0;
}
