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

void printKthLevel(Node* root, int k) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    int level = 0;

    while (!q.empty()) {
        int size = q.size();

        if (level == k) {
            for (int i = 0; i < size; i++) {
                cout << q.front()->data << " ";
                q.pop();
            }
            return;
        }

        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }

        level++;
    }

    cout << "Level does not exist";
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int k;
    cout << "Enter level: ";
    cin >> k;

    cout << "Nodes at level " << k << ": ";

    printKthLevel(root, k);

    return 0;
}