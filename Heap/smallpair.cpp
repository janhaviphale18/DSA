#include <iostream>
using namespace std;

struct PairElement
{
    int first;
    int second;
    int i;
    int j;
    long long sum;
};

class MinHeap
{
    PairElement heap[100];
    int size;

    bool isSmaller(PairElement a, PairElement b)
    {
        if (a.sum != b.sum)
            return a.sum < b.sum;

        if (a.i != b.i)
            return a.i < b.i;

        return a.j < b.j;
    }

    void heapifyDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size &&
            isSmaller(heap[left], heap[smallest]))
        {
            smallest = left;
        }

        if (right < size &&
            isSmaller(heap[right], heap[smallest]))
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

    void insert(PairElement element)
    {
        if (size == 100)
            return;

        int index = size;
        heap[size] = element;
        size++;

        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (!isSmaller(heap[index], heap[parent]))
                break;

            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    PairElement extractMin()
    {
        PairElement minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return minimum;
    }
};

int main()
{
    int n1, n2, k;

    int arr1[100], arr2[100];

    cout << "Enter size of first array (1-100): ";
    cin >> n1;

    if (n1 < 1 || n1 > 100)
    {
        cout << "Invalid array size!";
        return 0;
    }

    cout << "Enter elements of first sorted array: ";

    for (int i = 0; i < n1; i++)
    {
        cin >> arr1[i];

        if (i > 0 && arr1[i] < arr1[i - 1])
        {
            cout << "First array must be sorted!";
            return 0;
        }
    }

    cout << "\nEnter size of second array (1-100): ";
    cin >> n2;

    if (n2 < 1 || n2 > 100)
    {
        cout << "Invalid array size!";
        return 0;
    }

    cout << "Enter elements of second sorted array: ";

    for (int j = 0; j < n2; j++)
    {
        cin >> arr2[j];

        if (j > 0 && arr2[j] < arr2[j - 1])
        {
            cout << "Second array must be sorted!";
            return 0;
        }
    }

    int totalPairs = n1 * n2;

    cout << "\nEnter K (1 to " << totalPairs << "): ";
    cin >> k;

    if (k < 1 || k > totalPairs)
    {
        cout << "Invalid value of K!";
        return 0;
    }

    MinHeap minHeap;

    // Insert the first pair from selected rows.
    int initialRows = (k < n1) ? k : n1;

    for (int i = 0; i < initialRows; i++)
    {
        PairElement element;

        element.first = arr1[i];
        element.second = arr2[0];
        element.i = i;
        element.j = 0;
        element.sum = (long long)arr1[i] + arr2[0];

        minHeap.insert(element);
    }

    cout << "\n" << k << " pairs with the smallest sums:\n";

    // Extract K minimum-sum pairs.
    for (int count = 0; count < k; count++)
    {
        PairElement minimum = minHeap.extractMin();

        cout << "(" << minimum.first << ", "
             << minimum.second << ")"
             << " -> Sum: " << minimum.sum << endl;

        int nextIndex = minimum.j + 1;
        int row = minimum.i;

        // Insert the next pair from the same row.
        if (nextIndex < n2)
        {
            PairElement nextElement;

            nextElement.first = arr1[row];
            nextElement.second = arr2[nextIndex];
            nextElement.i = row;
            nextElement.j = nextIndex;
            nextElement.sum =
                (long long)arr1[row] + arr2[nextIndex];

            minHeap.insert(nextElement);
        }
    }

    return 0;
}
