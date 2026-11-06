#include <iostream>
#include <string>
using namespace std;

struct Task
{
    char name;
    int frequency;
};

struct CoolingTask
{
    Task task;
    int readyTime;
};

class MaxHeap
{
    Task heap[26];
    int size;

    bool hasHigherPriority(Task a, Task b)
    {
        if (a.frequency != b.frequency)
            return a.frequency > b.frequency;

        return a.name < b.name;
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

    void insert(Task task)
    {
        if (size == 26)
            return;

        int index = size;
        heap[size] = task;
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

    Task extractMax()
    {
        Task maximum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return maximum;
    }
};

int main()
{
    string tasks;
    int cooldown;

    cout << "Enter tasks (uppercase A-Z, maximum 1000): ";
    cin >> tasks;

    int n = tasks.length();

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of tasks!";
        return 0;
    }

    int frequency[26] = {0};

    // Calculate the frequency of each task.
    for (int i = 0; i < n; i++)
    {
        if (tasks[i] < 'A' || tasks[i] > 'Z')
        {
            cout << "Only uppercase letters A-Z are allowed!";
            return 0;
        }

        frequency[tasks[i] - 'A']++;
    }

    cout << "Enter cooling interval: ";
    cin >> cooldown;

    if (cooldown < 0 || cooldown > 1000)
    {
        cout << "Invalid cooling interval!";
        return 0;
    }

    MaxHeap maxHeap;

    // Insert all distinct tasks into the Max Heap.
    for (int i = 0; i < 26; i++)
    {
        if (frequency[i] > 0)
        {
            Task task;

            task.name = 'A' + i;
            task.frequency = frequency[i];

            maxHeap.insert(task);
        }
    }

    CoolingTask cooling[26];
    int coolingCount = 0;

    int time = 0;

    cout << "\nTask schedule:\n";

    while (!maxHeap.isEmpty() || coolingCount > 0)
    {
        // Release tasks whose cooling period is over.
        int i = 0;

        while (i < coolingCount)
        {
            if (cooling[i].readyTime <= time)
            {
                maxHeap.insert(cooling[i].task);

                cooling[i] = cooling[coolingCount - 1];
                coolingCount--;
            }
            else
            {
                i++;
            }
        }

        if (!maxHeap.isEmpty())
        {
            Task current = maxHeap.extractMax();

            cout << current.name << " ";

            current.frequency--;

            // Put the task into cooling if repetitions remain.
            if (current.frequency > 0)
            {
                cooling[coolingCount].task = current;
                cooling[coolingCount].readyTime =
                    time + cooldown + 1;

                coolingCount++;
            }
        }
        else
        {
            cout << "idle ";
        }

        time++;
    }

    cout << "\n\nTotal intervals required: " << time << endl;

    return 0;
}
