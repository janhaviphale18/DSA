#include <iostream>
#include <string>
using namespace std;

struct Word
{
    string value;
    int frequency;
};

class TopKWords
{
private:
    string arr[100];
    int size;

    Word freqArr[100];
    int uniqueCount;

    Word heap[100];
    int heapSize;

    // Check whether a is worse than b
    bool isWorse(Word a, Word b)
    {
        if (a.frequency != b.frequency)
        {
            return a.frequency < b.frequency;
        }

        return a.value > b.value;
    }

    // Check whether a is better than b
    bool isBetter(Word a, Word b)
    {
        if (a.frequency != b.frequency)
        {
            return a.frequency > b.frequency;
        }

        return a.value < b.value;
    }

    // Swap two Word structures
    void swapWord(Word &a, Word &b)
    {
        Word temp = a;
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

            swapWord(heap[index], heap[parent]);

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

            swapWord(heap[index], heap[smallest]);

            index = smallest;
        }
    }

    // Calculate frequency of each distinct word
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

    // Insert word into Min Heap
    void insert(Word w)
    {
        heap[heapSize] = w;

        heapifyUp(heapSize);

        heapSize++;
    }

    // Replace root with a better word
    void replaceRoot(Word w)
    {
        heap[0] = w;

        heapifyDown(0);
    }

public:
    // Accept input from user
    bool input()
    {
        cout << "Enter number of words (1-100): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > 100)
        {
            cout << "Invalid number of words!" << endl;
            return false;
        }

        cout << "Enter " << size << " words:" << endl;

        for (int i = 0; i < size; i++)
        {
            cin >> arr[i];

            if (cin.fail())
            {
                cout << "Invalid word!" << endl;
                return false;
            }
        }

        calculateFrequency();

        return true;
    }

    // Find Top K frequent words
    void findTopK(int k)
    {
        if (k < 1 || k > uniqueCount)
        {
            cout << "Invalid value of K!" << endl;
            return;
        }

        heapSize = 0;

        // Process all distinct words
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

        cout << "\nWord Frequency Table:" << endl;

        for (int i = 0; i < uniqueCount; i++)
        {
            cout << freqArr[i].value
                 << " : " << freqArr[i].frequency
                 << endl;
        }

        // Copy selected words for final sorting
        Word result[100];

        for (int i = 0; i < heapSize; i++)
        {
            result[i] = heap[i];
        }

        // Sort by frequency descending
        // For equal frequencies, sort alphabetically
        for (int i = 0; i < heapSize - 1; i++)
        {
            for (int j = i + 1; j < heapSize; j++)
            {
                if (isBetter(result[j], result[i]))
                {
                    swapWord(result[i], result[j]);
                }
            }
        }

        cout << "\nTop " << k << " Frequent Words:" << endl;

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
    TopKWords obj;

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