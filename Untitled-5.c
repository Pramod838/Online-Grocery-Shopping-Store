#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define table_size 310051
#define prob_size 19937
#define M 19191

int hash_function(int key) 
{
    return key % table_size;
}

int quadratic_probing(int key, int i) 
{
    return (key + i * i) % table_size;
}

int double_hashing(int key, int i) 
{
    int hash1 = key % table_size;
    int hash2 = M - (key % M);
    return (hash1 + i * hash2) % table_size;
}

void insert(int hash_table[], int key, int probing_type) 
{
    int i = 0;
    int h;

    switch (probing_type) 
    {
        case 0: 
            h = (key + M) % table_size;
            break;
        case 1:
            h = quadratic_probing(key, i);
            break;
        case 2: 
            h = double_hashing(key, i);
            break;
        default:
            h = key % table_size; 
    }

    
    hash_table[h] = key;
}

int main() 
{
    int hash_table[table_size] = {0};
    
    int probing_type;

    FILE *file = fopen("C://Users//pramo//Downloads//input_file.txt", "r");
    
    int num_lines;

    printf("Enter number of lines to insert: ");

    scanf("%d", &num_lines);


    printf("Select probing (1/2/3): ");
    scanf("%d", &probing_type);

    for (int i = 0; i < num_lines; i++)
     {
        char line[80];

        if (fgets(line, sizeof(line), file) == NULL) 
        {
            printf("Error in reading line %d from file\n", i + 1);
            break;
        }

        int sum = 0;

        for (int j = 0; line[j] != '\0'; j++)
         {
            sum += (int)line[j];
        }

        insert(hash_table, sum, probing_type);
    }

    fclose(file);

    int primary_clusters = 0;
    int secondary_clusters = 0;
    int cluster_length = 0;

    for (int i = 0; i < table_size; i++)
    {
        if (hash_table[i] != 0) 
        {
            cluster_length++;
        } 
        else 
        {
            if (cluster_length >= 5) 
            {
                primary_clusters++;
            } 
            else if (cluster_length > 1) 
            {
                secondary_clusters++;
            }
            cluster_length = 0;
        }
    }

    printf("Primary clusters: %d\n", primary_clusters);
    printf("Secondary clusters: %d\n", secondary_clusters);

    return 0;
}
