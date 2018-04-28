#include <iostream>
using namespace std;

const int maxrow = 4;
const int maxcol = 4;

void solve(int a[maxrow][maxcol]) { 
 int count = 0, row = 0, col = maxcol-1;
 while(row < maxrow && col >= 0) {
    if(a[row][col] == 0)
        col--, count++;
    else {
        row++;
    }
 }
 cout << count << endl;
}

int main() {
  int a[maxrow][maxcol] = {
                  {1,1,1,1},
                  {1,0,0,0},
                  {1,1,0,0},
                  {1,1,1,0},
  };
  solve(a);
}
