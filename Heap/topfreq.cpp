#include <iostream>
using namespace std;

struct Element
{
    int value;
    int frequency;
};

class TopKFrequent
{
private:
    int arr[100];
    int size;

    Element freqArr[100];
    int uniqueCount;

    Element heap[100];
    int heapSize;

    // Check whether one element has lower priority
    bool isWorse(Element a, Element b)
    {
        if (a.frequency != b.frequency)
        {
            return a.frequency < b.frequency;
        }

        return a.value > b.value;
    }

    // Check whether one element has higher priority
    bool isBetter(Element a, Element b)
    {
        if (a.frequency != b.frequency)
        {
            return a.frequency > b.frequency;
        }

        return a.value < b.value;
    }

    // Swap two elements
    void swapElement(Element &a, Element &b)
    {
        Element temp = a;
        a = b;
        b = temp;
    }

    // Restore Min Heap property upwards
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (!isWorse(heap[index], heap[parent]))
            {
                break;
            }

            swapElement(heap[index], heap[parent]);
            index = parent;
        }
    }

    // Restore Min Heap property downwards
    void heapifyDown(int index)
    {
        while (true)
        {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < heapSize &&
                isWorse(heap[left], heap[smallest]))
            {
                smallest = left;
            }

            if (right < heapSize &&
                isWorse(heap[right], heap[smallest]))
            {
                smallest = right;
            }

            if (smallest == index)
            {
                break;
            }

            swapElement(heap[index], heap[smallest]);
            index = smallest;
        }
    }

    // Calculate frequency of distinct elements
    void calculateFrequency()
    {
        uniqueCount = 0;

        for (int i = 0; i < size; i++)
        {
            bool found = false;

            for (int j = 0; j < uniqueCount; j++)
            {
                if (freqArr[j].value == arr[i])
                {
                    freqArr[j].frequency++;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                freqArr[uniqueCount].value = arr[i];
                freqArr[uniqueCount].frequency = 1;
                uniqueCount++;
            }
        }
    }

    // Insert an element into Min Heap
    void insert(Element e)
    {
        heap[heapSize] = e;
        heapifyUp(heapSize);
        heapSize++;
    }

    // Replace the root with a better element
    void replaceRoot(Element e)
    {
        heap[0] = e;
        heapifyDown(0);
    }

public:
    // Accept user input
    bool input()
    {
        cout << "Enter number of elements (1-100): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > 100)
        {
            cout << "Invalid array size!" << endl;
            return false;
        }

        cout << "Enter array elements:" << endl;

        for (int i = 0; i < size; i++)
        {
            cin >> arr[i];

            if (cin.fail())
            {
                cout << "Invalid element!" << endl;
                return false;
            }
        }

        calculateFrequency();

        return true;
    }

    // Find Top K frequent elements
    void findTopK(int k)
    {
        if (k < 1 || k > uniqueCount)
        {
            cout << "Invalid value of K!" << endl;
            return;
        }

        heapSize = 0;

        // Process every distinct element
        for (int i = 0; i < uniqueCount; i++)
        {
            if (heapSize < k)
            {
                insert(freqArr[i]);
            }
            else if (isBetter(freqArr[i], heap[0]))
            {
                replaceRoot(freqArr[i]);
            }
        }

        cout << "\nFrequency Table:" << endl;

        for (int i = 0; i < uniqueCount; i++)
        {
            cout << freqArr[i].value
                 << " occurs "
                 << freqArr[i].frequency
                 << " times" << endl;
        }

        cout << "\nTop " << k
             << " Frequent Elements:" << endl;

        // Sort the retained K elements for display
        Element result[100];

        for (int i = 0; i < heapSize; i++)
        {
            result[i] = heap[i];
        }

        for (int i = 0; i < heapSize - 1; i++)
        {
            for (int j = i + 1; j < heapSize; j++)
            {
                if (isBetter(result[j], result[i]))
                {
                    swapElement(result[i], result[j]);
                }
            }
        }

        for (int i = 0; i < heapSize; i++)
        {
            cout << result[i].value
                 << " (Frequency: "
                 << result[i].frequency << ")" << endl;
        }
    }
};

int main()
{
    TopKFrequent obj;

    if (!obj.input())
    {
        return 0;
    }

    int k;

    cout << "Enter the value of K: ";
    cin >> k;

    if (cin.fail())
    {
        cout << "Invalid value of K!" << endl;
        return 0;
    }

    obj.findTopK(k);

    return 0;
}
