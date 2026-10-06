#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

Node* create() {
    int value;
    cin >> value;

    if (value == -1)
        return NULL;

    Node* root = new Node(value);

    root->left = create();
    root->right = create();

    return root;
}

void storeParents(Node* root, map<Node*, Node*>& parent,
                  Node*& target, int key) {
    if (root == NULL)
        return;

    if (root->data == key)
        target = root;

    if (root->left != NULL) {
        parent[root->left] = root;
        storeParents(root->left, parent, target, key);
    }

    if (root->right != NULL) {
        parent[root->right] = root;
        storeParents(root->right, parent, target, key);
    }
}

int burnTree(Node* target, map<Node*, Node*>& parent) {
    if (target == NULL)
        return -1;

    queue<Node*> q;
    map<Node*, bool> visited;

    q.push(target);
    visited[target] = true;

    int time = 0;

    while (!q.empty()) {
        int size = q.size();
        bool burned = false;

        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();

            if (current->left != NULL &&
                !visited[current->left]) {
                visited[current->left] = true;
                q.push(current->left);
                burned = true;
            }

            if (current->right != NULL &&
                !visited[current->right]) {
                visited[current->right] = true;
                q.push(current->right);
                burned = true;
            }

            if (parent.count(current) &&
                !visited[parent[current]]) {
                visited[parent[current]] = true;
                q.push(parent[current]);
                burned = true;
            }
        }

        if (burned)
            time++;
    }

    return time;
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int key;
    cout << "Enter fire starting node: ";
    cin >> key;

    map<Node*, Node*> parent;
    Node* target = NULL;

    storeParents(root, parent, target, key);

    if (target == NULL) {
        cout << "Target node not found";
        return 0;
    }

    cout << "Minimum time to burn tree: "
         << burnTree(target, parent);

    return 0;
}