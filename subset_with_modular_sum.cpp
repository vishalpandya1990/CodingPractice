// C++ program to check if there is a subset
// with sum divisible by m.
#include <bits/stdc++.h>
using namespace std;

// Returns true if there is a subset
// of arr[] with sum divisible by m
bool modularSum(int arr[], int n, int m)
{
    if(n == 1)
        return arr[0]%m == 0;
        
    bool dp[m] = {false};
    // dp[j] = true if there is a subset with modular sum j; false otherwise
    
    for(int i = 0; i < n; i++) { // pick one element at a time
        int r = arr[i] % m;
        bool temp[m];
        memcpy(temp, dp, sizeof(dp));
        for(int j = 0; j < m; j++) {
            if(dp[j]) {
                temp[(j+arr[i])%m] = true;
            }
        }
        memcpy(dp, temp, sizeof(dp));
        dp[r] = true;
    }
    return dp[0];
}

// Driver code
int main()
{
	int arr[] = {1, 7};
	int n = sizeof(arr)/sizeof(arr[0]);
	int m = 5;

	modularSum(arr, n, m) ? cout << "YES\n" :
							cout << "NO\n";

	return 0;
}
