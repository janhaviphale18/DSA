#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>
using namespace std;

class BiconnectedGraph {
private:
    int vertices;
    int timer;

    vector<vector<pair<int, int>>> adj;

    vector<int> disc;
    vector<int> low;
    vector<int> parent;

    vector<bool> isArticulation;

    stack<pair<int, int>> edgeStack;

    vector<vector<pair<int, int>>> components;

    // Extract one biconnected component from the edge stack.
    void extractComponent(int u, int v) {
        vector<pair<int, int>> component;

        while (!edgeStack.empty()) {
            pair<int, int> edge = edgeStack.top();
            edgeStack.pop();

            component.push_back(edge);

            if (edge.first == u && edge.second == v) {
                break;
            }
        }

        if (!component.empty()) {
            components.push_back(component);
        }
    }

    // DFS using discovery and low-link values.
    void dfs(int u, int parentEdge) {
        disc[u] = low[u] = timer++;

        int children = 0;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int edgeID = edge.second;

            // Skip only the exact parent edge.
            if (edgeID == parentEdge) {
                continue;
            }

            // Process an unvisited adjacent vertex.
            if (disc[v] == -1) {
                children++;

                parent[v] = u;

                // Store DFS tree edge.
                edgeStack.push({u, v});

                dfs(v, edgeID);

                // Update low-link value.
                low[u] = min(low[u], low[v]);

                // A complete BCC is identified.
                if (low[v] >= disc[u]) {

                    // Non-root articulation point condition.
                    if (parent[u] != -1) {
                        isArticulation[u] = true;
                    }

                    extractComponent(u, v);
                }
            }
            else if (disc[v] < disc[u]) {

                // Process a back edge only once.
                edgeStack.push({u, v});

                low[u] = min(low[u], disc[v]);
            }
        }

        // Special articulation condition for DFS root.
        if (parent[u] == -1 && children > 1) {
            isArticulation[u] = true;
        }
    }

public:
    BiconnectedGraph(int v) {
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

    // Find BCCs in all connected components.
    void findBiconnectedComponents() {
        for (int i = 0; i < vertices; i++) {

            if (disc[i] == -1) {
                dfs(i, -1);

                // Process any remaining edges.
                if (!edgeStack.empty()) {
                    vector<pair<int, int>> component;

                    while (!edgeStack.empty()) {
                        component.push_back(edgeStack.top());
                        edgeStack.pop();
                    }

                    components.push_back(component);
                }
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

    // Display all biconnected components.
    void displayComponents() {
        cout << "\nBiconnected Components:\n";

        if (components.empty()) {
            cout << "No biconnected components found.\n";
            return;
        }

        for (int i = 0; i < (int)components.size(); i++) {
            cout << "\nComponent " << i + 1 << ":\n";

            vector<int> componentVertices;

            for (const auto& edge : components[i]) {
                cout << edge.first << " - " << edge.second << "\n";

                componentVertices.push_back(edge.first);
                componentVertices.push_back(edge.second);
            }

            sort(
                componentVertices.begin(),
                componentVertices.end()
            );

            componentVertices.erase(
                unique(
                    componentVertices.begin(),
                    componentVertices.end()
                ),
                componentVertices.end()
            );

            cout << "Vertices: ";

            for (int vertex : componentVertices) {
                cout << vertex << " ";
            }

            cout << "\nNumber of edges: "
                 << components[i].size() << "\n";
        }

        cout << "\nTotal biconnected components: "
             << components.size() << "\n";
    }

    // Display articulation points.
    void displayArticulationPoints() {
        cout << "\nArticulation Points:\n";

        int count = 0;

        for (int i = 0; i < vertices; i++) {
            if (isArticulation[i]) {
                cout << i << " ";
                count++;
            }
        }

        if (count == 0) {
            cout << "None";
        }

        cout << "\nTotal articulation points: "
             << count << "\n";
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

    BiconnectedGraph graph(V);

    cout << "\nEnter undirected edges using vertices from 0 to "
         << V - 1 << ":\n";

    for (int i = 1; i <= E; i++) {
        int u, v;

        cout << "Edge " << i << ": ";
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V || u == v) {
            cout << "Invalid edge.\n";
            return 0;
        }

        graph.addEdge(u, v, i);
    }

    graph.findBiconnectedComponents();

    graph.displayValues();

    graph.displayComponents();

    graph.displayArticulationPoints();

    return 0;
}
