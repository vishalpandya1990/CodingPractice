#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int>&v, int n) {
    int dec[n] = {0}; //decreasing starting at i-pos
    int asc[n] = {0}; //increasing ending at i-pos
    asc[0] = v[0];
    for(int i = 1; i < n; i++) {
        asc[i] = v[i];
        if(v[i] >= v[i-1]) asc[i] += asc[i-1];
    }
    dec[n-1] = v[n-1];
    for(int i = n-2; i >= 0; i--) {
        dec[i] = v[i];
        if(v[i] >= v[i+1]) dec[i] += dec[i+1];
    }
    
    int max = -1;
    for(int i = 0; i < n; i++){
        int cur = asc[i] + dec[i] - v[i];
        if(cur > max) max = cur;
    }
    return max;
}

int main()
{
	int arr[] = {5, 3, 9, 2, 7, 6, 4};
	
	int n = sizeof(arr) / sizeof(arr[0]);
	vector<int> v(n);
	for(int i = 0; i < n; i++)
	    v[i] = arr[i];
	cout << "Maximum Sum = "
		<< solve(v, n);
	return 0;	 
} 
