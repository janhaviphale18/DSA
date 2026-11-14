#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Change {
    int child;
    int parentRoot;
    int oldSize;
    bool merged;
};

struct Snapshot {
    int id;
    int historySize;
};

class RollbackDSU {
private:
    vector<int> parent;
    vector<int> componentSize;
    vector<Change> history;
    vector<Snapshot> snapshots;

    int nextSnapshotID;

public:
    RollbackDSU(int vertices) {
        parent.resize(vertices);
        componentSize.assign(vertices, 1);

        for (int i = 0; i < vertices; i++) {
            parent[i] = i;
        }

        nextSnapshotID = 1;
    }

    // Find representative without path compression.
    int find(int vertex) {
        while (parent[vertex] != vertex) {
            vertex = parent[vertex];
        }

        return vertex;
    }

    // Merge two components and record the operation.
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        // No merge is required.
        if (rootU == rootV) {
            history.push_back({-1, -1, -1, false});
            return false;
        }

        // Attach smaller component to larger component.
        if (componentSize[rootU] < componentSize[rootV]) {
            swap(rootU, rootV);
        }

        // Record the change before modifying DSU.
        history.push_back({
            rootV,
            rootU,
            componentSize[rootU],
            true
        });

        parent[rootV] = rootU;
        componentSize[rootU] += componentSize[rootV];

        return true;
    }

    // Check whether two vertices are connected.
    bool connected(int u, int v) {
        return find(u) == find(v);
    }

    // Create a snapshot of the current DSU state.
    int createSnapshot() {
        int id = nextSnapshotID++;

        snapshots.push_back({
            id,
            (int)history.size()
        });

        return id;
    }

    // Roll back to a previously created snapshot.
    bool rollback(int snapshotID) {
        int index = -1;

        for (int i = 0; i < (int)snapshots.size(); i++) {
            if (snapshots[i].id == snapshotID) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            return false;
        }

        int targetSize = snapshots[index].historySize;

        if (targetSize > (int)history.size()) {
            return false;
        }

        // Undo changes until the target history size is reached.
        while ((int)history.size() > targetSize) {
            Change change = history.back();
            history.pop_back();

            if (change.merged) {
                parent[change.child] = change.child;

                componentSize[change.parentRoot] =
                    change.oldSize;
            }
        }

        // Invalidate snapshots created after the selected snapshot.
        snapshots.erase(
            snapshots.begin() + index + 1,
            snapshots.end()
        );

        return true;
    }

    // Display the current component information.
    void displayComponents(int vertices) {
        cout << "\nCurrent DSU Components:\n";

        vector<bool> printed(vertices, false);

        for (int i = 0; i < vertices; i++) {
            int root = find(i);

            if (!printed[root]) {
                printed[root] = true;

                cout << "Component: ";

                for (int j = 0; j < vertices; j++) {
                    if (find(j) == root) {
                        cout << j << " ";
                    }
                }

                cout << "| Size: "
                     << componentSize[root] << "\n";
            }
        }

        cout << "\nParent Array: ";

        for (int i = 0; i < vertices; i++) {
            cout << parent[i] << " ";
        }

        cout << "\n";
    }
};

int main() {
    int V;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    RollbackDSU dsu(V);

    int Q;

    cout << "Enter number of operations: ";
    cin >> Q;

    if (Q < 0) {
        cout << "Invalid number of operations.\n";
        return 0;
    }

    cout << "\nAvailable Operations:\n";
    cout << "U u v       - Union two vertices\n";
    cout << "Q u v       - Check connectivity\n";
    cout << "S           - Create a snapshot\n";
    cout << "R snapshotID - Rollback to a snapshot\n";
    cout << "\n";

    for (int i = 0; i < Q; i++) {
        char type;

        cout << "Operation " << i + 1 << ": ";
        cin >> type;

        if (type == 'U' || type == 'u') {
            int u, v;
            cin >> u >> v;

            if (u < 0 || u >= V || v < 0 || v >= V) {
                cout << "Invalid vertices.\n";
                return 0;
            }

            if (dsu.unite(u, v)) {
                cout << "Components merged successfully.\n";
            }
            else {
                cout << "Vertices are already connected.\n";
            }
        }
        else if (type == 'Q' || type == 'q') {
            int u, v;
            cin >> u >> v;

            if (u < 0 || u >= V || v < 0 || v >= V) {
                cout << "Invalid vertices.\n";
                return 0;
            }

            if (dsu.connected(u, v)) {
                cout << "YES: Vertices are connected.\n";
            }
            else {
                cout << "NO: Vertices are not connected.\n";
            }
        }
        else if (type == 'S' || type == 's') {
            int id = dsu.createSnapshot();

            cout << "Snapshot created successfully.\n";
            cout << "Snapshot ID: " << id << "\n";
        }
        else if (type == 'R' || type == 'r') {
            int id;
            cin >> id;

            if (dsu.rollback(id)) {
                cout << "Rollback successful.\n";
                cout << "Restored snapshot: " << id << "\n";
            }
            else {
                cout << "Invalid or unavailable snapshot ID.\n";
            }
        }
        else {
            cout << "Invalid operation type.\n";
            return 0;
        }
    }

    dsu.displayComponents(V);

    return 0;
}
