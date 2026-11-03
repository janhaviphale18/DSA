
#include <iostream>
using namespace std;

class MaxHeap
{
    int arr[100];
    int size;

public:

    MaxHeap()
    {
        size = 0;
    }

    // Initialize Max Heap
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
        cout << "Max Heap Elements: ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    // Display maximum element
    void getMax()
    {
        if (size == 0)
        {
            cout << "Heap is empty." << endl;
        }
        else
        {
            cout << "Maximum Element: " << arr[0] << endl;
        }
    }
};

int main()
{
    MaxHeap h;

    int elements[] = {70, 50, 60, 20, 30, 40, 10};
    int n = 7;

    h.initialize(elements, n);

    cout << "Max Heap Implementation\n\n";

    h.display();

    h.getMax();

    return 0;
}
