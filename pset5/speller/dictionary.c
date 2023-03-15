// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int s = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int fri(node *n);

// Number of buckets in hash table
#define N 10000

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);
    node *n = NULL;
    if (table[h] != NULL)
    {
        if (strcasecmp(table[h]->word, word) == 0)
        {
            return true;
        }
        else if (table[h]->next != NULL)
        {
            n = table[h]->next;

            for (; n->next != NULL; n = n->next)
            {
                if (strcasecmp(n->word, word) == 0)
                {
                    return true;
                }
            }

            if (n->next == NULL)
            {
                if (strcasecmp(n->word, word) == 0)
                {
                    return true;
                }
            }

        }
    }
    return false;
}

unsigned int sum, len;
// Hashes word to a number
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

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dctnry = fopen(dictionary, "r");
    if (dctnry == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    char tmp_W[LENGTH + 1];
    while (fscanf(dctnry, "%s", tmp_W) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dctnry);
            return false;
        }
        strcpy(n->word, tmp_W);
        n->next = NULL;

        int h = hash(n->word);
        if (table[h] != NULL)
        {
            n->next = table[h];
            table[h] = n;
            s++;
        }
        else
        {
            table[h] = n;
            s++;
        }
    }
    fclose(dctnry);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return s;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int l = 0;
    for (int i = 0; N > i; i++)
    {
        if (table[i] == NULL)
        {
            l++;
        }
        else
        {
            int k = fri(table[i]);
            if (k == 0)
            {
                l++;
            }
        }
    }

    if (l == N)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

int fri(node *n)
{
    node *nl = NULL;
    if (n->next == NULL)
    {
        free(n);
        return 0;
    }
    nl = n->next;
    free(n);
    fri(nl);
    return 0;

}