// C++ program to print length of the largest 
// contiguous array sum
#include<iostream>
#include<climits>
#include <map>
#include <vector>
using namespace std;

int maxSubArraySum(int a[], int size)
{ 
    vector<pair<int, int>> res(size);
    res[0] = make_pair(0, a[0]);
    int maxSum = INT_MIN, maxIndex = -1;
    for(int i = 1; i < size; i++) {
        auto p = res[i-1];
        int extSum = a[i] + p.second;
        if(extSum > a[i]) {
            res[i] = make_pair(p.first, extSum);
        } else {
            res[i] = make_pair(i, a[i]);
        }
    }
    
    for(int i = 0; i < size; i++) {
        if(res[i].second > maxSum) {
            maxSum = res[i].second;
            maxIndex = i;
        }
    }
    
    return maxIndex - res[maxIndex].first + 1;
}

/*Driver program to test maxSubArraySum*/
int main()
{
	int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
	int n = sizeof(a)/sizeof(a[0]);
	cout << maxSubArraySum(a, n);
	return 0;
}
