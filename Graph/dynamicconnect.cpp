#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct Edge {
    int u, v;
};

struct Operation {
    char type;
    int id, u, v;
};

struct EdgeInfo {
    int u, v;
    int startTime;
};

struct Change {
    int child;
    int parentRoot;
    int oldSize;
};

class RollbackDSU {
private:
    vector<int> parent;
    vector<int> componentSize;
    vector<Change> history;

public:
    RollbackDSU(int vertices) {
        parent.resize(vertices);
        componentSize.assign(vertices, 1);

        for (int i = 0; i < vertices; i++) {
            parent[i] = i;
        }
    }

    // Find representative without path compression.
    int find(int vertex) {
        while (parent[vertex] != vertex) {
            vertex = parent[vertex];
        }

        return vertex;
    }

    // Merge two components using union by size.
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return;
        }

        if (componentSize[rootU] < componentSize[rootV]) {
            int temp = rootU;
            rootU = rootV;
            rootV = temp;
        }

        history.push_back({
            rootV,
            rootU,
            componentSize[rootU]
        });

        parent[rootV] = rootU;
        componentSize[rootU] += componentSize[rootV];
    }

    // Check connectivity.
    bool connected(int u, int v) {
        return find(u) == find(v);
    }

    // Save current history position.
    int snapshot() {
        return (int)history.size();
    }

    // Restore DSU to a previous history position.
    void rollback(int targetSize) {
        while ((int)history.size() > targetSize) {
            Change change = history.back();
            history.pop_back();

            parent[change.child] = change.child;

            componentSize[change.parentRoot] =
                change.oldSize;
        }
    }
};

class OfflineDynamicConnectivity {
private:
    int vertices;
    int operationsCount;

    vector<Operation> operations;
    vector<vector<Edge>> segmentTree;
    vector<string> answers;

    RollbackDSU dsu;

    // Insert an edge into the segment tree interval.
    void addInterval(
        int node,
        int left,
        int right,
        int queryLeft,
        int queryRight,
        Edge edge
    ) {
        if (queryLeft > right || queryRight < left) {
            return;
        }

        if (queryLeft <= left && right <= queryRight) {
            segmentTree[node].push_back(edge);
            return;
        }

        int mid = left + (right - left) / 2;

        addInterval(
            node * 2,
            left,
            mid,
            queryLeft,
            queryRight,
            edge
        );

        addInterval(
            node * 2 + 1,
            mid + 1,
            right,
            queryLeft,
            queryRight,
            edge
        );
    }

    // Process the segment tree using rollback DSU.
    void solve(
        int node,
        int left,
        int right
    ) {
        int savedState = dsu.snapshot();

        // Apply all edges active throughout this interval.
        for (const Edge& edge : segmentTree[node]) {
            dsu.unite(edge.u, edge.v);
        }

        if (left == right) {
            // A leaf represents one operation.
            if (operations[left].type == 'Q') {
                int u = operations[left].u;
                int v = operations[left].v;

                if (dsu.connected(u, v)) {
                    answers[left] = "YES";
                }
                else {
                    answers[left] = "NO";
                }
            }
        }
        else {
            int mid = left + (right - left) / 2;

            solve(node * 2, left, mid);
            solve(node * 2 + 1, mid + 1, right);
        }

        // Restore the DSU before leaving this segment.
        dsu.rollback(savedState);
    }

public:
    OfflineDynamicConnectivity(
        int v,
        int q
    ) : vertices(v),
        operationsCount(q),
        operations(q),
        segmentTree(4 * q + 5),
        answers(q, ""),
        dsu(v) {
    }

    // Read and validate all operations.
    bool readOperations() {
        map<int, EdgeInfo> activeEdges;
        map<int, bool> usedIDs;

        cout << "\nAvailable Operations:\n";
        cout << "A id u v - Add an edge\n";
        cout << "R id     - Remove an edge\n";
        cout << "Q u v    - Check connectivity\n\n";

        for (int i = 0; i < operationsCount; i++) {
            char type;

            cout << "Operation " << i + 1 << ": ";
            cin >> type;

            if (type == 'A' || type == 'a') {
                int id, u, v;
                cin >> id >> u >> v;

                if (id <= 0 ||
                    u < 0 || u >= vertices ||
                    v < 0 || v >= vertices ||
                    u == v) {
                    cout << "Invalid edge information.\n";
                    return false;
                }

                if (usedIDs[id]) {
                    cout << "Edge ID has already been used.\n";
                    return false;
                }

                usedIDs[id] = true;

                activeEdges[id] = {u, v, i};

                operations[i] = {'A', id, u, v};
            }
            else if (type == 'R' || type == 'r') {
                int id;
                cin >> id;

                if (activeEdges.find(id) == activeEdges.end()) {
                    cout << "Cannot remove an inactive edge.\n";
                    return false;
                }

                EdgeInfo info = activeEdges[id];

                // Edge is active from its addition time
                // until the operation immediately before removal.
                int start = info.startTime;
                int finish = i - 1;

                if (start <= finish && operationsCount > 0) {
                    addInterval(
                        1,
                        0,
                        operationsCount - 1,
                        start,
                        finish,
                        {info.u, info.v}
                    );
                }

                activeEdges.erase(id);

                operations[i] = {'R', id, -1, -1};
            }
            else if (type == 'Q' || type == 'q') {
                int u, v;
                cin >> u >> v;

                if (u < 0 || u >= vertices ||
                    v < 0 || v >= vertices) {
                    cout << "Invalid query vertices.\n";
                    return false;
                }

                operations[i] = {'Q', -1, u, v};
            }
            else {
                cout << "Invalid operation type.\n";
                return false;
            }
        }

        // Add intervals for edges that remain active.
        for (const auto& entry : activeEdges) {
            int start = entry.second.startTime;
            int finish = operationsCount - 1;

            if (start <= finish && operationsCount > 0) {
                addInterval(
                    1,
                    0,
                    operationsCount - 1,
                    start,
                    finish,
                    {
                        entry.second.u,
                        entry.second.v
                    }
                );
            }
        }

        return true;
    }

    // Execute all offline connectivity queries.
    void processQueries() {
        if (operationsCount == 0) {
            cout << "\nNo operations to process.\n";
            return;
        }

        solve(1, 0, operationsCount - 1);

        cout << "\nConnectivity Query Results:\n";

        int queryNumber = 0;

        for (int i = 0; i < operationsCount; i++) {
            if (operations[i].type == 'Q') {
                queryNumber++;

                cout << "Query " << queryNumber << ": "
                     << answers[i] << "\n";
            }
        }

        cout << "\nTotal queries answered: "
             << queryNumber << "\n";
    }
};

int main() {
    int V, Q;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter number of operations: ";
    cin >> Q;

    if (Q < 0) {
        cout << "Invalid number of operations.\n";
        return 0;
    }

    OfflineDynamicConnectivity graph(V, Q);

    if (!graph.readOperations()) {
        return 0;
    }

    graph.processQueries();

    return 0;
}
