#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define EXTRACT_MIN -1 //an invalid or non-occurring integer

/********************* Disjoint-set data structures *******************/

typedef enum _rootIdType {
    DESTROYED = -2,
    EMPTY,
    NORMAL
} rootIdType;


typedef struct _kSet {
    int rootId;
    int setSize;
} kSet;

typedef struct _setElement {
    int parent; // parent >= 0 for non-root; parent = -(setId) for root
} setElement;



/************************ Function prototypes **********************/

void initializeSets(kSet s[], int setCount);
void makeEmptySet(kSet s[], int setCount, int setId);
void destroyEmptySet(kSet s[], int setCount, int setId);
void addElementToSet(setElement e[], kSet s[], int eCount, int setCount, int setId, int eId);
int mergeTwoNonEmptySets(kSet s[], int setCount, setElement e[], int setId1, int setId2);
void unionKset(kSet s[], int setCount, setElement e[], int fromSetId, int toSetId);
int getNextSetId(kSet s[], int setCount, int curSetId);
int getRootIdOfThisElement(setElement e[], int eCount, int eId);
int getSetIdOfThisElement(setElement e[], int eCount, int eId);
void parseInputSequence(int input[], int inLen, kSet s[], setElement e[], int n, int m);
vector<int> off_line_minimum(int input[], int n, int m);
void printResultVector(vector<int> vec);
void printInputArray(int a[], int n);




/**************************** Implementation ************************/

/*
 * add() call will happen only while parsing the input sequence.
 * ToDo: Incremental addition can lead to skewed kSet.
 *       Need to find another way to create kSet for each I-patch in the input sequence.
 */
void addElementToSet(setElement e[], kSet s[], int eCount, int setCount, int setId, int eId) {
    assert(setId >= 1 && setId <= setCount);
    assert(eId >= 0 && eId < eCount);
    int setIndex = setId - 1;
    if(s[setIndex].rootId == EMPTY) {
        s[setIndex].rootId = eId;
        s[setIndex].setSize = 1;
        e[eId].parent = -setId;
    } else {
        s[setIndex].setSize += 1;
        e[eId].parent = s[setIndex].rootId; //path compression while adding
    }
}

void destroyEmptySet(kSet s[], int setCount, int setId) {
    assert(setId >= 1 && setId <= setCount);
    int setIndex = setId - 1;
    assert(s[setIndex].setSize == 0); //this method must NOT be called on non-empty sets
    s[setIndex].rootId = DESTROYED;
    s[setIndex].setSize = 0;
}

void makeEmptySet(kSet s[], int setCount, int setId) {
    assert(setId >= 1 && setId <= setCount);
    int setIndex = setId - 1;
    s[setIndex].setSize = 0;
    s[setIndex].rootId = EMPTY;
}

/*
 * This method does NOT delete or invalidate left out set. It is left to the caller.
 * It returns set-id of final merged set (bigger one).
 * Caller can use the returned set-id to infer what to do with remaining set.
 */
int mergeTwoNonEmptySets(kSet s[], int setCount, setElement e[], int setId1, int setId2) {
    assert(setId1 >= 1 && setId1 <= setCount);
    assert(setId2 >= 1 && setId2 <= setCount);
    int setIndex1 = setId1 - 1, setIndex2 = setId2 - 1;
    int size1 = s[setIndex1].setSize;
    int size2 = s[setIndex2].setSize;
    int finalRootIndex = -1;
    assert((size1 > 0)&& (size2 > 0));
    if(size1 < size2) {               // union by rank
         e[s[setIndex1].rootId].parent = s[setIndex2].rootId;
         s[setIndex2].setSize = size1 + size2;
         finalRootIndex = setIndex2;
    } else  {
         e[s[setIndex2].rootId].parent = s[setIndex1].rootId;
         s[setIndex1].setSize = size1 + size2;
         finalRootIndex = setIndex1;
    }
    return finalRootIndex;
}

//from-set must be non-empty.
void unionKset(kSet s[], int setCount, setElement e[], int fromSetId, int toSetId) {
      assert(fromSetId >= 1 && fromSetId <= setCount);
      assert(toSetId >= 1 && toSetId <= setCount);
      int fromSetIndex = fromSetId - 1;
      int toSetIndex = toSetId - 1;
      assert(s[fromSetIndex].setSize > 0);
      int finalSetIndex;
      if(s[toSetIndex].rootId == EMPTY) {
        s[toSetIndex].setSize = s[fromSetIndex].setSize;
        s[toSetIndex].rootId = s[fromSetIndex].rootId;
        e[s[fromSetIndex].rootId].parent = -toSetId;
        goto destroyFromSet;
      }
      finalSetIndex = mergeTwoNonEmptySets(s, setCount, e, fromSetId, toSetId);
      assert(finalSetIndex >= 0 && finalSetIndex < setCount);
      //make sure things are merged in to-set. So, copy content of final-set in to-set.
      //merge is done for union-by-rank.
      s[toSetIndex].rootId = s[finalSetIndex].rootId;
      s[toSetIndex].setSize = s[finalSetIndex].setSize;
      //Also force-update root element's parent.
      e[s[finalSetIndex].rootId].parent = -toSetId;

destroyFromSet:
      s[fromSetIndex].setSize = 0;
      destroyEmptySet(s, setCount, fromSetId);
      return;
}

int getNextSetId(kSet s[], int setCount, int curSetId) {
   assert(curSetId >= 1 && curSetId <= setCount);
   int curSetIndex = curSetId - 1;
   int i = curSetIndex + 1;
   while(i < setCount) {
      if(s[i].rootId != DESTROYED) {
         return i+1;
      }
      i++;
   }
   assert(curSetId == setCount);
   return -1;

}

int getRootIdOfThisElement(setElement e[], int eCount, int eId) {
   assert((eId >= 0) && (eId < eCount));
   int i = eId;
   while((i >= 0) && (i < eCount) && (e[i].parent >= 0))
      i = e[i].parent;
   assert((i >= 0) && (i < eCount));
   return i;
}

int getSetIdOfThisElement(setElement e[], int eCount, int eId) {
   //eId == eValue for this problem
   int rootId = getRootIdOfThisElement(e, eCount, eId);
   return -(e[rootId].parent);
}

void initializeSets(kSet s[], int setCount) {
   int i;
   for(i = 0; i < setCount; i++) {
       s[i].setSize = 0;
       s[i].rootId = EMPTY;
   }

}

void parseInputSequence(int input[], int inLen, kSet s[], setElement e[], int n, int m) {

   int setIsAlreadyCreated = 0, curSetId = 0, noOfExtractSoFar = 0, noOfIntSoFar = 0, i;
   int visited[n] = {0};
   for(i = 0; i < inLen; i++) {
       assert(noOfExtractSoFar <= noOfIntSoFar); // validating input sequence - part-1
       if(input[i] != EXTRACT_MIN) {
           noOfIntSoFar++;
           visited[input[i]-1]++;            // recording count of an integer in input sequence
           if(setIsAlreadyCreated) {
              addElementToSet(e, s, n, m+1, curSetId, input[i]-1); // minus 1 while taking input
           } else {
             setIsAlreadyCreated = 1;
             curSetId++;
             addElementToSet(e, s, n, m+1, curSetId, input[i]-1); // minus 1 while taking input
           }
        } else {
            noOfExtractSoFar++;
            setIsAlreadyCreated = 0;
            if(input[i-1] == EXTRACT_MIN) { // i > 0 for sure since 1st element can't be extract-min
               curSetId++;
               makeEmptySet(s, m+1, curSetId);
            }
        }
   }

   if(input[inLen-1] == EXTRACT_MIN) {   //ToDo: Check whether it's needed anymore.
      curSetId++;
      makeEmptySet(s, m+1, curSetId);
   }
   for(i = 0; i < n; i++) {
       assert(visited[i] == 1);         // validating input sequence - part-2
   }
   assert(curSetId == m+1); // total of m+1 sets needs to be formed after parsing input
}


/******************** OFF-LINE-MINIMUM method **************************/

vector<int> off_line_minimum(int input[], int n, int m) { // n+m is total number of elements in input[]
   kSet s[m+1];
   setElement e[n];
   vector<int> extract(m);

   initializeSets(s, m+1); //mark all sets as empty

   parseInputSequence(input, n+m, s, e, n, m);

   int i;
   for(i = 0; i < n; i++) {
      int setIdOfThis = getSetIdOfThisElement(e, n, i);
      if(setIdOfThis != m+1) {
        extract[setIdOfThis-1] = i+1; // plus 1 while giving output
        int nextSetId = getNextSetId(s, m+1, setIdOfThis);
        unionKset(s, m+1, e, setIdOfThis, nextSetId);
     }
   }
   return extract;
}

/************************ Utility methods ***************************/

void printResultVector(vector<int> vec) {
   int i, n = vec.size();
   for(i = 0; i < n; i++) {
     cout << vec[i] << " ";
   }
   cout << endl;
}

void printInputArray(int a[], int n) {
   int i;
   for(i = 0; i < n; i++) {
     if(a[i] != EXTRACT_MIN)
        cout << a[i] << " ";
     else
        cout << "E" << " ";
   }
   cout << endl;
}


/***************************** Main **********************************/

int main(void) {

   int input1[] = {5, 2, 6, EXTRACT_MIN, 1, 7, EXTRACT_MIN, EXTRACT_MIN, 4, 8, EXTRACT_MIN, 3, EXTRACT_MIN};
   int inLen1 = sizeof(input1) / sizeof(input1[0]);
   int m1 = 5, n1 = inLen1 - m1; //ToDo: Currently, need to know these before parsing begins
   printInputArray(input1, inLen1);
   printResultVector(off_line_minimum(input1, n1, m1));
   cout << endl;

   int input2[] = {5, 2, 6, EXTRACT_MIN, 8, 7, EXTRACT_MIN, EXTRACT_MIN, 4, EXTRACT_MIN, 3, EXTRACT_MIN, 1};
   int inLen2 = sizeof(input2) / sizeof(input2[0]);
   int m2 = 5, n2 = inLen2 - m2;
   printInputArray(input2, inLen2);
   printResultVector(off_line_minimum(input2, n2, m2));
   cout << endl;

   int input3[] = {2, EXTRACT_MIN, 1, 3, 4, 5,EXTRACT_MIN, EXTRACT_MIN, EXTRACT_MIN, EXTRACT_MIN};
   int inLen3 = sizeof(input3) / sizeof(input3[0]);
   int m3 = 5, n3 = inLen3 - m3;
   printInputArray(input3, inLen3);
   printResultVector(off_line_minimum(input3, n3, m3));
   cout << endl;

   int input4[] = {5, 2, 6, EXTRACT_MIN, 1, 7, EXTRACT_MIN, EXTRACT_MIN, 4, 8, EXTRACT_MIN, 3, EXTRACT_MIN, 9, 10, 11};
   int inLen4 = sizeof(input4) / sizeof(input4[0]);
   int m4 = 5, n4 = inLen4 - m4;
   printInputArray(input4, inLen4);
   printResultVector(off_line_minimum(input4, n4, m4));
   cout << endl;

   return 0;
}
