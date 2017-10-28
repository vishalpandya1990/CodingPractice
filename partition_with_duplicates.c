#include <stdio.h>

#define ARRAY_NUM(arr) (sizeof(arr) / sizeof(arr[0]))

/* This is a little tricky way of returning 2 integer values.
   We can later change it to some proper method.
   While using this method of returning values, we require
   index values (or n) to be lesser than this constant.
*/

const int MULTIPLICATION_CONST = 100000001;

void printArray(int a[], int n) {
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int *p, int *q) {
   int tmp = *p;
   *p = *q;
   *q = tmp;
}

int partition_with_duplicates(int a[], int low, int high) {
    int pivot = a[high];
    int le, ee, cur;
    le = ee = low-1;
    cur = low;
    while(cur < high) {
        if(a[cur] > pivot){
            cur++;
        } else if(a[cur] == pivot) {
            ee++;
            swap(&a[cur], &a[ee]);
            cur++;
        } else {
            le++;ee++;
            swap(&a[le], &a[cur]);
            swap(&a[ee], &a[cur]);
            cur++;
        }
    }
    swap(&a[ee+1], &a[high]);
    ee++;
    return (le+1)*MULTIPLICATION_CONST + ee;
}

int main(){
    int a1[] = {1};
    int a2[] = {1, 2};
    int a3[] = {1,2,3};
    int a4[] = {1,3,2};
    int a5[] = {2,3,1,2};
    int a6[] = {1,2,2};
    int a7[] = {1,3,2,2};
    int a8[] = {1,3,2,2,5,3};
    printf("\nBefore\n");
    printArray(a1, ARRAY_NUM(a1));
    printArray(a2, ARRAY_NUM(a2));
    printArray(a3, ARRAY_NUM(a3));
    printArray(a4, ARRAY_NUM(a4));
    printArray(a5, ARRAY_NUM(a5));
    printArray(a6, ARRAY_NUM(a6));
    printArray(a7, ARRAY_NUM(a7));
    printArray(a8, ARRAY_NUM(a8));
    int x1 = partition_with_duplicates(a1, 0, ARRAY_NUM(a1) - 1);
    int x2 = partition_with_duplicates(a2, 0, ARRAY_NUM(a2) - 1);
    int x3 = partition_with_duplicates(a3, 0, ARRAY_NUM(a3) - 1);
    int x4 = partition_with_duplicates(a4, 0, ARRAY_NUM(a4) - 1);
    int x5 = partition_with_duplicates(a5, 0, ARRAY_NUM(a5) - 1);
    int x6 = partition_with_duplicates(a6, 0, ARRAY_NUM(a6) - 1);
    int x7 = partition_with_duplicates(a7, 0, ARRAY_NUM(a7) - 1);
    int x8 = partition_with_duplicates(a8, 0, ARRAY_NUM(a8) - 1);
    printf("\nAfter\n");
    printf("s1 = %d, e1 = %d : ", x1/MULTIPLICATION_CONST, x1%MULTIPLICATION_CONST);
    printArray(a1, ARRAY_NUM(a1));
    printf("s2 = %d, e2 = %d : ", x2/MULTIPLICATION_CONST, x2%MULTIPLICATION_CONST);
    printArray(a2, ARRAY_NUM(a2));
    printf("s3 = %d, e3 = %d : ", x3/MULTIPLICATION_CONST, x3%MULTIPLICATION_CONST);
    printArray(a3, ARRAY_NUM(a3));
    printf("s4 = %d, e4 = %d : ", x4/MULTIPLICATION_CONST, x4%MULTIPLICATION_CONST);
    printArray(a4, ARRAY_NUM(a4));
    printf("s5 = %d, e5 = %d : ", x5/MULTIPLICATION_CONST, x5%MULTIPLICATION_CONST);
    printArray(a5, ARRAY_NUM(a5));
    printf("s6 = %d, e6 = %d : ", x6/MULTIPLICATION_CONST, x6%MULTIPLICATION_CONST);
    printArray(a6, ARRAY_NUM(a6));
    printf("s7 = %d, e7 = %d : ", x7/MULTIPLICATION_CONST, x7%MULTIPLICATION_CONST);
    printArray(a7, ARRAY_NUM(a7));
    printf("s8 = %d, e8 = %d : ", x8/MULTIPLICATION_CONST, x8%MULTIPLICATION_CONST);
    printArray(a8, ARRAY_NUM(a8));
    return 0;
}

