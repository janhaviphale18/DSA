
#include <iostream>
using namespace std;

class MinHeap
{
    int arr[100];
    int size;

public:

    MinHeap()
    {
        size = 0;
    }

    // Initialize Min Heap
    void initialize(int elements[], int n)
    {
        size = n;

        for (int i = 0; i < n; i++)
        {
            arr[i] = elements[i];
        }
    }

    // Display Heap
    void display()
    {
        cout << "Min Heap Elements: ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    // Display minimum element
    void getMin()
    {
        if (size == 0)
        {
            cout << "Heap is empty." << endl;
        }
        else
        {
            cout << "Minimum Element: " << arr[0] << endl;
        }
    }
};

int main()
{
    MinHeap h;

    int elements[] = {10, 20, 30, 40, 50, 60, 70};
    int n = 7;

    h.initialize(elements, n);

    cout << "Min Heap Implementation\n\n";

    h.display();

    h.getMin();

    return 0;
}
