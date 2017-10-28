#include <stdio.h>

#define ARRAY_NUM(arr)  ( sizeof(arr) / sizeof(arr[0]) )

const int LARGE_NUM = 10000001;

void print_array(int a[], int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}

int min(int a, int b) {
 return a < b ? a : b;
}

int max(int a, int b) {
 return a > b ? a : b;
}
void find_min_and_max(int a[], int n, int *minimum, int *maximum) {
    int minn, maxx;
    int i = 0;
    if(n&1){
        minn = maxx = a[0];
        i++;
    } else {
        minn = a[0] < a[1] ? (maxx = a[1], a[0]) : (maxx = a[0], a[1]);
        i += 2;
    }
     for(; i < n; i += 2) {
          if(a[i] < a[i+1]){
            minn = min(minn, a[i]);
            maxx = max(maxx, a[i+1]);
          } else {
            minn = min(minn, a[i+1]);
            maxx = max(maxx, a[i]);
          }
     }

     *minimum = minn;
     *maximum = maxx;
     return;
}

int main() {

    int a1[] = {20, 1, 45, 2, 23};
    int a2[] = {5, 3, 1, 2};
    int a3[] = {1};
    int a4[] = {3, 3};
    int a5[] = {1, 2};
    int a6[] = {3, 1, 1, 2};
    int a7[] = {3, 1, 2, 2, 4};
    int a8[] = {4, 4, 4, 4, 4};
    int min1, max1;
    int min2, max2;int min3, max3;
    int min4, max4;int min5, max5;
    int min6, max6;int min7, max7;
    int min8, max8;
    find_min_and_max(a1, ARRAY_NUM(a1), &min1, &max1);
    find_min_and_max(a2, ARRAY_NUM(a2), &min2, &max2);
    find_min_and_max(a3, ARRAY_NUM(a3), &min3, &max3);
    find_min_and_max(a4, ARRAY_NUM(a4), &min4, &max4);
    find_min_and_max(a5, ARRAY_NUM(a5), &min5, &max5);
    find_min_and_max(a6, ARRAY_NUM(a6), &min6, &max6);
    find_min_and_max(a7, ARRAY_NUM(a7), &min7, &max7);
    find_min_and_max(a8, ARRAY_NUM(a8), &min8, &max8);
    printf("min1 = %d, max1 = %d : ", min1, max1);
    print_array(a1, ARRAY_NUM(a1));
    printf("min2 = %d, max2 = %d : ", min2, max2);
    print_array(a2, ARRAY_NUM(a2));
    printf("min3 = %d, max3 = %d : ", min3, max3);
    print_array(a3, ARRAY_NUM(a3));
    printf("min4 = %d, max4 = %d : ", min4, max4);
    print_array(a4, ARRAY_NUM(a4));
    printf("min5 = %d, max5 = %d : ", min5, max5);
    print_array(a5, ARRAY_NUM(a5));
    printf("min6 = %d, max6 = %d : ", min6, max6);
    print_array(a6, ARRAY_NUM(a6));
    printf("min7 = %d, max7 = %d : ", min7, max7);
    print_array(a7, ARRAY_NUM(a7));
    printf("min8 = %d, max8 = %d : ", min8, max8);
    print_array(a8, ARRAY_NUM(a8));
    return 0;
}
