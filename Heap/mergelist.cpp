
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = NULL;
    }
};

struct HeapElement
{
    Node* node;
};

class MinHeap
{
    HeapElement heap[10];
    int size;

    void heapifyDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size &&
            heap[left].node->data < heap[smallest].node->data)
        {
            smallest = left;
        }

        if (right < size &&
            heap[right].node->data < heap[smallest].node->data)
        {
            smallest = right;
        }

        if (smallest != index)
        {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap()
    {
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void insert(Node* node)
    {
        if (size == 10)
            return;

        int index = size;
        heap[size].node = node;
        size++;

        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent].node->data <= heap[index].node->data)
                break;

            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    Node* extractMin()
    {
        Node* minimum = heap[0].node;

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return minimum;
    }
};

Node* createList(int n, int listNumber)
{
    Node* head = NULL;
    Node* tail = NULL;

    int value, previous;

    cout << "Enter sorted elements of list "
         << listNumber << ": ";

    for (int i = 0; i < n; i++)
    {
        cin >> value;

        if (i > 0 && value < previous)
        {
            cout << "List must be sorted in ascending order!\n";
            
            while (head != NULL)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }

            return NULL;
        }

        Node* newNode = new Node(value);

        if (head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        previous = value;
    }

    return head;
}

void displayList(Node* head)
{
    while (head != NULL)
    {
        cout << head->data;

        if (head->next != NULL)
            cout << " -> ";

        head = head->next;
    }

    cout << endl;
}

void deleteList(Node* head)
{
    while (head != NULL)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int k;

    cout << "Enter number of sorted linked lists (1-10): ";
    cin >> k;

    if (k < 1 || k > 10)
    {
        cout << "Invalid number of linked lists!";
        return 0;
    }

    Node* heads[10] = {NULL};

    for (int i = 0; i < k; i++)
    {
        int n;

        cout << "\nEnter number of nodes in list "
             << i + 1 << " (1-100): ";
        cin >> n;

        if (n < 1 || n > 100)
        {
            cout << "Invalid number of nodes!";
            
            for (int j = 0; j < i; j++)
                deleteList(heads[j]);

            return 0;
        }

        heads[i] = createList(n, i + 1);

        if (heads[i] == NULL)
        {
            for (int j = 0; j <= i; j++)
                deleteList(heads[j]);

            return 0;
        }
    }

    MinHeap minHeap;

    // Insert the first node of every linked list.
    for (int i = 0; i < k; i++)
    {
        minHeap.insert(heads[i]);
    }

    Node* mergedHead = NULL;
    Node* mergedTail = NULL;

    // Extract the smallest node and insert its next node.
    while (!minHeap.isEmpty())
    {
        Node* minimum = minHeap.extractMin();

        Node* nextNode = minimum->next;

        // Detach the extracted node.
        minimum->next = NULL;

        if (mergedHead == NULL)
        {
            mergedHead = mergedTail = minimum;
        }
        else
        {
            mergedTail->next = minimum;
            mergedTail = minimum;
        }

        if (nextNode != NULL)
        {
            minHeap.insert(nextNode);
        }
    }

    cout << "\nMerged sorted linked list:\n";
    displayList(mergedHead);

    deleteList(mergedHead);

    return 0;
}
