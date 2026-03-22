#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   

#include "dictionary.h"

#define N 10007

typedef struct node
{
    char word[LENGTH + 1];   
    struct node *next;       
} node;
node *table[N];
unsigned int word_count = 0;

unsigned int hash(const char *word)
{
    // Using the djb2 algorithm for better distribution across buckets.
    unsigned long hash_val = 5381;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_val = ((hash_val << 5) + hash_val) + tolower(word[i]);
    }
    return hash_val % N;
}

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    
    // Read strings from file one at a time
    while (fscanf(file, "%45s", word) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);

        // Hash word to obtain a hash value
        unsigned int index = hash(word);

        // Insert node into hash table at that location (prepend)
        n->next = table[index];
        table[index] = n;
        
        // Increment global word counter
        word_count++;
    }

    fclose(file);
    return true;
}

bool check(const char *word)
{
    // Hash the word to obtain its bucket index
    unsigned int index = hash(word);

    // Traverse the linked list at that specific bucket
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        // Compare case-insensitively
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    
    return false;
}

unsigned int size(void)
{
    return word_count;
}

bool unload(void)
{
    // Iterate through all buckets in the hash table array
    for (int i = 0; i < N; i++)
    {
        // Set a pointer to the head of the linked list
        node *tmp = table[i];
        
        // Traverse and free each node
        while (tmp != NULL)
        {
            node *next = tmp->next; 
            free(tmp);              
            tmp = next;             
        }
    }

    return true;
}