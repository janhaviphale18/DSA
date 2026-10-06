#include <iostream>
#include <queue>
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

void diagonalTraversal(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    cout << "Diagonal traversal: ";

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        while (current != NULL) {
            cout << current->data << " ";

            if (current->left != NULL)
                q.push(current->left);

            current = current->right;
        }
    }
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    diagonalTraversal(root);

    return 0;
}