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

void find_min_and_second_min(int a[], int n, int *min, int *smin) {
     int minn = a[0], cur_idx;
     for(cur_idx = 1; cur_idx < n; cur_idx++) {
        if(a[cur_idx] < minn) {
            minn = cur_idx;
        }
     }
     int sminn = LARGE_NUM;
     for(cur_idx = 0; cur_idx < n; cur_idx++) {
        if(a[cur_idx] != minn && a[cur_idx] < sminn) {
            sminn = a[cur_idx];
        }
     }
     *min = minn;
     *smin = sminn;
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
    int min1, smin1;
    int min2, smin2;int min3, smin3;
    int min4, smin4;int min5, smin5;
    int min6, smin6;int min7, smin7;
    int min8, smin8;
    find_min_and_second_min(a1, ARRAY_NUM(a1), &min1, &smin1);
    find_min_and_second_min(a2, ARRAY_NUM(a2), &min2, &smin2);
    find_min_and_second_min(a3, ARRAY_NUM(a3), &min3, &smin3);
    find_min_and_second_min(a4, ARRAY_NUM(a4), &min4, &smin4);
    find_min_and_second_min(a5, ARRAY_NUM(a5), &min5, &smin5);
    find_min_and_second_min(a6, ARRAY_NUM(a6), &min6, &smin6);
    find_min_and_second_min(a7, ARRAY_NUM(a7), &min7, &smin7);
    find_min_and_second_min(a8, ARRAY_NUM(a8), &min8, &smin8);
    printf("min1 = %d, smin1 = %d : ", min1, smin1);
    print_array(a1, ARRAY_NUM(a1));
    printf("min2 = %d, smin2 = %d : ", min2, smin2);
    print_array(a2, ARRAY_NUM(a2));
    printf("min3 = %d, smin3 = %d : ", min3, smin3);
    print_array(a3, ARRAY_NUM(a3));
    printf("min4 = %d, smin4 = %d : ", min4, smin4);
    print_array(a4, ARRAY_NUM(a4));
    printf("min5 = %d, smin5 = %d : ", min5, smin5);
    print_array(a5, ARRAY_NUM(a5));
    printf("min6 = %d, smin6 = %d : ", min6, smin6);
    print_array(a6, ARRAY_NUM(a6));
    printf("min7 = %d, smin7 = %d : ", min7, smin7);
    print_array(a7, ARRAY_NUM(a7));
    printf("min8 = %d, smin8 = %d : ", min8, smin8);
    print_array(a8, ARRAY_NUM(a8));
    return 0;
}
