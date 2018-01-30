#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int insertion(int arr[], int length);
void merge_sort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);
void count(int arr[], int length);

int main()
{
    int arr[10000], r;
    srand(time(NULL));

    for (int i = 0; i < 10000; ++i) {
        r = rand();
        arr[i] = r % 10000;
    }
    int length = (sizeof(arr) / sizeof(int));
    //insertion(arr, length);
    //merge_sort(arr, 0, length);
    count(arr, length);
    for (int i = 0; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int insertion(int arr[], int length) {
    int storage, i;

    for (int x = 1; x < length; x++) {
        storage = arr[x];
        i = x;
        while (arr[i-1] > storage && i >= 1) {
            arr[i] = arr[i-1];
            i -= 1;
        }
        arr[i] = storage;
    }
    for (i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}


void count(int arr[], int length) {
    int new[length + 1];
    for (int x = 0; x < length + 1; ++x) {
        new[x] = 0;
    }
    int a = 0;
    for (int i = 0; i < length; ++i) {
        new[arr[i]]++;
    }
    for (int i = 0; i < length + 1; ++i) {
        for (int j = 0; j < new[i]; ++j) {
            arr[a++] = i;
        }
    }
}


void merge_sort(int arr[], int low, int high)
{

    int mid = (low + high) / 2;

    if ((high - low) > 1) {
        merge_sort(arr, low, mid);
        merge_sort(arr, mid, high);
        merge(arr, low, mid, high);
    }
}

void merge(int arr[], int low, int mid, int high)
{
    const int lsize = mid - low;
    const int rsize = high - mid;
    int left[lsize];
    int right[rsize];

    int l, r, i;
    l = r = 0;
    i = low;

    for (l = 0; l < lsize; ++i, ++l) {
        left[l] = arr[i];
    }
    i = mid;

    for (r = 0; r < rsize; ++i, ++r) {
        right[r] = arr[i];
    }

    l = r = 0;
    i = low;

    while (i < high) {
        if (l >= lsize) {
            while (r < rsize) {
                arr[i++] = right[r++];
            }
        }
        else if (r >= rsize) {
            while (l < lsize) {
                arr[i++] = left[l++];
            }
        }
        else {
            arr[i++] = (left[l] < right[r]) ? left[l++] : right[r++];
        }
    }
}
