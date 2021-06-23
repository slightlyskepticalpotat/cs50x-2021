// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Total number of words
unsigned int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_num = hash(word);
    node *n = table[hash_num];
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 by dan bernstein - http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; // Bitshifted times 33, add c
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    char new_word[LENGTH + 1];
    while (fscanf(input, "%s", new_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, new_word);
        unsigned int hash_num = hash(new_word);
        n->next = table[hash_num];
        table[hash_num] = n;
        words += 1;
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n)
        {
            // Refer to n by a different name
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        return true;
    }
    // We should never get here
    return false;
}
