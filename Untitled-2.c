#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 310051
#define HASH_TABLE_SIZE 19937

int divisionHash(int key)
 {
    return key % TABLE_SIZE;
}

int midSquareHash(int key)
 {
    key = (key * key) / 4096;
    return key % TABLE_SIZE;
}

int pureFoldingHash(int key)
 {
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    return sum % TABLE_SIZE;
}

int foldShiftingHash(int key)
 {
    int sum = 0;
    while (key > 0) {
        sum += key % 256;
        key /= 256;
    }
    return sum % TABLE_SIZE;
}

int foldBoundaryHash(int key) 
{
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    sum += key % 9;
    return sum % TABLE_SIZE;
}

int main()
 {
    int n = TABLE_SIZE; 

    int hashtable[TABLE_SIZE] = {0};
    int collisions[5] = {0};

    int (*hash_functions[5])(int);
    hash_functions[0] = divisionHash;
    hash_functions[1] = midSquareHash;
    hash_functions[2] = pureFoldingHash;
    hash_functions[3] = foldShiftingHash;
    hash_functions[4] = foldBoundaryHash;

    FILE *file = fopen("C://Users//pramo//Downloads//input_file.txt", "r"); 
    if (file == NULL)
     {
        printf("Failed to open the file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
     {
        char key[100]; 
        if (fscanf(file, "%s", key) != 1) {
            break;
        }

        int sum = 0;
        for (int j = 0; key[j] != '\0'; j++)
         {
            sum += key[j];
        }

        int index = hash_functions[i % 5](sum);

        while (hashtable[index] != 0)
         {
            collisions[i % 5]++;
            index = (index + 1) % TABLE_SIZE;
        }

        hashtable[index] = sum;
    }

    fclose(file);

    printf("Collisions using Division Method: %d\n", collisions[0]);
    printf("Collisions using Mid Square Method: %d\n", collisions[1]);
    printf("Collisions using Pure Folding Method: %d\n", collisions[2]);
    printf("Collisions using Fold Shifting Method: %d\n", collisions[3]);
    printf("Collisions using Fold Boundary Method: %d\n", collisions[4]);

    return 0;
}
