#include <bits/stdc++.h>
using namespace std;

int n = 5;

// O(n^2) complexity
void bubble_sort(int* arr) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void merge(int *arr, int l, int m, int r) {
    int ll = m - l + 1;
    int rl = r - m;
    int temp_l[ll], temp_r[rl];

    for (int i = 0; i < ll; i++) {
        temp_l[i] = arr[l+i];
    }

    for (int i = 0; i < rl; i++) {
        temp_r[i] = arr[m+i+1];
    }

    for (int i = 0, j = 0, k = l; k <= r; k++) {
        if (i < ll && j >= rl || temp_l[i] <= temp_r[j]) {
            arr[k] = temp_l[i];
            i++;
        } else {
            arr[k] = temp_r[j];
            j++;
        }
    }
}
// O(nlogn) complexity
void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l)/2;

        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

// O(nlogn) complexity
void quick_sort(int a[], int l, int r){
    if (l <= r) {
        int m = a[(l+r)/2];
        int lx = l;
        int rx = r;
        while (lx <= rx) {
            while (a[lx] < m)
                lx++;
            while (m < a[rx])
                rx--;
            if (lx <= rx)
                swap(a[lx++],a[rx--]);
        }
        quick_sort(a, l, rx);
        quick_sort(a, lx, r);
    }
}


int main() {
    int nums[] = {2,4,3,1,5};
//    bubble_sort(nums);
//    merge_sort(nums, 0, n-1);
//    quick_sort(nums, 0, n-1);
    for (int i = 0; i < n; i++)
        cout << nums[i] << " ";
}