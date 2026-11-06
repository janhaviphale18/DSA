#include <iostream>
#include <string>
using namespace std;

struct Character
{
    char ch;
    int frequency;
};

class MaxHeap
{
    Character heap[256];
    int size;

    bool hasHigherPriority(Character a, Character b)
    {
        if (a.frequency != b.frequency)
            return a.frequency > b.frequency;

        return a.ch < b.ch;
    }

    void heapifyDown(int index)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size &&
            hasHigherPriority(heap[left], heap[largest]))
        {
            largest = left;
        }

        if (right < size &&
            hasHigherPriority(heap[right], heap[largest]))
        {
            largest = right;
        }

        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap()
    {
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void insert(Character element)
    {
        if (size == 256)
            return;

        int index = size;
        heap[size] = element;
        size++;

        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (!hasHigherPriority(heap[index], heap[parent]))
                break;

            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    Character extractMax()
    {
        Character maximum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return maximum;
    }
};

int main()
{
    string input;
    int frequency[256] = {0};

    cout << "Enter a string (without spaces): ";
    cin >> input;

    int n = input.length();

    // Count the frequency of each character.
    for (int i = 0; i < n; i++)
    {
        unsigned char ch = input[i];
        frequency[ch]++;
    }

    MaxHeap maxHeap;

    // Insert each distinct character into the Max Heap.
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            Character element;

            element.ch = (char)i;
            element.frequency = frequency[i];

            maxHeap.insert(element);
        }
    }

    string result = "";

    Character previous;
    previous.frequency = 0;
    previous.ch = '\0';

    // Reorganize the string.
    while (!maxHeap.isEmpty())
    {
        Character current = maxHeap.extractMax();

        result += current.ch;
        current.frequency--;

        // Reinsert the previously used character.
        if (previous.frequency > 0)
        {
            maxHeap.insert(previous);
        }

        // Hold the current character for the next iteration.
        previous = current;
    }

    if ((int)result.length() != n)
    {
        cout << "\nReorganization is not possible!";
    }
    else
    {
        cout << "\nReorganized string: " << result << endl;
    }

    return 0;
}
