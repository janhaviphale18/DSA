#include <iostream>
#include <map>
#include <string>
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

string serialize(Node* root, map<string, int>& count) {
    if (root == NULL)
        return "#";

    string left = serialize(root->left, count);
    string right = serialize(root->right, count);

    string current = to_string(root->data) + "," + left + "," + right;

    count[current]++;

    if (count[current] == 2)
        cout << "Duplicate subtree rooted at: "
             << root->data << endl;

    return current;
}

int main() {
    cout << "Enter tree elements (-1 for NULL): ";

    Node* root = create();

    map<string, int> count;

    serialize(root, count);

    return 0;
}