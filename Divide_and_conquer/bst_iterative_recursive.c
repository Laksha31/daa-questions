#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL) return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

struct Node* searchRecursive(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return searchRecursive(root->left, key);
    return searchRecursive(root->right, key);
}

struct Node* searchIterative(struct Node* root, int key) {
    while (root != NULL) {
        if (key == root->key)
            return root;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

int main() {
    struct Node* root = NULL;
    int n, i, key;
    clock_t start, end;
    double tRec, tItr;

    printf("Enter number of nodes: \n");
    scanf("%d", &n);
    srand(time(0));

    printf("Randomly generated elements:\n");
    for (i = 0; i < n; i++) {
        int val = rand() % 1000;  // values between 0–999
        printf("%d ", val);
        root = insert(root, val);
    }
    printf("\n");

    printf("Enter key to search: ");
    scanf("%d", &key);
    int repeat = 100000;  // increased repeat for better timing accuracy

    // Recursive Search
    start = clock();
    for (i = 0; i < repeat; i++)
        searchRecursive(root, key);
    end = clock();
    tRec = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Iterative Search
    start = clock();
    for (i = 0; i < repeat; i++)
        searchIterative(root, key);
    end = clock();
    tItr = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Recursive: %s\n", searchRecursive(root, key) ? "Found" : "Not Found");
    printf("Iterative: %s\n", searchIterative(root, key) ? "Found" : "Not Found");
    printf("Time Recursive (avg over %d runs): %.3f µs\n", repeat, (tRec * 1000000) / repeat);
    printf("Time Iterative (avg over %d runs): %.3f µs\n", repeat, (tItr * 1000000) / repeat);

    return 0;
}
