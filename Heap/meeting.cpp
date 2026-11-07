#include <iostream>
#include <algorithm>
using namespace std;

struct Meeting
{
    int start;
    int end;
};

class MinHeap
{
    int heap[1000];
    int size;

public:
    MinHeap()
    {
        size = 0;
    }

    void insert(int value)
    {
        if (size == 1000)
            return;

        int i = size;
        heap[i] = value;
        size++;

        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[parent] <= heap[i])
                break;

            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    int extractMin()
    {
        if (size == 0)
            return -1;

        int result = heap[0];

        heap[0] = heap[size - 1];
        size--;

        int i = 0;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && heap[left] < heap[smallest])
                smallest = left;

            if (right < size && heap[right] < heap[smallest])
                smallest = right;

            if (smallest == i)
                break;

            swap(heap[i], heap[smallest]);
            i = smallest;
        }

        return result;
    }

    int getMin()
    {
        if (size == 0)
            return -1;

        return heap[0];
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

int main()
{
    int n;

    cout << "Enter number of meetings: ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of meetings!" << endl;
        return 0;
    }

    Meeting meetings[1000];

    cout << "\nEnter starting and ending time of each meeting:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Meeting " << i + 1 << ":\n";

        cout << "Start time: ";
        cin >> meetings[i].start;

        cout << "End time: ";
        cin >> meetings[i].end;

        if (meetings[i].start < 0 ||
            meetings[i].end <= meetings[i].start)
        {
            cout << "Invalid meeting interval!" << endl;
            return 0;
        }
    }

    // Sort meetings according to starting time.
    sort(meetings, meetings + n,
         [](Meeting a, Meeting b)
         {
             return a.start < b.start;
         });

    MinHeap minHeap;

    int minimumRooms = 0;

    for (int i = 0; i < n; i++)
    {
        // Release a room if its meeting has ended.
        while (!minHeap.isEmpty() &&
               minHeap.getMin() <= meetings[i].start)
        {
            minHeap.extractMin();
        }

        // Allocate a room for the current meeting.
        minHeap.insert(meetings[i].end);

        // Track maximum rooms occupied simultaneously.
        if (minHeap.getSize() > minimumRooms)
        {
            minimumRooms = minHeap.getSize();
        }
    }

    cout << "\n========== RESULT ==========\n";

    cout << "Minimum meeting rooms required: "
         << minimumRooms << endl;

    return 0;
}