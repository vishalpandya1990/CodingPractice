#include<iostream>
#include <queue>


using namespace std;

void printArray(int arr[], int size)
{
for (int i=0; i < size; i++)
	cout << arr[i] << " ";
cout << endl;
}

void sortK(int a[], int b[], int n, int k) {
    priority_queue<int, vector<int>, greater<int>> minh;
    for(int i = 0; i < k; i++) {
        minh.push(a[i]);
    }
    int idx = 0;
    for(int i = k; i < n; i++) {
        a[idx++] = minh.top();
        minh.pop();
        minh.push(a[i]);
    }
    
    while(!minh.empty()) {
        a[idx++] = minh.top();
        minh.pop();
    }
}

int main()
{
	int k = 3;
	int arr[] = {2, 6, 3, 12, 56, 8};
	int n = sizeof(arr)/sizeof(arr[0]);
	int b[n];
	printArray (arr, n);
	sortK(arr, b, n, k);
	cout << "Following is sorted array\n";
	printArray (arr, n);

	return 0;
}
