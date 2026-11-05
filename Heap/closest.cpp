#include <iostream>
using namespace std;

struct Point
{
    long long x;
    long long y;
    long double distance;
};

class KClosestPoints
{
private:
    Point points[100];
    Point heap[100];

    int size;
    int heapSize;
    int k;

    // Compare points by distance
    bool isFarther(Point a, Point b)
    {
        if (a.distance != b.distance)
        {
            return a.distance > b.distance;
        }

        if (a.x != b.x)
        {
            return a.x > b.x;
        }

        return a.y > b.y;
    }

    // Check whether a point is closer
    bool isCloser(Point a, Point b)
    {
        if (a.distance != b.distance)
        {
            return a.distance < b.distance;
        }

        if (a.x != b.x)
        {
            return a.x < b.x;
        }

        return a.y < b.y;
    }

    // Swap two points
    void swapPoint(Point &a, Point &b)
    {
        Point temp = a;
        a = b;
        b = temp;
    }

    // Restore Max Heap property upwards
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (!isFarther(heap[index], heap[parent]))
            {
                break;
            }

            swapPoint(heap[index], heap[parent]);

            index = parent;
        }
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
                isFarther(heap[left], heap[largest]))
            {
                largest = left;
            }

            if (right < heapSize &&
                isFarther(heap[right], heap[largest]))
            {
                largest = right;
            }

            if (largest == index)
            {
                break;
            }

            swapPoint(heap[index], heap[largest]);

            index = largest;
        }
    }

    // Insert point into Max Heap
    void insert(Point p)
    {
        heap[heapSize] = p;

        heapifyUp(heapSize);

        heapSize++;
    }

    // Replace the farthest point
    void replaceRoot(Point p)
    {
        heap[0] = p;

        heapifyDown(0);
    }

    // Sort selected points by increasing distance
    void sortResults(Point result[])
    {
        for (int i = 0; i < heapSize - 1; i++)
        {
            for (int j = i + 1; j < heapSize; j++)
            {
                if (isCloser(result[j], result[i]))
                {
                    swapPoint(result[i], result[j]);
                }
            }
        }
    }

public:
    // Accept point coordinates
    bool input()
    {
        cout << "Enter number of points (1-100): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > 100)
        {
            cout << "Invalid number of points!" << endl;
            return false;
        }

        cout << "Enter X and Y coordinates:" << endl;

        for (int i = 0; i < size; i++)
        {
            cout << "Point " << i + 1 << ": ";

            cin >> points[i].x >> points[i].y;

            if (cin.fail())
            {
                cout << "Invalid coordinates!" << endl;
                return false;
            }

            long double x = points[i].x;
            long double y = points[i].y;

            points[i].distance = x * x + y * y;
        }

        cout << "Enter the value of K: ";
        cin >> k;

        if (cin.fail() || k < 1 || k > size)
        {
            cout << "Invalid value of K!" << endl;
            return false;
        }

        return true;
    }

    // Find K closest points
    void findClosestPoints()
    {
        heapSize = 0;

        // Process every point
        for (int i = 0; i < size; i++)
        {
            if (heapSize < k)
            {
                insert(points[i]);
            }
            else if (isCloser(points[i], heap[0]))
            {
                replaceRoot(points[i]);
            }
        }

        // Display final Max Heap
        cout << "\nFinal Max Heap:" << endl;

        for (int i = 0; i < heapSize; i++)
        {
            cout << "(" << heap[i].x
                 << ", " << heap[i].y << ") ";

            cout << "Distance Squared: "
                 << heap[i].distance << endl;
        }

        // Copy selected points
        Point result[100];

        for (int i = 0; i < heapSize; i++)
        {
            result[i] = heap[i];
        }

        // Arrange selected points by increasing distance
        sortResults(result);

        cout << "\n" << k
             << " Closest Points to Origin:" << endl;

        for (int i = 0; i < heapSize; i++)
        {
            cout << "(" << result[i].x
                 << ", " << result[i].y << ")";

            cout << " - Distance Squared: "
                 << result[i].distance << endl;
        }
    }
};

int main()
{
    KClosestPoints obj;

    if (!obj.input())
    {
        return 0;
    }

    obj.findClosestPoints();

    return 0;
}
