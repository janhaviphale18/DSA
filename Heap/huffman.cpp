
#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Node
{
    char data;
    int frequency;

    Node* left;
    Node* right;

    Node(char ch, int freq)
    {
        data = ch;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }
};

class MinHeap
{
private:
    Node* heap[MAX];
    int size;

    void heapifyDown(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size &&
            heap[left]->frequency < heap[smallest]->frequency)
        {
            smallest = left;
        }

        if (right < size &&
            heap[right]->frequency < heap[smallest]->frequency)
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[i]->frequency < heap[parent]->frequency)
            {
                swap(heap[i], heap[parent]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

public:
    MinHeap()
    {
        size = 0;
    }

    bool insert(Node* newNode)
    {
        if (size == MAX)
        {
            return false;
        }

        heap[size] = newNode;
        heapifyUp(size);
        size++;

        return true;
    }

    Node* extractMin()
    {
        if (size == 0)
        {
            return nullptr;
        }

        Node* minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
        {
            heapifyDown(0);
        }

        return minimum;
    }

    int getSize()
    {
        return size;
    }
};

void generateCodes(Node* root, string code)
{
    if (root == nullptr)
    {
        return;
    }

    // Leaf node represents an original character
    if (root->left == nullptr && root->right == nullptr)
    {
        if (code.empty())
        {
            code = "0";
        }

        cout << root->data << " : " << code << endl;
        return;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

Node* buildHuffmanTree(char characters[], int frequencies[], int n)
{
    MinHeap minHeap;

    // Insert all characters into the Min Heap
    for (int i = 0; i < n; i++)
    {
        Node* newNode = new Node(characters[i], frequencies[i]);
        minHeap.insert(newNode);
    }

    // Combine the two minimum-frequency nodes repeatedly
    while (minHeap.getSize() > 1)
    {
        Node* left = minHeap.extractMin();
        Node* right = minHeap.extractMin();

        Node* parent = new Node(
            '\0',
            left->frequency + right->frequency
        );

        parent->left = left;
        parent->right = right;

        minHeap.insert(parent);
    }

    return minHeap.extractMin();
}

void deleteTree(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main()
{
    char characters[MAX];
    int frequencies[MAX];

    int n;

    cout << "Enter number of distinct characters: ";
    cin >> n;

    if (n < 1 || n > MAX)
    {
        cout << "Invalid number of characters.\n";
        return 1;
    }

    cout << "\nEnter characters and their frequencies:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Character " << i + 1 << ": ";
        cin >> characters[i];

        cout << "Frequency: ";
        cin >> frequencies[i];

        if (frequencies[i] <= 0)
        {
            cout << "Frequency must be positive.\n";
            return 1;
        }

        for (int j = 0; j < i; j++)
        {
            if (characters[i] == characters[j])
            {
                cout << "Duplicate characters are not allowed.\n";
                return 1;
            }
        }
    }

    Node* root = buildHuffmanTree(characters, frequencies, n);

    cout << "\nHuffman Codes:\n";
    generateCodes(root, "");

    deleteTree(root);

    return 0;
}
