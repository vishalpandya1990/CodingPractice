#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int seatAvailability(int a[], int n) {
	if(n == 1 ) {
		if(a[0]) return -1; //no vacant seat
		else return 0; // returning index of chosen location
  }
	int left[n], right[n];
	left[0] = a[0] ? 0 : 1; right[n-1] = a[n-1] ? 0 : 1;
	for(int i = 1; i < n; i++) {
		if(a[i] == 0) left[i] = left[i-1] + 1;
		else
			left[i] = 0;
  }
  for(int i = n-2; i >= 0; i--) {
	  if(a[i] == 0) right[i] = right[i+1] + 1;
    else
	    right[i] = 0;

  }
  int maxNonZeroDist = INT_MIN, curDist, maxIndex = -1;
  for(int i = 0; i < n; i++) {
      if(a[i]) continue;
      int curDist = min(left[i], right[i]);
      if(curDist  > maxNonZeroDist) {
		    maxNonZeroDist = curDist;
		    maxIndex = i;
    }

  }
  return maxIndex;
}


int main() {
  int a[] = {0,1};
  cout << seatAvailability(a, 2) << endl;
  return 0;
}
