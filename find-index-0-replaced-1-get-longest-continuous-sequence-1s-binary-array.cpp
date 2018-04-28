#include<iostream>
using namespace std;

int maxOnesIndex(bool arr[], int n)
{
    int left[n], right[n];
    left[0] = arr[0] ? 1 : 0;
    for(int i = 1; i < n; i++) {
        if(arr[i] == 0) left[i] = 0;
        else {
            left[i] = left[i-1] + 1;
        }
    }
    right[n-1] = right[n-1] ? 1 : 0;
    for(int i = n - 2; i >= 0; i--) {
        if(arr[i] == 0) right[i] = 0;
        else {
            right[i] = right[i+1] + 1;
        }
    }
    int maxCount = -1, maxIndex;
    for(int i = 0; i < n; i++) {
        if(arr[i] == 0) {
            int numOfRightOnes = i == n-1 ? 0 : right[i+1];
            int numOfLeftOnes = i == 0 ? 0 : left[i-1];
            int curCount = numOfLeftOnes + numOfRightOnes;
            if(maxCount < curCount) {
                maxCount = curCount;
                maxIndex = i;
            }
        }
    }
    return maxIndex;
}

// Driver program
int main()
{
	bool arr[] = {1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1};
	int n = sizeof(arr)/sizeof(arr[0]);
	cout << "Index of 0 to be replaced is "
		<< maxOnesIndex(arr, n);
	return 0;
}
