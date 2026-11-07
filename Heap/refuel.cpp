#include <iostream>
#include <algorithm>
using namespace std;

struct Station
{
    long long position;
    long long fuel;
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

    void insert(long long fuel)
    {
        if (size == 1000)
            return;

        int i = size;
        heap[i] = fuel;
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
        if (size == 0)
            return -1;

        long long result = heap[0];

        heap[0] = heap[size - 1];
        size--;

        int i = 0;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < size && heap[left] > heap[largest])
                largest = left;

            if (right < size && heap[right] > heap[largest])
                largest = right;

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
};

int main()
{
    long long target, startFuel;
    int n;

    cout << "Enter destination distance: ";
    cin >> target;

    if (target <= 0)
    {
        cout << "Destination distance must be positive!" << endl;
        return 0;
    }

    cout << "Enter initial fuel: ";
    cin >> startFuel;

    if (startFuel < 0)
    {
        cout << "Initial fuel cannot be negative!" << endl;
        return 0;
    }

    cout << "Enter number of fuel stations: ";
    cin >> n;

    if (n < 0 || n > 1000)
    {
        cout << "Invalid number of stations!" << endl;
        return 0;
    }

    Station stations[1000];

    cout << "\nEnter position and fuel available at each station:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Station " << i + 1 << ":\n";

        cout << "Position: ";
        cin >> stations[i].position;

        cout << "Fuel: ";
        cin >> stations[i].fuel;

        if (stations[i].position < 0 ||
            stations[i].position >= target ||
            stations[i].fuel < 0)
        {
            cout << "Invalid station details!" << endl;
            return 0;
        }
    }

    // Sort stations according to their positions.
    sort(stations, stations + n,
         [](Station a, Station b)
         {
             return a.position < b.position;
         });

    MaxHeap maxHeap;

    long long currentFuel = startFuel;
    long long previousPosition = 0;

    int stops = 0;

    for (int i = 0; i <= n; i++)
    {
        // Destination is treated as the final checkpoint.
        long long nextPosition;

        if (i == n)
            nextPosition = target;
        else
            nextPosition = stations[i].position;

        long long distance = nextPosition - previousPosition;

        // Refuel from previously passed stations if needed.
        while (currentFuel < distance)
        {
            if (maxHeap.isEmpty())
            {
                cout << "\nDestination cannot be reached." << endl;
                return 0;
            }

            currentFuel += maxHeap.extractMax();
            stops++;
        }

        // Travel to the next checkpoint.
        currentFuel -= distance;
        previousPosition = nextPosition;

        // Add the fuel available at this station.
        if (i < n)
        {
            maxHeap.insert(stations[i].fuel);
        }
    }

    cout << "\n========== RESULT ==========\n";

    cout << "Minimum refueling stops: " << stops << endl;
    cout << "Remaining fuel: " << currentFuel << endl;

    return 0;
}