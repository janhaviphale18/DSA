#include <iostream>
using namespace std;

struct Element
{
    int value;
    int frequency;
};

class FrequencySort
{
private:
    int arr[100];
    int size;

    Element freqArr[100];
    int uniqueCount;

    Element heap[100];
    int heapSize;

    // Check whether element a has higher priority than b
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

    // Restore Max Heap property downwards
    void heapifyDown(int index)
    {
        while (true)
        {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < heapSize &&
                isBetter(heap[left], heap[largest]))
            {
                largest = left;
            }

            if (right < heapSize &&
                isBetter(heap[right], heap[largest]))
            {
                largest = right;
            }

            if (largest == index)
            {
                break;
            }

            swapElement(heap[index], heap[largest]);

            index = largest;
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

    // Build Max Heap using bottom-up approach
    void buildMaxHeap()
    {
        heapSize = uniqueCount;

        for (int i = 0; i < uniqueCount; i++)
        {
            heap[i] = freqArr[i];
        }

        for (int i = heapSize / 2 - 1; i >= 0; i--)
        {
            heapifyDown(i);
        }
    }

    // Extract highest-priority element
    Element extractMax()
    {
        Element maximum = heap[0];

        heap[0] = heap[heapSize - 1];
        heapSize--;

        if (heapSize > 0)
        {
            heapifyDown(0);
        }

        return maximum;
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

    // Perform frequency-based sorting
    void sortByFrequency()
    {
        buildMaxHeap();

        cout << "\nFrequency Table:" << endl;

        for (int i = 0; i < uniqueCount; i++)
        {
            cout << freqArr[i].value
                 << " occurs "
                 << freqArr[i].frequency
                 << " times" << endl;
        }

        cout << "\nSorted Array by Frequency:" << endl;

        while (heapSize > 0)
        {
            Element current = extractMax();

            for (int i = 0; i < current.frequency; i++)
            {
                cout << current.value << " ";
            }
        }

        cout << endl;
    }
};

int main()
{
    FrequencySort obj;

    if (!obj.input())
    {
        return 0;
    }

    obj.sortByFrequency();

    return 0;
}
