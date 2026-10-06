#include <iostream>
#include <vector>
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

void printDown(Node* root, int k, Node* block) {
    if (root == NULL || root == block || k < 0)
        return;

    if (k == 0) {
        cout << root->data << " ";
        return;
    }

    printDown(root->left, k - 1, block);
    printDown(root->right, k - 1, block);
}

int printDistance(Node* root, int target, int k) {
    if (root == NULL)
        return -1;

    if (root->data == target) {
        printDown(root, k, NULL);
        return 0;
    }

    int leftDistance = printDistance(root->left, target, k);

    if (leftDistance != -1) {
        int distance = leftDistance + 1;

        if (distance == k)
            cout << root->data << " ";
        else
            printDown(root->right, k - distance - 1, NULL);

        return distance;
    }

    int rightDistance = printDistance(root->right, target, k);

    if (rightDistance != -1) {
        int distance = rightDistance + 1;

        if (distance == k)
            cout << root->data << " ";
        else
            printDown(root->left, k - distance - 1, NULL);

        return distance;
    }

    return -1;
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    int target, k;

    cout << "Enter target node: ";
    cin >> target;

    cout << "Enter distance k: ";
    cin >> k;

    cout << "Nodes at distance " << k
         << " from " << target << ": ";

    if (printDistance(root, target, k) == -1)
        cout << "Target node not found";

    return 0;
}