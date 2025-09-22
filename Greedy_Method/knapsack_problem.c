#include <stdio.h>

void fractionalKnapsack(int n, float W, float weight[], float value[]) {
    float ratio[20], temp, total = 0;
    int i, j;

    for (i = 0; i < n; i++)
        ratio[i] = value[i] / weight[i];

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                temp = ratio[i]; ratio[i] = ratio[j]; ratio[j] = temp;
                temp = weight[i]; weight[i] = weight[j]; weight[j] = temp;
                temp = value[i]; value[i] = value[j]; value[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (weight[i] <= W) {
            total += value[i];
            W -= weight[i];
        } else {
            total += ratio[i] * W;
            break;
        }
    }
    printf("Maximum Profit = %.2f\n", total);
}

int main() {
    int n, i;
    float W;
    printf("Enter number of items ");
    scanf("%d", &n);

    float weight[n], value[n];
    printf("Enter weights ");
    for (i = 0; i < n; i++) 
    scanf("%f", &weight[i]);

    printf("Enter values: ");
    for (i = 0; i < n; i++) 
    scanf("%f", &value[i]);

    printf("Enter knapsack capacity: ");
    scanf("%f", &W);

    fractionalKnapsack(n, W, weight, value);
    return 0;
}
