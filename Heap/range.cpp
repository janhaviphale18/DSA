#include <iostream>
using namespace std;

struct Element
{
    int value;
    int arrayIndex;
    int elementIndex;
};

class MinHeap
{
    Element heap[10];
    int size;

    void heapifyDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size &&
            heap[left].value < heap[smallest].value)
        {
            smallest = left;
        }

        if (right < size &&
            heap[right].value < heap[smallest].value)
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

    void insert(Element element)
    {
        if (size == 10)
            return;

        int index = size;
        heap[size] = element;
        size++;

        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent].value <= heap[index].value)
                break;

            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    Element extractMin()
    {
        Element minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return minimum;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

int main()
{
    int k;

    cout << "Enter number of sorted arrays (1-10): ";
    cin >> k;

    if (k < 1 || k > 10)
    {
        cout << "Invalid number of arrays!";
        return 0;
    }

    int arrays[10][100];
    int lengths[10];

    for (int i = 0; i < k; i++)
    {
        cout << "\nEnter size of array " << i + 1
             << " (1-100): ";
        cin >> lengths[i];

        if (lengths[i] < 1 || lengths[i] > 100)
        {
            cout << "Invalid array size!";
            return 0;
        }

        cout << "Enter sorted elements: ";

        for (int j = 0; j < lengths[i]; j++)
        {
            cin >> arrays[i][j];

            if (j > 0 && arrays[i][j] < arrays[i][j - 1])
            {
                cout << "Array must be sorted in ascending order!";
                return 0;
            }
        }
    }

    MinHeap minHeap;

    int currentMax = arrays[0][0];

    // Insert the first element of every array.
    for (int i = 0; i < k; i++)
    {
        Element element;

        element.value = arrays[i][0];
        element.arrayIndex = i;
        element.elementIndex = 0;

        minHeap.insert(element);

        if (arrays[i][0] > currentMax)
            currentMax = arrays[i][0];
    }

    int bestStart = minHeap.extractMin().value;

    // Restore the initial heap.
    for (int i = 0; i < k; i++)
    {
        Element element;

        element.value = arrays[i][0];
        element.arrayIndex = i;
        element.elementIndex = 0;

        minHeap.insert(element);
    }

    int bestEnd = currentMax;

    while (!minHeap.isEmpty())
    {
        Element minimum = minHeap.extractMin();

        int currentMin = minimum.value;

        int currentWidth = currentMax - currentMin;
        int bestWidth = bestEnd - bestStart;

        if (currentWidth < bestWidth)
        {
            bestStart = currentMin;
            bestEnd = currentMax;
        }

        int nextIndex = minimum.elementIndex + 1;
        int arrayNumber = minimum.arrayIndex;

        // Stop if one array has no more elements.
        if (nextIndex >= lengths[arrayNumber])
            break;

        int nextValue = arrays[arrayNumber][nextIndex];

        Element nextElement;

        nextElement.value = nextValue;
        nextElement.arrayIndex = arrayNumber;
        nextElement.elementIndex = nextIndex;

        minHeap.insert(nextElement);

        if (nextValue > currentMax)
            currentMax = nextValue;
    }

    cout << "\nSmallest range: ["
         << bestStart << ", " << bestEnd << "]";

    cout << "\nRange width: "
         << bestEnd - bestStart << endl;

    return 0;
}
