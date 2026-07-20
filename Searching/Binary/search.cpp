#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int position = -1;
    
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements in the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the key to be searched: ";
    cin >> key;
    
    int low = 0, high = n-1; 
    int mid;

    while (low <= high){
        mid = low + (high - low)/ 2;
        if (key == arr[mid]){
            position = mid+1;
            break;
        }
        else if(key < arr[mid]){
            high = mid-1;
        }
        else {
            low = mid+1;
        }
    }
    if(position != -1) {
        cout << key << " found at position " << position;
    }
    else {
        cout << key << " not found in the array";
    }

    return 0;
}