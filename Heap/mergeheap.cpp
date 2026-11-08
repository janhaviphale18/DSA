
#include <iostream>
using namespace std;

const int MAX = 1000;

void heapifyDown(int arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
    {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest])
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapifyDown(arr, n, smallest);
    }
}

void buildMinHeap(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapifyDown(arr, n, i);
    }
}

void displayHeap(int arr[], int n)
{
    if (n == 0)
    {
        cout << "Heap is empty.\n";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    int heap1[MAX], heap2[MAX];
    int merged[2 * MAX];

    int n1, n2;

    cout << "Enter number of elements in first heap: ";
    cin >> n1;

    if (n1 < 0 || n1 > MAX)
    {
        cout << "Invalid size for first heap.\n";
        return 1;
    }

    cout << "Enter elements of first heap: ";

    for (int i = 0; i < n1; i++)
    {
        cin >> heap1[i];
    }

    cout << "\nEnter number of elements in second heap: ";
    cin >> n2;

    if (n2 < 0 || n2 > MAX)
    {
        cout << "Invalid size for second heap.\n";
        return 1;
    }

    if (n1 + n2 == 0)
    {
        cout << "Both heaps are empty. Nothing to merge.\n";
        return 0;
    }

    cout << "Enter elements of second heap: ";

    for (int i = 0; i < n2; i++)
    {
        cin >> heap2[i];
    }

    // Build the first Min Heap
    buildMinHeap(heap1, n1);

    // Build the second Min Heap
    buildMinHeap(heap2, n2);

    cout << "\nFirst Min Heap: ";
    displayHeap(heap1, n1);

    cout << "Second Min Heap: ";
    displayHeap(heap2, n2);

    // Copy elements of the first heap
    for (int i = 0; i < n1; i++)
    {
        merged[i] = heap1[i];
    }

    // Copy elements of the second heap
    for (int i = 0; i < n2; i++)
    {
        merged[n1 + i] = heap2[i];
    }

    int total = n1 + n2;

    // Build the final merged Min Heap
    buildMinHeap(merged, total);

    cout << "\nMerged Min Heap: ";
    displayHeap(merged, total);

    cout << "\nTotal elements after merging: " << total << endl;

    return 0;
}
