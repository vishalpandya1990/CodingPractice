#include <iostream>
#include <queue>

using namespace std;

int getMedian(int newElem, priority_queue<int>& left, priority_queue<int, vector<int>, greater<int>>& right) {
    if(left.empty()) {
        left.push(newElem);
        return newElem;
    }
    if(right.empty()) {
        right.push(newElem);
        return (left.top() + right.top())/2;
    }
    //cout << "Before: ne = " << newElem << " ls=" << left.size() << " rs=" << right.size() << " ";
    //cout << "lt=" << left.top() << " rt=" << right.top() << endl;
    size_t leftSize;
    size_t rightSize;
    int result = -1;
    int leftTop = left.top();
    int rightTop = right.top();
    if(newElem <= leftTop) {
        left.push(newElem);
        leftSize = left.size();
        rightSize = right.size();
        if(leftSize == rightSize + 2) {
            int temp = left.top();
            left.pop();
            right.push(temp);
            result = (left.top() + right.top())/2;
        } else if(leftSize == rightSize + 1) {
            result = left.top();
        } else if(leftSize == rightSize) {
            result = (left.top() + right.top())/2;
        }
    } else {
        right.push(newElem);
        leftSize = left.size();
        rightSize = right.size();
        if(leftSize == rightSize - 1) {
            int temp = right.top();
            right.pop();
            left.push(temp);
            result = left.top();
        } else if(leftSize == rightSize) {
            result = (left.top() + right.top())/2;
        }
    }
    //cout << "After: " << newElem << " ls=" << left.size() << " rs=" << right.size() << " ";
    //cout << "lt=" << left.top() << " rt=" << right.top() <<  " res=" << result << endl;
    return result;
}

void printMedian(int A[], int size)
{
	int m = 0;
	priority_queue<int> left; // max heap
	priority_queue<int, vector<int>, greater<int>>right; // min heap

	for(int i = 0; i < size; i++)
	{
		m = getMedian(A[i], left, right);
		cout << m << endl;
	}
}
// Driver code
int main()
{
	int A[] = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};
	int size = sizeof(A) / sizeof(A[0]);

	// In lieu of A, we can also use data read from a stream
	printMedian(A, size);

	return 0;
}
