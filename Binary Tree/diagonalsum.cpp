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

void diagonalSum(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    cout << "Diagonal sums: ";

    while (!q.empty()) {
        int sum = 0;
        int size = q.size();

        while (size--) {
            Node* current = q.front();
            q.pop();

            while (current != NULL) {
                sum += current->data;

                if (current->left != NULL)
                    q.push(current->left);

                current = current->right;
            }
        }

        cout << sum << " ";
    }
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    diagonalSum(root);

    return 0;
}