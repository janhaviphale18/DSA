#include <iostream>
using namespace std;

struct Element
{
    int value;
    int row;
    int col;
};

class KthMatrix
{
private:
    int matrix[10][10];
    int rows, cols;

    Element heap[100];
    int heapSize;

    // Swap two heap elements
    void swapElement(Element &a, Element &b)
    {
        Element temp = a;
        a = b;
        b = temp;
    }

    // Restore Min Heap property upwards
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[index].value >= heap[parent].value)
            {
                break;
            }

            swapElement(heap[index], heap[parent]);
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
                heap[left].value < heap[smallest].value)
            {
                smallest = left;
            }

            if (right < heapSize &&
                heap[right].value < heap[smallest].value)
            {
                smallest = right;
            }

            if (smallest == index)
            {
                break;
            }

            swapElement(heap[index], heap[smallest]);
            index = smallest;
        }
    }

    // Insert an element into Min Heap
    void insert(Element e)
    {
        if (heapSize == 100)
        {
            return;
        }

        heap[heapSize] = e;
        heapifyUp(heapSize);
        heapSize++;
    }

    // Remove minimum element
    Element extractMin()
    {
        Element minimum = heap[0];

        heap[0] = heap[heapSize - 1];
        heapSize--;

        if (heapSize > 0)
        {
            heapifyDown(0);
        }

        return minimum;
    }

    // Validate matrix sorting
    bool isSorted()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                if (matrix[i][j] < matrix[i][j - 1])
                {
                    return false;
                }
            }
        }

        for (int j = 0; j < cols; j++)
        {
            for (int i = 1; i < rows; i++)
            {
                if (matrix[i][j] < matrix[i - 1][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

public:
    // Accept matrix input
    bool input()
    {
        cout << "Enter number of rows (1-10): ";
        cin >> rows;

        cout << "Enter number of columns (1-10): ";
        cin >> cols;

        if (cin.fail() || rows < 1 || rows > 10 ||
            cols < 1 || cols > 10)
        {
            cout << "Invalid matrix dimensions!" << endl;
            return false;
        }

        cout << "Enter matrix elements:" << endl;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cin >> matrix[i][j];

                if (cin.fail())
                {
                    cout << "Invalid matrix element!" << endl;
                    return false;
                }
            }
        }

        if (!isSorted())
        {
            cout << "Matrix is not sorted!" << endl;
            return false;
        }

        return true;
    }

    // Find Kth smallest element
    void findKthSmallest(int k)
    {
        int total = rows * cols;

        if (k < 1 || k > total)
        {
            cout << "Invalid value of K!" << endl;
            return;
        }

        heapSize = 0;

        // Insert first element of every row
        for (int i = 0; i < rows; i++)
        {
            Element e;

            e.value = matrix[i][0];
            e.row = i;
            e.col = 0;

            insert(e);
        }

        cout << "\nExtracted Elements: ";

        int result = 0;

        for (int i = 1; i <= k; i++)
        {
            Element current = extractMin();

            result = current.value;

            cout << result << " ";

            // Insert next element from the same row
            int nextCol = current.col + 1;

            if (nextCol < cols)
            {
                Element next;

                next.value = matrix[current.row][nextCol];
                next.row = current.row;
                next.col = nextCol;

                insert(next);
            }
        }

        cout << "\n\nKth Smallest Element: "
             << result << endl;
    }
};

int main()
{
    KthMatrix obj;

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

    obj.findKthSmallest(k);

    return 0;
}
