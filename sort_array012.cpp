#include <iostream>
using namespace std;
void solve(int a[], int n) { 
 if(n <= 1) return;
 int nz, nt, no, cur;
 nz = nt = no = cur = 0;
 while(cur < n) {
   switch(a[cur++]) {
     case 0:
     {
       a[nt++] = 2;
       a[no++] = 1;
       a[nz++] = 0;
       break;
     }
     case 1:
     {
       a[nt++] = 2;
       a[no++] = 1;
       break;
     }
     case 2:
     {
       a[nt++] = 2;
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
  int a[] = {0, 2, 1, 1, 0, 0};
  solve(a, 6);
  printArray(a, 6);
}
