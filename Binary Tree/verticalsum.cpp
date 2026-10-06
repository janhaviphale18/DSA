#include <iostream>
#include <map>
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

void verticalSum(Node* root) {
    if (root == NULL)
        return;

    map<int, int> sum;
    queue<pair<Node*, int>> q;

    q.push({root, 0});

    while (!q.empty()) {
        Node* current = q.front().first;
        int hd = q.front().second;
        q.pop();

        sum[hd] += current->data;

        if (current->left != NULL)
            q.push({current->left, hd - 1});

        if (current->right != NULL)
            q.push({current->right, hd + 1});
    }

    cout << "Vertical sums: ";

    for (auto entry : sum)
        cout << entry.second << " ";
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    verticalSum(root);

    return 0;
}