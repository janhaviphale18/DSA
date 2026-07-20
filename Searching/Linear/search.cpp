#include <iostream>
using namespace std;
int main()
{
int n, arr[100], key;
int  position = -1;

cout << "Enter the number of elements in the array: ";
cin >> n;

cout << "Enter the elements of the array: ";
for (int i = 0; i < n; i++) {
    cin >> arr[i];
}

cout << "Enter the key to be searched: ";
cin >> key;
for( int i = 0; i < n; i++) {
    if (arr[i] == key) {
        position = i+1;
        break;
    }
}

if (position != -1) {
    cout << key << " is found at position " << position;
}
else {
    cout << key << " is not found in the array";
}

return 0;
}
