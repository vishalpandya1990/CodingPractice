#include <stdio.h>
#include <limits.h>

#define UNDEFINED -1               //assuming a[i] >= 0 for all i
#define NEGATIVE_INFINITY INT_MIN  //assuming a[i] > INT_MIN for all i

/*
 * Problem statement :- http://www.geeksforgeeks.org/find-the-nearest-smaller-numbers-on-left-side-in-an-array/
 */

void nearestSmallerOnLeft_using_stack(int a[], int res[], int n) {
    int s[n+1], top = 0, i;
    s[0] = NEGATIVE_INFINITY;
    for(i = 0; i < n; i++) {
        while(top >=0 && s[top] >= a[i]) top--;
        res[i] = s[top];
        s[++top] = a[i];
    }
}

void nearestSmallerOnLeft_Naive(int a[], int result[], int n) {
    result[0] = UNDEFINED;
    int i, j, min;
    for(i = 1; i < n; i++) {
        result[i] = UNDEFINED;
        for(j = i - 1; j >= 0 ; j--) {
            if(a[j] < a[i]) {
                result[i] = a[j];
                break;
            }
        }
    }
}

void print_result(int res[], int n, int valueForUndefined) {
    int i;
    for(i = 0; i < n; i++){
        if(res[i] != valueForUndefined)
            printf("%d ", res[i]);
        else
            printf("_ ");
    }
    puts("");
}

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int a[n], res[n], i;
        for(i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }
        nearestSmallerOnLeft_using_stack(a, res, n);
        print_result(res, n, NEGATIVE_INFINITY);
    }
	return 0;
}
