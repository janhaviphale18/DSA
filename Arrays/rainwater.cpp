#include <iostream>
using namespace std;

int main()
{
    int size;
    int height[100];
    int leftMax[100];
    int rightMax[100];
    int totalWater = 0;

    cout << "Enter number of buildings: ";
    cin >> size;

    cout << "Enter building heights: ";

    for (int index = 0; index < size; index++)
    {
        cin >> height[index];
    }

    leftMax[0] = height[0];

    for (int index = 1; index < size; index++)
    {
        if (height[index] > leftMax[index - 1])
        {
            leftMax[index] = height[index];
        }
        else
        {
            leftMax[index] = leftMax[index - 1];
        }
    }

    rightMax[size - 1] = height[size - 1];

    for (int index = size - 2; index >= 0; index--)
    {
        if (height[index] > rightMax[index + 1])
        {
            rightMax[index] = height[index];
        }
        else
        {
            rightMax[index] = rightMax[index + 1];
        }
    }

    for (int index = 0; index < size; index++)
    {
        int minimumHeight;

        if (leftMax[index] < rightMax[index])
        {
            minimumHeight = leftMax[index];
        }
        else
        {
            minimumHeight = rightMax[index];
        }

        totalWater = totalWater + (minimumHeight - height[index]);
    }

    cout << "Total trapped rainwater: "
         << totalWater << endl;

    return 0;
}