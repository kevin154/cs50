// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 400;

// Number of words in dict
unsigned int dictCount = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert to lowercase
    size_t len = 1 + strlen(word);
    char *lower = malloc(len * sizeof(char));
    strcpy(lower, word);

    for (size_t i = 0; i < len; i++) 
    {
        lower[i] = tolower(lower[i]);
    }

    // Get hash of lookup word
    int index = hash(lower);
    node *item = table[index];

    // Ensure that we move to a non NULL item
    while (item != NULL) 
    {
        if (strcmp(item->word, lower) == 0)
        {
            free(lower);
            return true;
        }
        else
        {    
            node *tmp = item->next;
            item = tmp;
        }
    }
    free(lower);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open input file 
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }

    char buffer[LENGTH + 2];

    while (fgets(buffer, LENGTH + 2, input)) 
    {
        node *new_node = malloc(sizeof(node));
        
        // Ensure max length is adhered to by checking newline, else remove newline
        if (strchr(buffer, '\n') == NULL)
        {
            continue;
        }
        else 
        {
            buffer[strcspn(buffer, "\n")] = '\0';
        }
        
        // Copy buffer into current node
        strncpy(new_node->word, buffer, LENGTH + 1);
        
        unsigned int index = hash(buffer);

        // Check if hashtable key is NULL
        if (table[index] == NULL)
        {    
            new_node->next = NULL;
            table[index] = new_node;    
        }
        // Chain new word to existing table index
        else 
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
        dictCount++;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictCount;
}

// Unloads dictionary from memory, returning true if successful
bool unload(void)
{
    node *cursor, *tmp;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    dictCount = 0;
    return true;
}
