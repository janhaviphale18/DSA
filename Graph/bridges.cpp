#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

class BridgeFinder {
private:
    int vertices;
    int timer;

    vector<vector<pair<int, int>>> adj;

    vector<int> disc;
    vector<int> low;
    vector<int> parent;

    vector<pair<int, int>> bridges;

    // DFS traversal using discovery and low-link values.
    void dfs(int u, int parentEdge) {
        disc[u] = low[u] = timer++;
        
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int edgeID = edge.second;

            // Skip only the exact edge used to enter this vertex.
            if (edgeID == parentEdge) {
                continue;
            }

            // If v is unvisited, explore the DFS tree edge.
            if (disc[v] == -1) {
                parent[v] = u;

                dfs(v, edgeID);

                // Update low-link value after returning from DFS.
                low[u] = min(low[u], low[v]);

                // Check whether the edge is a bridge.
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
            else {
                // Update using an already visited adjacent vertex.
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    BridgeFinder(int v) {
        vertices = v;
        timer = 0;

        adj.resize(vertices);

        disc.assign(vertices, -1);
        low.assign(vertices, -1);
        parent.assign(vertices, -1);
    }

    // Add an undirected edge with a unique ID.
    void addEdge(int u, int v, int edgeID) {
        adj[u].push_back({v, edgeID});
        adj[v].push_back({u, edgeID});
    }

    // Find bridges in all connected components.
    void findBridges() {
        for (int i = 0; i < vertices; i++) {
            if (disc[i] == -1) {
                dfs(i, -1);
            }
        }

        // Sort bridges for consistent output.
        sort(bridges.begin(), bridges.end());
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

    // Display all identified bridges.
    void displayBridges() {
        cout << "\nBridges in the Graph:\n";

        if (bridges.empty()) {
            cout << "No bridges found.\n";
        }
        else {
            for (int i = 0; i < (int)bridges.size(); i++) {
                cout << "Bridge " << i + 1 << ": "
                     << bridges[i].first << " - "
                     << bridges[i].second << "\n";
            }
        }

        cout << "\nTotal number of bridges: "
             << bridges.size() << "\n";
    }

    // Display the connected components after removing bridges.
    void displayBridgeFreeComponents() {
        vector<vector<int>> components;
        vector<bool> visited(vertices, false);

        vector<vector<int>> graphWithoutBridges(vertices);

        // Construct a graph without bridge edges.
        for (int u = 0; u < vertices; u++) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;

                bool isBridge = false;

                for (const auto& bridge : bridges) {
                    if ((bridge.first == u && bridge.second == v) ||
                        (bridge.first == v && bridge.second == u)) {
                        isBridge = true;
                        break;
                    }
                }

                if (!isBridge) {
                    graphWithoutBridges[u].push_back(v);
                }
            }
        }

        // Find components in the remaining graph.
        for (int i = 0; i < vertices; i++) {
            if (visited[i]) {
                continue;
            }

            vector<int> component;
            vector<int> st;

            st.push_back(i);
            visited[i] = true;

            while (!st.empty()) {
                int u = st.back();
                st.pop_back();

                component.push_back(u);

                for (int v : graphWithoutBridges[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        st.push_back(v);
                    }
                }
            }

            components.push_back(component);
        }

        cout << "\nComponents After Removing Bridges:\n";

        for (int i = 0; i < (int)components.size(); i++) {
            cout << "Component " << i + 1 << ": ";

            for (int vertex : components[i]) {
                cout << vertex << " ";
            }

            cout << "\n";
        }

        cout << "Total components after removing bridges: "
             << components.size() << "\n";
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

    BridgeFinder graph(V);

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

    graph.findBridges();

    graph.displayValues();

    graph.displayBridges();

    graph.displayBridgeFreeComponents();

    return 0;
}
