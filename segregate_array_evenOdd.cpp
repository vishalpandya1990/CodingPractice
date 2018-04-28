#include <iostream>
using namespace std;
void solve(int a[], int n) { 
 if(n <= 1) return;
 int ne, no, cur;
 ne = no = cur = 0;
 while(cur < n) {
   int r = a[cur] %2 ;
   switch(r) {
     case 0:
     {
       int temp = a[cur];
       a[cur] = a[ne];
       a[ne] = temp;
       ne++, no++, cur++;
       break;
     }
     case 1:
     {
       a[no++] = a[cur++];
       break;
     }
     default:
     {
       cout << "Error\n";
       break;
     }
   }
 }
}

void printArray(int a[], int n) {
  for(int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
int main() {
  int a[] = {10, 22, 5, 14, 6, 8};
  solve(a, 6);
  printArray(a, 6);
}
