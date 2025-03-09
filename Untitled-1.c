#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 1009

typedef struct 
{
    int key;
    int data;
} HashEntry;

typedef struct
 {
    HashEntry table[TABLE_SIZE];
} HashTable;

int divisionMethod(int key) 
{
    return key % TABLE_SIZE;
}

int midSquareMethod(int key) 
{
    int square = key * key;
    return (square / 100) % TABLE_SIZE;
}

int pureFoldingMethod(int key) 
{
    int sum = 0;
    while (key > 0)
     {
        sum += key % 1000;
        key /= 1000;
    }
    return sum % TABLE_SIZE;
}

int foldShiftingMethod(int key) 
{
    int sum = 0;
    while (key > 0) 
    {
        sum += key % 1000;
        key /= 1000;
    }
    return (sum >> 2) % TABLE_SIZE; // Right shift by 2 bits
}

int foldBoundaryMethod(int key) 
{
    int sum = 0;
    while (key > 0) {
        sum += key % 1000;
        key /= 1000;
    }
    return (sum % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE; // Apply the folding boundary formula
}

void insert(HashTable* hashTable, int key, int data, int (*hashFunction)(int)) 
{
    int index = hashFunction(key);

    while (hashTable->table[index].key != -1) 
    {
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }

    hashTable->table[index].key = key;
    hashTable->table[index].data = data;
}

int main() 
{
    HashTable hashTable;
    srand(time(NULL));

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        hashTable.table[i].key = -1;
    }

    int collisions_division = 0, collisions_mid_square = 0, collisions_pure_folding = 0, collisions_fold_shifting = 0, collisions_fold_boundary = 0;

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        int key = rand() % 10000;
        insert(&hashTable, key, key, divisionMethod);
        insert(&hashTable, key, key, midSquareMethod);
        insert(&hashTable, key, key, pureFoldingMethod);
        insert(&hashTable, key, key, foldShiftingMethod);
        insert(&hashTable, key, key, foldBoundaryMethod);
    }

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hashTable.table[i].key != -1) 
        {
            int j = i + 1;
            while (hashTable.table[j].key != -1) 
            {
                j = (j + 1) % TABLE_SIZE;
                collisions_division++;
            }
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hashTable.table[i].key != -1) 
        {
            int j = i + 1;
            while (hashTable.table[j].key != -1) 
            {
                j = (j + 1) % TABLE_SIZE;
                collisions_mid_square++;
            }
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hashTable.table[i].key != -1) 
        {
            int j = i + 1;
            while (hashTable.table[j].key != -1) 
            {
                j = (j + 1) % TABLE_SIZE;
                collisions_pure_folding++;
            }
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hashTable.table[i].key != -1) 
        {
            int j = i + 1;
            while (hashTable.table[j].key != -1) 
            {
                j = (j + 1) % TABLE_SIZE;
                collisions_fold_shifting++;
            }
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hashTable.table[i].key != -1)
         {
            int j = i + 1;
            while (hashTable.table[j].key != -1)
             {
                j = (j + 1) % TABLE_SIZE;
                collisions_fold_boundary++;
            }
        }
    }

    printf("Collisions using Division Method: %d\n", collisions_division);
    printf("Collisions using Mid Square Method: %d\n", collisions_mid_square);
    printf("Collisions using Pure Folding Method: %d\n", collisions_pure_folding);
    printf("Collisions using Fold Shifting Method: %d\n", collisions_fold_shifting);
    printf("Collisions using Fold Boundary Method: %d\n", collisions_fold_boundary);

    return 0;
}
