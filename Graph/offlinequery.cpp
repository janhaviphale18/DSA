#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Edge {
    int u, v;
};

struct Operation {
    char type;
    int first, second;
};

struct Answer {
    int queryNumber;
    bool connected;
};

class DSU {
private:
    vector<int> parent;
    vector<int> size;

public:
    DSU(int vertices) {
        parent.resize(vertices);
        size.assign(vertices, 1);

        for (int i = 0; i < vertices; i++) {
            parent[i] = i;
        }
    }

    int find(int vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex]);
        }

        return parent[vertex];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return false;
        }

        if (size[rootU] < size[rootV]) {
            swap(rootU, rootV);
        }

        parent[rootV] = rootU;
        size[rootU] += size[rootV];

        return true;
    }

    bool connected(int u, int v) {
        return find(u) == find(v);
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

    vector<Edge> edges(E + 1);
    vector<bool> deleted(E + 1, false);

    cout << "\nEnter edges using vertices from 0 to "
         << V - 1 << ":\n";

    for (int i = 1; i <= E; i++) {
        int u, v;

        cout << "Edge " << i << ": ";
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V || u == v) {
            cout << "Invalid edge. Self-loops are not allowed.\n";
            return 0;
        }

        for (int j = 1; j < i; j++) {
            if ((edges[j].u == u && edges[j].v == v) ||
                (edges[j].u == v && edges[j].v == u)) {
                cout << "Duplicate edge is not allowed.\n";
                return 0;
            }
        }

        edges[i] = {u, v};
    }

    int Q;

    cout << "\nEnter number of operations: ";
    cin >> Q;

    if (Q < 0) {
        cout << "Invalid number of operations.\n";
        return 0;
    }

    vector<Operation> operations(Q);
    int queryCount = 0;

    cout << "\nOperations:\n";
    cout << "D edgeID  -> Delete an edge\n";
    cout << "Q u v     -> Check connectivity\n";

    for (int i = 0; i < Q; i++) {
        char type;

        cout << "Operation " << i + 1 << ": ";
        cin >> type;

        if (type == 'D' || type == 'd') {
            int id;
            cin >> id;

            if (id < 1 || id > E) {
                cout << "Invalid edge ID.\n";
                return 0;
            }

            if (deleted[id]) {
                cout << "This edge has already been scheduled for deletion.\n";
                return 0;
            }

            deleted[id] = true;
            operations[i] = {'D', id, -1};
        }
        else if (type == 'Q' || type == 'q') {
            int u, v;
            cin >> u >> v;

            if (u < 0 || u >= V || v < 0 || v >= V) {
                cout << "Invalid query vertices.\n";
                return 0;
            }

            operations[i] = {'Q', u, v};
            queryCount++;
        }
        else {
            cout << "Invalid operation type.\n";
            return 0;
        }
    }

    DSU dsu(V);

    // Build the final graph using edges that were never deleted.
    for (int i = 1; i <= E; i++) {
        if (!deleted[i]) {
            dsu.unite(edges[i].u, edges[i].v);
        }
    }

    vector<Answer> answers;

    // Process all operations in reverse order.
    for (int i = Q - 1; i >= 0; i--) {

        if (operations[i].type == 'Q') {
            int u = operations[i].first;
            int v = operations[i].second;

            bool result = dsu.connected(u, v);

            answers.push_back({0, result});
        }
        else if (operations[i].type == 'D') {
            int id = operations[i].first;

            // Restore the deleted edge.
            dsu.unite(edges[id].u, edges[id].v);
        }
    }

    // Restore the original chronological order.
    reverse(answers.begin(), answers.end());

    cout << "\nConnectivity Query Results:\n";

    for (int i = 0; i < (int)answers.size(); i++) {
        cout << "Query " << i + 1 << ": ";

        if (answers[i].connected) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

    cout << "\nTotal queries answered: " << queryCount << "\n";

    return 0;
}
