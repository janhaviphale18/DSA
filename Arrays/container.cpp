#include <iostream>
using namespace std;

int main()
{
    int size;
    int height[100];
    int maximumArea = 0;

    cout << "Enter number of buildings: ";
    cin >> size;

    cout << "Enter building heights: ";

    for (int index = 0; index < size; index++)
    {
        cin >> height[index];
    }

    for (int left = 0; left < size - 1; left++)
    {
        for (int right = left + 1; right < size; right++)
        {
            int minimumHeight;

            if (height[left] < height[right])
            {
                minimumHeight = height[left];
            }
            else
            {
                minimumHeight = height[right];
            }

            int width = right - left;
            int area = minimumHeight * width;

            if (area > maximumArea)
            {
                maximumArea = area;
            }
        }
    }

    cout << "Maximum water stored: " << maximumArea << endl;

    return 0;
}