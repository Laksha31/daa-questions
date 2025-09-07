#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++)
    { L[i] = arr[l + i]; }
    for (int j = 0; j < n2; j++)
    { R[j] = arr[m + 1 + j]; }
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr1 = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc(n * sizeof(int));

    srand(time(0));
    for (int i = 0; i < n; i++) {
        int val = rand() % 100000;
        arr1[i] = arr2[i] = val;
    }

    clock_t start, end;
    double time_taken;

    start = clock();
    mergeSort(arr1, 0, n - 1);
    end = clock();
    time_taken = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC; 
    printf("Merge Sort took %.2f ms\n", time_taken);

    start = clock();
    quickSort(arr2, 0, n - 1);
    end = clock();
    time_taken = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC; 
    printf("Quick Sort took %.2f ms\n", time_taken);
    free(arr1);
    free(arr2);
    return 0;
}
