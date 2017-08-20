#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//Use proper macros so that both min heap and max heap are handled.
#define UNDEFINED 1000001   //remove it
#define ERROR -1 //use exceptions handling

typedef bool (*compareFn) (int, int);

bool smaller (int a, int b) {
    return a < b;
}

bool bigger (int a, int b) {
    return a > b;
}

class Heap {
  protected:
      vector<int> elementStore;
      int size;
      int capacity;
      compareFn comparator;
      string heapName;
      void heapify(int);
      void exchange (int&, int&);
      int getLeftChild(int);
      int getRightChild(int);
      int getParent(int);
      bool isValidIndex(int);
  public:
      Heap(compareFn f);
      Heap(int c, compareFn f);
      Heap(int c, compareFn f, vector<int> &a);
      Heap(int c, compareFn f, int* a, int n);
      int getTop(void);
      int getSize(void);
      int getCapacity(void);
      bool isEmpty(void);
      bool isFull(void);
      int deleteTop(void);
      int insertKey(int);
      int changeKey(int, int);
      void printElementStore(void);
      string getHeapName(void);
      void setHeapName(string);
};

Heap::Heap(compareFn f) {
    capacity = UNDEFINED;
    size = 0;
    comparator = f;
    heapName = "<NotDefined>";
}


Heap::Heap(int c, compareFn f) {
    assert(c >= 0);
    capacity = c;
    elementStore.resize(capacity);
    assert(c == elementStore.size());
    size = 0;
    comparator = f;
    heapName = "<NotDefined>";
}

Heap::Heap(int c, compareFn f, vector<int> &a) {
    //Assuming c >= a.size() 
    assert(c >= 0);
    capacity = c;
    size = a.size();
    comparator = f;
    elementStore = a;
    heapName = "<NotDefined>";
    assert(a.size() == elementStore.size());
    if(size)
       heapify(0);
}

Heap::Heap(int c, compareFn f, int *a, int n) {
    //Assuming c >= n
    assert(c >= 0);
    capacity = c;
    size = n;
    comparator = f;
    heapName = "<NotDefined>";
    for(int i = 0; i < n; i++)
      elementStore.push_back(a[i]);
    assert(c == elementStore.size());
    if(size)
       heapify(0);
}

string Heap::getHeapName(void) {
    return heapName;
}

void Heap::setHeapName(string name) {
    heapName = name;
}

int Heap::getLeftChild(int index) {
    if(isValidIndex(index)) {
        return (index << 1) + 1;
    }
    return -1;
}

int Heap::getRightChild(int index) {
    if(isValidIndex(index)) {
        return (index << 1) + 2;
    }
    return -1;
}

int Heap::getParent(int index){
    if(index && isValidIndex(index)) {
        return ((index - 1) >> 1);
    }
    return -1;
}

int Heap::getSize(void) {
    return size;
}

int Heap::getCapacity(void) {
    return capacity;
}
bool Heap::isValidIndex(int index) {
    if((index >= size) || (index < 0)) 
       return false;
    else
       return true;
}

bool Heap::isEmpty(void) {
    return size == 0;
}

bool Heap::isFull(void) {
    return size == capacity;
}

void Heap::exchange(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void Heap::heapify(int curIndex) {
    int left = getLeftChild(curIndex);
    int right = getRightChild(curIndex);
    int better = curIndex;
    if(isValidIndex(left) && comparator(elementStore[left], elementStore[better]))
       better = left;
    if(isValidIndex(right) && comparator(elementStore[right], elementStore[better]))
       better = right;
    
    if(better != curIndex) {
        exchange(elementStore[better], elementStore[curIndex]);
        heapify(better);
    }
}

int Heap::insertKey(int key) {
    if(isFull()) return 1; //1 for error - 0 for success
    elementStore.push_back(key);
    size++; //add at newly created last position
    int curIndex = size - 1;
    int parent = getParent(curIndex);
    while((curIndex > 0) && (comparator(elementStore[curIndex], elementStore[parent]))) {
        exchange(elementStore[parent], elementStore[curIndex]);
        curIndex = parent;
        parent = getParent(curIndex);
    }
    return 0;
}

//only considers changes to make existing values "better"
int Heap::changeKey(int index, int key) {
    if(!isValidIndex(index)) return 1;
    if(comparator(elementStore[index], key)) return 1;
    elementStore[index] = key;
    int curIndex = index;
    int parent = getParent(curIndex);
    while((curIndex > 0) && (comparator(elementStore[parent], elementStore[curIndex]))) {
        exchange(elementStore[parent], elementStore[curIndex]);
        curIndex = parent;
        parent = getParent(curIndex);
    }
    return 0;
}

int Heap::getTop(void) {
    if(isEmpty()) return UNDEFINED;
    return elementStore[0];
}

int Heap::deleteTop(void) {
    if(isEmpty()) return 1; //1 for error - 0 for success
    int curTop = getTop();
    elementStore[0] = elementStore[size - 1]; //can't use changeKey since we may be "worsening" the top value
    size--;
    elementStore.resize(size);
    heapify(0);
    return curTop;
}

void Heap::printElementStore(void) {
     if(isEmpty()) {
         cout << heapName << ": " << "It is empty" << endl;
         return;
     }
     cout << heapName << ": ";
     for(int i = 0; i < size; i++){
         cout << elementStore[i] << " ";
     }
     cout << endl;
 }


class MinHeap : public Heap {
    public:
      MinHeap() : Heap(smaller) {}
      MinHeap(int c) : Heap(c, smaller) {}
      MinHeap(int c, vector<int> &a) : Heap(c, smaller, a) {}
      MinHeap(int c, int* a, int n) : Heap(c, smaller, a, n) {}
};

class MaxHeap : public Heap {
    public:
      MaxHeap() : Heap(bigger) {}
      MaxHeap(int c) : Heap(c, bigger) {}
      MaxHeap(int c, vector<int> &a) : Heap(c, bigger, a) {}
      MaxHeap(int c, int* a, int n) : Heap(c, bigger, a, n) {}
};

int main() {
    cout << "Using min heap first\n";
    MinHeap minh;
    minh.insertKey(4);
    cout << "Added 4\n";
    minh.insertKey(2);
    cout << "Added 2\n";
    cout << minh.getTop() << endl;
    minh.deleteTop();
    cout << "performed deleteTop\n";
    cout << minh.getTop() << endl;
    minh.insertKey(5);
    cout << "added 5\n";
    minh.insertKey(7);
    cout << "added 7\n";
    minh.insertKey(3);
    cout << "added 3\n";
    cout << minh.getTop() << endl;
    
    cout << "Now using max heap\n";
    
    MaxHeap maxh;
    maxh.insertKey(4);
    cout << "added 4\n";
    maxh.insertKey(2);
    cout << "added 2\n";
    cout << maxh.getTop() << endl;
    maxh.deleteTop();
    cout << "performed deleteTop\n";
    cout << maxh.getTop() << endl;
    maxh.insertKey(5);
    cout << "added 5\n";
    maxh.insertKey(7);
    cout << "added 7\n";
    maxh.insertKey(3);
    cout << "added 3\n";
    cout << maxh.getTop() << endl;
	return 0;
}
