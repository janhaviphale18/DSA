#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    // Stores the partition ID of every vertex.
    vector<int> partition;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
        partition.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void displayGraph() {

        cout << "\n========== ADJACENCY LIST ==========\n";

        for (int i = 0; i < V; i++) {

            cout << i << " -> ";

            for (int neighbour : adj[i]) {
                cout << neighbour << " ";
            }

            cout << "\n";
        }
    }

    void initializePartition() {

        cout << "\n========== INITIAL PARTITION ==========\n";

        map<int, int> degreeMap;

        // Vertices with the same degree receive the same group.
        for (int i = 0; i < V; i++) {
            degreeMap[adj[i].size()] = 0;
        }

        int groupID = 0;

        for (auto& entry : degreeMap) {
            entry.second = groupID++;
        }

        for (int i = 0; i < V; i++) {
            partition[i] = degreeMap[adj[i].size()];
        }

        displayPartition();
    }

    int countGroups(const vector<int>& groups) {

        set<int> uniqueGroups(
            groups.begin(),
            groups.end()
        );

        return uniqueGroups.size();
    }

    void displayPartition() {

        map<int, vector<int>> groups;

        for (int i = 0; i < V; i++) {
            groups[partition[i]].push_back(i);
        }

        for (const auto& group : groups) {

            cout << "Group " << group.first << ": { ";

            for (int vertex : group.second) {
                cout << vertex << " ";
            }

            cout << "}\n";
        }
    }

    // Returns the number of neighbours of vertex v
    // in a particular partition group.
    int countNeighboursInGroup(
        int vertex,
        int groupID,
        const vector<int>& groups
    ) {

        int count = 0;

        for (int neighbour : adj[vertex]) {

            if (groups[neighbour] == groupID) {
                count++;
            }
        }

        return count;
    }

    void refinePartition() {

        cout << "\n========== EQUITABLE PARTITION REFINEMENT ==========\n";

        int iteration = 1;

        while (iteration <= V) {

            map<vector<int>, int> signatureMap;

            vector<vector<int>> signatures(V);

            // Construct a signature for each vertex.
            for (int vertex = 0; vertex < V; vertex++) {

                vector<int> signature;

                // Preserve the current group.
                signature.push_back(partition[vertex]);

                int totalGroups = countGroups(partition);

                // Count neighbours in every current group.
                for (int group = 0; group < totalGroups; group++) {

                    int count = countNeighboursInGroup(
                        vertex,
                        group,
                        partition
                    );

                    signature.push_back(count);
                }

                signatures[vertex] = signature;

                signatureMap[signature] = 0;
            }

            // Assign a unique group ID to every unique signature.
            int newGroupID = 0;

            for (auto& entry : signatureMap) {
                entry.second = newGroupID++;
            }

            vector<int> newPartition(V);

            for (int vertex = 0; vertex < V; vertex++) {

                newPartition[vertex] =
                    signatureMap[signatures[vertex]];
            }

            int oldGroups = countGroups(partition);
            int newGroups = countGroups(newPartition);

            partition = newPartition;

            cout << "\nIteration " << iteration << ":\n";

            displayPartition();

            cout << "Number of groups: "
                 << newGroups << "\n";

            if (oldGroups == newGroups) {

                cout << "\nEquitable partition reached.\n";
                break;
            }

            iteration++;
        }
    }

    void displayNeighbourCounts() {

        cout << "\n========== NEIGHBOUR COUNTS ==========\n";

        int totalGroups = countGroups(partition);

        cout << "Vertex\tGroup";

        for (int group = 0; group < totalGroups; group++) {
            cout << "\tG" << group;
        }

        cout << "\n";

        for (int vertex = 0; vertex < V; vertex++) {

            cout << vertex << "\t"
                 << partition[vertex];

            for (int group = 0; group < totalGroups; group++) {

                cout << "\t"
                     << countNeighboursInGroup(
                         vertex,
                         group,
                         partition
                     );
            }

            cout << "\n";
        }
    }

    void constructQuotientGraph() {

        cout << "\n========== QUOTIENT GRAPH ==========\n";

        int totalGroups = countGroups(partition);

        vector<vector<int>> quotient(
            totalGroups,
            vector<int>(totalGroups, 0)
        );

        // Count neighbours in each group for one representative.
        vector<int> representative(totalGroups, -1);

        for (int vertex = 0; vertex < V; vertex++) {

            if (representative[partition[vertex]] == -1) {
                representative[partition[vertex]] = vertex;
            }
        }

        for (int i = 0; i < totalGroups; i++) {

            int vertex = representative[i];

            for (int j = 0; j < totalGroups; j++) {

                quotient[i][j] = countNeighboursInGroup(
                    vertex,
                    j,
                    partition
                );
            }
        }

        cout << "\nQuotient adjacency matrix:\n";

        cout << "     ";

        for (int j = 0; j < totalGroups; j++) {
            cout << setw(4) << j;
        }

        cout << "\n";

        for (int i = 0; i < totalGroups; i++) {

            cout << setw(4) << i << " ";

            for (int j = 0; j < totalGroups; j++) {
                cout << setw(4) << quotient[i][j];
            }

            cout << "\n";
        }

        cout << "\nQuotient graph groups:\n";

        for (int group = 0; group < totalGroups; group++) {

            cout << "Quotient vertex " << group << " represents { ";

            for (int vertex = 0; vertex < V; vertex++) {

                if (partition[vertex] == group) {
                    cout << vertex << " ";
                }
            }

            cout << "}\n";
        }
    }

    void verifyEquitablePartition() {

        cout << "\n========== EQUITABLE PARTITION VERIFICATION ==========\n";

        int totalGroups = countGroups(partition);

        bool equitable = true;

        for (int u = 0; u < V; u++) {

            for (int v = u + 1; v < V; v++) {

                if (partition[u] != partition[v]) {
                    continue;
                }

                for (int group = 0; group < totalGroups; group++) {

                    int countU = countNeighboursInGroup(
                        u,
                        group,
                        partition
                    );

                    int countV = countNeighboursInGroup(
                        v,
                        group,
                        partition
                    );

                    if (countU != countV) {

                        equitable = false;

                        cout << "Vertices " << u << " and " << v
                             << " have different neighbour counts "
                             << "in group " << group << ".\n";
                    }
                }
            }
        }

        if (equitable) {
            cout << "The final partition is equitable.\n";
        }
        else {
            cout << "The final partition is not equitable.\n";
        }
    }
};

int main() {

    int V, E;

    cout << "EQUITABLE PARTITION AND QUOTIENT GRAPH\n";

    cout << "Enter number of vertices (maximum 20): ";
    cin >> V;

    if (V <= 0 || V > 20) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0 || E > V * (V - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    Graph graph(V);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter edges (u v):\n";

    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertex. Enter again.\n";
            i--;
            continue;
        }

        if (u == v) {
            cout << "Self-loops are not allowed. Enter again.\n";
            i--;
            continue;
        }

        if (u > v) {
            swap(u, v);
        }

        if (existingEdges.count({u, v})) {
            cout << "Duplicate edge. Enter again.\n";
            i--;
            continue;
        }

        existingEdges.insert({u, v});

        graph.addEdge(u, v);
    }

    graph.displayGraph();

    graph.initializePartition();

    graph.refinePartition();

    graph.displayNeighbourCounts();

    graph.verifyEquitablePartition();

    graph.constructQuotientGraph();

    cout << "\nProgram completed successfully.\n";

    return 0;
}
