#include <iostream>
using namespace std;

class HeapValidator
{
    int heap[1000];
    int size;

public:

    HeapValidator()
    {
        size = 0;
    }

    void input()
    {
        cout << "Enter number of elements: ";
        cin >> size;

        if (size < 1 || size > 1000)
        {
            cout << "Invalid number of elements!" << endl;
            size = 0;
            return;
        }

        cout << "Enter array elements:\n";

        for (int i = 0; i < size; i++)
        {
            cin >> heap[i];
        }
    }

    bool isMinHeap()
    {
        bool valid = true;

        cout << "\nMin Heap Validation:\n";

        // Check every parent with its children.
        for (int i = 0; i < size; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[i] > heap[left])
            {
                cout << "Violation: Parent "
                     << heap[i] << " is greater than left child "
                     << heap[left] << endl;

                valid = false;
            }

            if (right < size && heap[i] > heap[right])
            {
                cout << "Violation: Parent "
                     << heap[i] << " is greater than right child "
                     << heap[right] << endl;

                valid = false;
            }
        }

        return valid;
    }

    bool isMaxHeap()
    {
        bool valid = true;

        cout << "\nMax Heap Validation:\n";

        // Check every parent with its children.
        for (int i = 0; i < size; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[i] < heap[left])
            {
                cout << "Violation: Parent "
                     << heap[i] << " is smaller than left child "
                     << heap[left] << endl;

                valid = false;
            }

            if (right < size && heap[i] < heap[right])
            {
                cout << "Violation: Parent "
                     << heap[i] << " is smaller than right child "
                     << heap[right] << endl;

                valid = false;
            }
        }

        return valid;
    }

    void validate()
    {
        bool minValid = isMinHeap();
        bool maxValid = isMaxHeap();

        cout << "\n========== VALIDATION RESULT ==========\n";

        if (minValid)
            cout << "Valid Min Heap: YES" << endl;
        else
            cout << "Valid Min Heap: NO" << endl;

        if (maxValid)
            cout << "Valid Max Heap: YES" << endl;
        else
            cout << "Valid Max Heap: NO" << endl;

        if (minValid && maxValid)
        {
            cout << "The array satisfies both heap properties."
                 << endl;
        }
    }
};

int main()
{
    HeapValidator h;

    h.input();

    h.validate();

    return 0;
}