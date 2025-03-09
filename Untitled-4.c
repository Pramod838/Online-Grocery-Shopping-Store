#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 310051
#define HASH_SIZE1 19937
#define HASH_SIZE2 19934

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(Node** hashTable, int hashSize, int key) {
    int index = key % hashSize;
    Node* newNode = createNode(key);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

double calculateLoadFactor(int numKeys, int hashSize) {
    return (double)numKeys / hashSize;
}

int calculateASCIISum(char* str) {
    int sum = 0;
    for (int i = 0; i < strlen(str); i++)
     {
        sum += str[i];
    }
    return sum;
}

int main() {
    Node* hashTable1[HASH_SIZE1] = {NULL};
    Node* hashTable2[HASH_SIZE2] = {NULL};
    char key[65];
    int numKeys = 0;
    int totalKeys;

    printf("Enter the number of keys to insert: ");
    scanf("%d", &totalKeys);

  
  FILE *file = fopen("C://Users//pramo//Downloads//input_file.txt", "r"); 
   

    while (fgets(key, sizeof(key), file) != NULL && numKeys < totalKeys) 
    {
        int asciiSum = calculateASCIISum(key);
        insert(hashTable1, HASH_SIZE1, asciiSum);
        insert(hashTable2, HASH_SIZE2, asciiSum);
        numKeys++;
    }

    fclose(file);

    printf("Load factor for hash table size %d: %.10f\n", HASH_SIZE1, calculateLoadFactor(numKeys, HASH_SIZE1));
    printf("Load factor for hash table size %d: %.10f\n", HASH_SIZE2, calculateLoadFactor(numKeys, HASH_SIZE2));

    return 0;
}
