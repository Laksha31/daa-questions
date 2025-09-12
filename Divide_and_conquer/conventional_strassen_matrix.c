#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void conventionalMultiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;
    int A11[mid][mid], A12[mid][mid], A21[mid][mid], A22[mid][mid];
    int B11[mid][mid], B12[mid][mid], B21[mid][mid], B22[mid][mid];
    int C11[mid][mid], C12[mid][mid], C21[mid][mid], C22[mid][mid];
    int M1[mid][mid], M2[mid][mid], M3[mid][mid], M4[mid][mid];
    int M5[mid][mid], M6[mid][mid], M7[mid][mid];
    int temp1[mid][mid], temp2[mid][mid];

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    add(mid, A11, A22, temp1);
    add(mid, B11, B22, temp2);
    strassen(mid, temp1, temp2, M1);

    add(mid, A21, A22, temp1);
    strassen(mid, temp1, B11, M2);

    sub(mid, B12, B22, temp2);
    strassen(mid, A11, temp2, M3);

    sub(mid, B21, B11, temp2);
    strassen(mid, A22, temp2, M4);

    add(mid, A11, A12, temp1);
    strassen(mid, temp1, B22, M5);

    sub(mid, A21, A11, temp1);
    add(mid, B11, B12, temp2);
    strassen(mid, temp1, temp2, M6);

    sub(mid, A12, A22, temp1);
    add(mid, B21, B22, temp2);
    strassen(mid, temp1, temp2, M7);

    add(mid, M1, M4, temp1);
    sub(mid, temp1, M5, temp2);
    add(mid, temp2, M7, C11);

    add(mid, M3, M5, C12);

    add(mid, M2, M4, C21);

    sub(mid, M1, M2, temp1);
    add(mid, temp1, M3, temp2);
    add(mid, temp2, M6, C22);

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }
}

long long current_time_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000000 + tv.tv_usec;
}

int main() {
    int n;
    printf("Enter matrix size (e.g., 2 or 4): ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C1[n][n], C2[n][n];

    printf("Enter elements of Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    int iterations = 10000;

    long long start, end;

    start = current_time_microseconds();
    for (int i = 0; i < iterations; i++) {
        conventionalMultiply(n, A, B, C1);
    }
    end = current_time_microseconds();
    double time_conventional = (end - start) / (double)iterations;

    start = current_time_microseconds();
    for (int i = 0; i < iterations; i++) {
        strassen(n, A, B, C2);
    }
    end = current_time_microseconds();
    double time_strassen = (end - start) / (double)iterations;

    printf("\nConventional Result:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C1[i][j]);
        printf("\n");
    }

    printf("\nStrassen Result:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C2[i][j]);
        printf("\n");
    }

    printf("\nAverage Time (per multiplication):\n");
    printf("Conventional: %.3f microseconds\n", time_conventional);
    printf("Strassen: %.3f microseconds\n", time_strassen);

    return 0;
}
