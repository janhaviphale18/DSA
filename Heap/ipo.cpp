#include <iostream>
using namespace std;

struct Project
{
    long long capital;
    long long profit;
};

class MinHeap
{
    Project heap[1000];
    int size;

public:
    MinHeap()
    {
        size = 0;
    }

    void insert(Project p)
    {
        if (size == 1000)
        {
            cout << "Min Heap is full!" << endl;
            return;
        }

        int i = size;
        heap[i] = p;
        size++;

        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[parent].capital <= heap[i].capital)
                break;

            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    Project extractMin()
    {
        Project result = heap[0];

        heap[0] = heap[size - 1];
        size--;

        int i = 0;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size &&
                heap[left].capital < heap[smallest].capital)
            {
                smallest = left;
            }

            if (right < size &&
                heap[right].capital < heap[smallest].capital)
            {
                smallest = right;
            }

            if (smallest == i)
                break;

            swap(heap[i], heap[smallest]);
            i = smallest;
        }

        return result;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

class MaxHeap
{
    long long heap[1000];
    int size;

public:
    MaxHeap()
    {
        size = 0;
    }

    void insert(long long profit)
    {
        if (size == 1000)
        {
            cout << "Max Heap is full!" << endl;
            return;
        }

        int i = size;
        heap[i] = profit;
        size++;

        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[parent] >= heap[i])
                break;

            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    long long extractMax()
    {
        long long result = heap[0];

        heap[0] = heap[size - 1];
        size--;

        int i = 0;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < size &&
                heap[left] > heap[largest])
            {
                largest = left;
            }

            if (right < size &&
                heap[right] > heap[largest])
            {
                largest = right;
            }

            if (largest == i)
                break;

            swap(heap[i], heap[largest]);
            i = largest;
        }

        return result;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    long long getMax()
    {
        return heap[0];
    }
};

int main()
{
    int n, k;
    long long initialCapital;

    cout << "Enter number of projects: ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of projects!" << endl;
        return 0;
    }

    cout << "Enter maximum number of projects to select: ";
    cin >> k;

    if (k < 0 || k > n)
    {
        cout << "Invalid value of K!" << endl;
        return 0;
    }

    cout << "Enter initial capital: ";
    cin >> initialCapital;

    if (initialCapital < 0)
    {
        cout << "Initial capital cannot be negative!" << endl;
        return 0;
    }

    MinHeap minHeap;
    MaxHeap maxHeap;

    cout << "\nEnter required capital and profit for each project:\n";

    for (int i = 0; i < n; i++)
    {
        Project p;

        cout << "Project " << i + 1 << ":\n";

        cout << "Required capital: ";
        cin >> p.capital;

        cout << "Profit: ";
        cin >> p.profit;

        if (p.capital < 0 || p.profit < 0)
        {
            cout << "Capital and profit cannot be negative!" << endl;
            return 0;
        }

        minHeap.insert(p);
    }

    long long currentCapital = initialCapital;
    int selected = 0;

    for (int i = 0; i < k; i++)
    {
        // Add all affordable projects to Max Heap.
        while (!minHeap.isEmpty())
        {
            Project p = minHeap.extractMin();

            if (p.capital <= currentCapital)
            {
                maxHeap.insert(p.profit);
            }
            else
            {
                // Put the unaffordable project back.
                minHeap.insert(p);
                break;
            }
        }

        // Stop if no project is affordable.
        if (maxHeap.isEmpty())
            break;

        // No benefit in selecting a zero-profit project.
        if (maxHeap.getMax() == 0)
            break;

        // Select the project with maximum profit.
        long long profit = maxHeap.extractMax();

        currentCapital += profit;
        selected++;
    }

    cout << "\n========== RESULT ==========\n";

    cout << "Projects selected: " << selected << endl;
    cout << "Final maximum capital: " << currentCapital << endl;

    return 0;
}