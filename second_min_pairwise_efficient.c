#include <stdio.h>

#define ARRAY_NUM(arr)  ( sizeof(arr) / sizeof(arr[0]) )

typedef struct pair {
  int f, s;
}pair;

void find_min_and_second_min(int a[], int n, int *min, int *smin) {
     if(n == 1) {
         *min = *smin = a[0];
         return;
     }
     if(n == 2) {
         *smin = a[0] < a[1] ? (*min = a[0], a[1]) : (*min = a[1], a[0]);
         return;
     }
     int first = a[0];
     int num = n;
     int *base = a;
     if(n&1) {
        base++;
        num--;
     }
     int pair_count = num/2;
     int *pair_min = (int *)malloc(pair_count * sizeof(int));
     pair *p = (struct pair *)malloc(pair_count * sizeof(pair));
     int base_idx, pair_idx = 0;
     for(base_idx = 0; base_idx < num; base_idx += 2) {
        int minn = base[base_idx] < base[base_idx+1] ? base[base_idx] : base[base_idx+1];
        pair_min[pair_idx] = minn;
        p[pair_idx].f = base[base_idx];
        p[pair_idx].s = base[base_idx+1];
        pair_idx++;
     }
    int pmin, psmin;
    find_min_and_second_min(pair_min, pair_count, &pmin, &psmin);
    for(pair_idx = 0 ; pair_idx < pair_count; pair_idx++) {
        if(pair_min[pair_idx] == pmin) break;
    }
    int min_pair_second = p[pair_idx].f == pmin ? p[pair_idx].s : p[pair_idx].f;
    *min = pmin;
    *smin = psmin < min_pair_second ? psmin : min_pair_second;
    if(n&1) {
        if(first < *min) {
            *smin = *min;
            *min = first;
        } else if(first < *smin) {
           *smin = first;
        }
    }
    free(p);
    free(pair_min);
    return;
}

void print_array(int a[], int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main() {
    int a1[] = {20, 1, 45, 2, 23};
    int a2[] = {5, 3, 1, 2};
    int a3[] = {1};
    int a4[] = {3, 3};
    int a5[] = {1, 2};
    int a6[] = {3, 1, 1, 2};
    int a7[] = {3, 1, 2, 2, 4};
    int min1, smin1;
    int min2, smin2;int min3, smin3;
    int min4, smin4;int min5, smin5;
    int min6, smin6;int min7, smin7;
    find_min_and_second_min(a1, ARRAY_NUM(a1), &min1, &smin1);
    find_min_and_second_min(a2, ARRAY_NUM(a2), &min2, &smin2);
    find_min_and_second_min(a3, ARRAY_NUM(a3), &min3, &smin3);
    find_min_and_second_min(a4, ARRAY_NUM(a4), &min4, &smin4);
    find_min_and_second_min(a5, ARRAY_NUM(a5), &min5, &smin5);
    find_min_and_second_min(a6, ARRAY_NUM(a6), &min6, &smin6);
    find_min_and_second_min(a7, ARRAY_NUM(a7), &min7, &smin7);
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
    return 0;
}
