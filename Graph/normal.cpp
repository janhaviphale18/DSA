#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <queue>
using namespace std;

using Permutation = vector<int>;

class NormalSubgroup {
private:
    int n;

    vector<vector<int>> adj;
    vector<int> degree;

    vector<int> mapping;
    vector<bool> used;

    vector<Permutation> automorphisms;
    map<Permutation, int> groupIndex;

    vector<Permutation> subgroup;
    map<Permutation, int> subgroupIndex;

    Permutation identity;

    Permutation compose(const Permutation& p,
                        const Permutation& q) const {
        // p o q: apply q first, then p.
        Permutation result(n);

        for (int i = 0; i < n; i++) {
            result[i] = p[q[i]];
        }

        return result;
    }

    Permutation inverse(const Permutation& p) const {
        Permutation result(n);

        for (int i = 0; i < n; i++) {
            result[p[i]] = i;
        }

        return result;
    }

    bool compatible(int vertex, int candidate) const {
        if (degree[vertex] != degree[candidate]) {
            return false;
        }

        for (int previous = 0; previous < vertex; previous++) {
            if (adj[vertex][previous] !=
                adj[candidate][mapping[previous]]) {
                return false;
            }
        }

        return true;
    }

    void backtrack(int vertex) {
        if (vertex == n) {
            automorphisms.push_back(mapping);
            return;
        }

        for (int candidate = 0; candidate < n; candidate++) {
            if (used[candidate]) {
                continue;
            }

            if (!compatible(vertex, candidate)) {
                continue;
            }

            mapping[vertex] = candidate;
            used[candidate] = true;

            backtrack(vertex + 1);

            used[candidate] = false;
            mapping[vertex] = -1;
        }
    }

    void printPermutation(const Permutation& p) const {
        cout << "[";

        for (int i = 0; i < n; i++) {
            if (i > 0) {
                cout << " ";
            }

            cout << p[i];
        }

        cout << "]";
    }

public:
    NormalSubgroup(int vertices) {
        n = vertices;

        adj.assign(n, vector<int>(n, 0));
        degree.assign(n, 0);

        mapping.assign(n, -1);
        used.assign(n, false);

        identity.resize(n);
        iota(identity.begin(), identity.end(), 0);
    }

    bool addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        if (u == v || adj[u][v] == 1) {
            return false;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;

        degree[u]++;
        degree[v]++;

        return true;
    }

    void findAutomorphisms() {
        automorphisms.clear();
        groupIndex.clear();

        backtrack(0);

        sort(automorphisms.begin(), automorphisms.end());

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            groupIndex[automorphisms[i]] = i;
        }
    }

    int groupSize() const {
        return (int)automorphisms.size();
    }

    void displayGroup() const {
        cout << "\nFULL AUTOMORPHISM GROUP\n";
        cout << "Group order: " << groupSize() << "\n";

        for (int i = 0; i < groupSize(); i++) {
            cout << "G" << i << " = ";
            printPermutation(automorphisms[i]);

            if (automorphisms[i] == identity) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    bool generateSubgroup(const vector<int>& generatorIDs) {
        subgroup.clear();
        subgroupIndex.clear();

        vector<Permutation> generators;
        set<int> uniqueIDs;

        // Validate and collect generators.
        for (int id : generatorIDs) {
            if (id < 0 || id >= groupSize()) {
                return false;
            }

            if (!uniqueIDs.insert(id).second) {
                continue;
            }

            if (automorphisms[id] == identity) {
                return false;
            }

            generators.push_back(automorphisms[id]);
        }

        // Include the inverse of each generator.
        int originalCount = (int)generators.size();

        for (int i = 0; i < originalCount; i++) {
            Permutation inv = inverse(generators[i]);

            if (find(generators.begin(), generators.end(), inv)
                == generators.end()) {
                generators.push_back(inv);
            }
        }

        // Begin with the identity.
        queue<Permutation> q;

        subgroup.push_back(identity);
        subgroupIndex[identity] = 0;

        q.push(identity);

        // Generate all reachable subgroup elements.
        while (!q.empty()) {
            Permutation current = q.front();
            q.pop();

            for (const auto& generator : generators) {
                Permutation result = compose(current, generator);

                if (groupIndex.find(result) == groupIndex.end()) {
                    cout << "Error: composition is not an automorphism.\n";
                    return false;
                }

                if (subgroupIndex.find(result) ==
                    subgroupIndex.end()) {

                    int index = (int)subgroup.size();

                    subgroup.push_back(result);
                    subgroupIndex[result] = index;

                    q.push(result);
                }
            }
        }

        return true;
    }

    void displaySubgroup() const {
        cout << "\nGENERATED SUBGROUP\n";
        cout << "Subgroup order: " << subgroup.size() << "\n";

        for (int i = 0; i < (int)subgroup.size(); i++) {
            cout << "H" << i << " = ";
            printPermutation(subgroup[i]);

            if (subgroup[i] == identity) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    void checkNormality() const {
        cout << "\nNORMAL SUBGROUP VERIFICATION\n";

        bool normal = true;
        int checked = 0;

        for (int g = 0; g < groupSize(); g++) {
            Permutation inverseG = inverse(automorphisms[g]);

            for (int h = 0; h < (int)subgroup.size(); h++) {
                // Calculate g o h o g^(-1).
                Permutation first =
                    compose(automorphisms[g], subgroup[h]);

                Permutation conjugate =
                    compose(first, inverseG);

                checked++;

                if (subgroupIndex.find(conjugate) ==
                    subgroupIndex.end()) {

                    normal = false;

                    cout << "\nCounterexample found!\n";

                    cout << "g = G" << g << " = ";
                    printPermutation(automorphisms[g]);
                    cout << "\n";

                    cout << "h = H" << h << " = ";
                    printPermutation(subgroup[h]);
                    cout << "\n";

                    cout << "g o h o g^(-1) = ";
                    printPermutation(conjugate);
                    cout << "\n";

                    auto it = groupIndex.find(conjugate);

                    if (it != groupIndex.end()) {
                        cout << "Result belongs to full group as G"
                             << it->second << ".\n";
                    }

                    cout << "But it does not belong to H.\n";

                    return;
                }
            }
        }

        cout << "Conjugates checked: " << checked << "\n";

        if (normal) {
            cout << "The subgroup IS a normal subgroup.\n";
            cout << "H is normal in Aut(G).\n";
        } else {
            cout << "The subgroup is NOT normal.\n";
        }
    }

    void displayConjugates(int groupID, int subgroupID) const {
        if (groupID < 0 || groupID >= groupSize() ||
            subgroupID < 0 ||
            subgroupID >= (int)subgroup.size()) {
            cout << "Invalid element IDs.\n";
            return;
        }

        Permutation g = automorphisms[groupID];
        Permutation h = subgroup[subgroupID];

        Permutation result =
            compose(compose(g, h), inverse(g));

        cout << "\nCONJUGATION RESULT\n";

        cout << "g = G" << groupID << "\n";
        cout << "h = H" << subgroupID << "\n";

        cout << "g o h o g^(-1) = ";
        printPermutation(result);
        cout << "\n";

        auto it = groupIndex.find(result);

        if (it != groupIndex.end()) {
            cout << "Full group element: G" << it->second << "\n";
        }

        if (subgroupIndex.find(result) != subgroupIndex.end()) {
            cout << "The result belongs to the subgroup.\n";
        } else {
            cout << "The result does not belong to the subgroup.\n";
        }
    }
};

int main() {
    int n, m;

    cout << "NORMAL SUBGROUP DETECTION IN GRAPH AUTOMORPHISMS\n";

    cout << "Enter number of vertices (1 to 6): ";

    if (!(cin >> n) || n < 1 || n > 6) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "Enter number of edges: ";

    if (!(cin >> m) || m < 0 || m > n * (n - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 1;
    }

    NormalSubgroup graph(n);

    cout << "Enter edges (u v), using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {
        int u, v;

        if (!(cin >> u >> v)) {
            cout << "Invalid input.\n";
            return 1;
        }

        if (!graph.addEdge(u, v)) {
            cout << "Invalid or duplicate edge.\n";
            return 1;
        }
    }

    graph.findAutomorphisms();
    graph.displayGroup();

    int count;

    cout << "\nEnter number of subgroup generators: ";

    if (!(cin >> count) ||
        count < 0 ||
        count > graph.groupSize() - 1) {
        cout << "Invalid generator count.\n";
        return 1;
    }

    vector<int> generatorIDs(count);

    cout << "Enter generator IDs (without G):\n";

    for (int i = 0; i < count; i++) {
        if (!(cin >> generatorIDs[i])) {
            cout << "Invalid generator input.\n";
            return 1;
        }
    }

    if (!graph.generateSubgroup(generatorIDs)) {
        cout << "Invalid generator selection.\n";
        return 1;
    }

    graph.displaySubgroup();
    graph.checkNormality();

    int gID, hID;

    cout << "\nEnter a full group element ID for conjugation: ";

    if (!(cin >> gID)) {
        cout << "Invalid input.\n";
        return 1;
    }

    cout << "Enter a subgroup element ID for conjugation: ";

    if (!(cin >> hID)) {
        cout << "Invalid input.\n";
        return 1;
    }

    graph.displayConjugates(gID, hID);

    cout << "\nNormal subgroup analysis completed.\n";

    return 0;
}
