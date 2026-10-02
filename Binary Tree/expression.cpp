#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;

    Node(string value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

bool isOperator(string value) {
    return value == "+" || value == "-" ||
           value == "*" || value == "/";
}

Node* createExpressionTree() {
    int n;

    cout << "Enter number of postfix elements: ";
    cin >> n;

    stack<Node*> st;

    cout << "Enter postfix expression: ";

    for (int i = 0; i < n; i++) {
        string value;
        cin >> value;

        Node* node = new Node(value);

        if (isOperator(value)) {
            Node* right = st.top();
            st.pop();

            Node* left = st.top();
            st.pop();

            node->left = left;
            node->right = right;
        }

        st.push(node);
    }

    return st.top();
}

int evaluate(Node* root) {
    if (root == NULL)
        return 0;

    if (!isOperator(root->data))
        return stoi(root->data);

    int left = evaluate(root->left);
    int right = evaluate(root->right);

    if (root->data == "+")
        return left + right;

    if (root->data == "-")
        return left - right;

    if (root->data == "*")
        return left * right;

    return left / right;
}

void inorder(Node* root) {
    if (root == NULL)
        return;

    if (isOperator(root->data))
        cout << "(";

    inorder(root->left);

    cout << root->data;

    inorder(root->right);

    if (isOperator(root->data))
        cout << ")";
}

int main() {
    Node* root = createExpressionTree();

    cout << "Inorder expression: ";
    inorder(root);

    cout << endl;

    cout << "Result: " << evaluate(root);

    return 0;
}