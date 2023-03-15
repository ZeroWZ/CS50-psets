#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 100000

// Hash table
node *table[N];

unsigned int Index;
node *tmp = NULL;
unsigned int count = 0;
char Word[LENGTH + 1];
unsigned int sum, len;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    for (tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number for check function
unsigned int hash(const char *word)
{
    sum = 0;
    len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        sum = tolower(word[i]) + sum * (len - i) * (i * i * len);
    }
    return sum % N;

}

unsigned int hash2(const char *word)
{
    sum = 0;
    len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        sum = word[i] + sum * (len - i) * (i * i * len);
    }
    return sum % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("The dictionary can't open\n");
        return false;
    }

    // Get every word in the dictionary and add it to the hash table
    while (1)
    {
        node *n_node = malloc(sizeof(node));
        if (n_node == NULL)
        {
            printf("there isn't enough memory\n");
            fclose(dic);
            return false;
        }
        if (fscanf(dic, "%s", n_node->word) == EOF)
        {
            free(n_node);
            break;
        }

        Index = hash2(n_node->word);


        n_node->next = table[Index];

        table[Index] = n_node;
        count++;
    }

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            if (table[i]->next != NULL)
            {
                do
                {
                    tmp = table[i]->next;
                    free(table[i]);
                    table[i] = tmp;
                }
                while (table[i]->next != NULL);

                free(table[i]);
            }
            else
            {
                free(table[i]);
            }
        }
    }
    return true;
}