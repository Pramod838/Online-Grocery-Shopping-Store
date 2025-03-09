#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node *insert(struct Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

struct Node *unionSets(struct Node *root1, struct Node *root2) {
    struct Node *result = NULL;
    // Insert elements from the first tree
    insertUnion(&result, root1);

    // Insert elements from the second tree
    insertUnion(&result, root2);

    return result;
}

void insertUnion(struct Node **result, struct Node *root) {
    if (root != NULL) {
        insertUnion(result, root->left);
        *result = insert(*result, root->data);
        insertUnion(result, root->right);
    }
}

void printElements(struct Node *root);

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node *root1 = NULL;
    struct Node *root2 = NULL;
    struct Node *unionResult = NULL;

    int n1, n2, i, data;

    printf("Enter the number of nodes in tree 1: ");
    scanf("%d", &n1);

    printf("Enter the data for nodes of tree 1\n");
    for (i = 0; i < n1; i++) {
        scanf("%d", &data);
        root1 = insert(root1, data);
    }

    printf("Enter the number of nodes in tree 2: ");
    scanf("%d", &n2);

    printf("Enter the data for nodes of tree 2\n");
    for (i = 0; i < n2; i++) {
        scanf("%d", &data);
        root2 = insert(root2, data);
    }

    unionResult = unionSets(root1, root2);

    printf("\n Union Tree elements:\n");
    printElements(unionResult);

    // Free memory
    freeTree(root1);
    freeTree(root2);
    freeTree(unionResult);

    return 0;
}

void printElements(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        printElements(root->left);
        printElements(root->right);
    }
}
