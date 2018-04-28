#include <iostream>
#include <cassert>

using namespace std;

void printSet(bool choices[], int arr[], int n) {
   assert(n >= 0);
   static unsigned subsetNum = 0;
   bool someOneIsChosen = false;
   cout << "SubsetNum = " << ++subsetNum << ":  ";
   for(int i = 0; i < n; i++) {
		if(choices[i]) {
		    someOneIsChosen = true;
			cout << arr[i] << " ";
		}
   }
   if(!someOneIsChosen) {
       cout << "empty set";
   }
   cout << endl;
}


void printSubsets(int curIndex, int arr[], int n, bool choices[]) {
	if(curIndex == n) {
		// we are done with "choices" for all the n elements.
		// Therefore, print the subset so formed.
		printSet(choices, arr, n);
		return;
	}
	// Choice-1: don't select
	choices[curIndex] = false;
	printSubsets(curIndex + 1, arr, n, choices);
	
	// Choice-2: do select
	choices[curIndex] = true;
	printSubsets(curIndex + 1, arr, n, choices);
}


int main() {
	int set[] = {2, 3, 4, 1, 8, 9};
	int n = sizeof(set) / sizeof(set[0]);
	bool choices[n] = {false};
	printSubsets(0, set, n, choices);
	return 0;
}