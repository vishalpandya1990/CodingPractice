#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

/************************ Disjoint-set data structures ****************/

struct setElement {
    int value;
    struct disjointSet *setPtr;
    struct setElement *next;
    setElement(int x) {setPtr = NULL; next = NULL; value = x;}
};

struct disjointSet {
  struct setElement *head, *tail;
  size_t setSize;
  disjointSet() {head = tail = NULL; setSize = 0;}
};

typedef disjointSet* SetPtr;
typedef setElement*  ElementPtr;

map<int, ElementPtr> valueToPointerHashMap;

/*************************** Function prototypes ********************/

void addToHash(map<int, ElementPtr> &hashMap, ElementPtr ePtr);
void removeFromHash(map<int, ElementPtr> &hashMap, ElementPtr ePtr);
void removeFromHash(map<int, ElementPtr> &hashMap, int value);

void destroySet(SetPtr ptr);
void updateSetPtr(SetPtr from, SetPtr to);
SetPtr unionSet(SetPtr s1, SetPtr s2);
SetPtr makeSet(ElementPtr ePtr);
SetPtr makeSet(int eValue);
SetPtr findSet(ElementPtr ePtr);
SetPtr findSet(int value);
void printSetElements(SetPtr sPtr);

/***************************** Implementation *************************/

void addToHash(map<int, ElementPtr> &hashMap, ElementPtr ePtr) {
    //assert(hashMap); // Check this
    assert(ePtr);
    int value = ePtr->value;
    assert(hashMap.find(value) == hashMap.end()); // we will not create duplicate element struct for same key (value)
    hashMap[value] = ePtr;
}

void removeFromHash(map<int, ElementPtr> &hashMap, ElementPtr ePtr) {
   //assert(hashMap);
   assert(ePtr);
   //assert(hashMap.find(ePtr->value) != hashMap.end());
   hashMap.erase(ePtr->value);
}

void removeFromHash(map<int, ElementPtr> &hashMap, int value) {
   //assert(hashMap);
   //assert(hashMap.find(value) != hashMap.end());
   hashMap.erase(value);
}

void destroySet(SetPtr ptr) {
    assert(ptr);
    ptr ->head = ptr ->tail = NULL;
    //ptr->setSize = 0;
    free(ptr);
}

void updateSetPtr(SetPtr from, SetPtr to) {
   assert(from && to);
   ElementPtr cur = from->head;
   while(cur) {
      cur->setPtr = to;
      cur = cur->next;
   }
}
SetPtr unionSet(SetPtr s1, SetPtr s2) {
    assert(s1 && s2);
    size_t size1 = s1->setSize;
    size_t size2 = s2->setSize;
    assert(size1 && size2);    // size_t is an unsigned data type
    SetPtr finalSetPtr = NULL;
    if(size1 < size2) {
        updateSetPtr(s1, s2);       // should be called first before appending since update() runs till null-end is reached
        s2->tail->next  = s1->head; // Until the completion of this method, from-set will be in inconsistent set temporarily
        s2->tail        = s1->tail; // Since it's a single threaded application, this is okay. Otherwise, we would need synchronization.
        s2->setSize    += size1;
        destroySet(s1);
        finalSetPtr = s2;
    } else {
        updateSetPtr(s2, s1);
        s1->tail->next  = s2->head;
        s1->tail        = s2->tail;
        s1->setSize    += size2;
        destroySet(s2);
        finalSetPtr = s1;
    }
    return finalSetPtr;
}

SetPtr makeSet(ElementPtr ePtr) {
   assert(ePtr);
   SetPtr sPtr = new disjointSet();
   assert(sPtr);
   sPtr->head = sPtr->tail = ePtr;
   sPtr->setSize = 1;
   ePtr->setPtr = sPtr;
   ePtr->next = NULL; // re-doing
   return sPtr;
}

SetPtr makeSet(int eValue) {
   ElementPtr ePtr = new setElement(eValue);
   assert(ePtr);
   addToHash(valueToPointerHashMap, ePtr);
   SetPtr sPtr = new disjointSet();
   assert(sPtr);
   sPtr->head = sPtr->tail = ePtr;
   sPtr->setSize = 1;
   ePtr->setPtr = sPtr;
   ePtr->next = NULL; // re-doing
   return sPtr;
}

SetPtr findSet(ElementPtr ePtr) {
   assert(ePtr);
   assert(ePtr->setPtr); //not sure whether needed
   return ePtr->setPtr;
}

SetPtr findSet(int value) {
   map<int, ElementPtr>::iterator it;
   it = valueToPointerHashMap.find(value);
   if(it != valueToPointerHashMap.end()) {
      ElementPtr ePtr = valueToPointerHashMap[value]; // it->second
      assert(ePtr);
      assert(ePtr->setPtr); //not sure whether needed
      return ePtr->setPtr;
   }
   return NULL;
}

void printSetElements(SetPtr sPtr) {
   if(!sPtr ) {
      cout << "Null set\n";
      return;
   }
   size_t sz = sPtr->setSize, i;
   if(!sz) {
      cout << "Empty set\n";
      return;
   }
   ElementPtr curElementPtr = sPtr->head;
   assert(curElementPtr);
   for(i = 0; i < sz; i++) {
       assert(curElementPtr);
       cout << curElementPtr->value << " ";
       curElementPtr = curElementPtr->next;
   }
   cout << endl;
   assert(curElementPtr == NULL); //to ensure that setSize and set-element's list are in sync about the element count
}

/******************************** Main ************************************/

int main() {
   int input1[] = {2, 6, 9, 21, 13};
   int n1 = sizeof(input1) / sizeof(input1[0]);

   int i;
   SetPtr s[n1] = {NULL};
   for(i = 0; i < n1; i++) {
      s[i] = makeSet(input1[i]);
   }
   SetPtr s13 = findSet(input1[n1-1]);
   printSetElements(s13);

   SetPtr s0 = findSet(input1[0]);
   printSetElements(s0);

   unionSet(s[1], s[2]);
   unionSet(s[1], s[3]);
   unionSet(s[1], s[0]);

   s13 = findSet(input1[n1-1]);
   printSetElements(s13);

   s0 = findSet(input1[0]);
   printSetElements(s0);

   return 0;
}
