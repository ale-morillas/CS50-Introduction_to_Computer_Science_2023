// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

//Dictionary size
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Word hash value
    int word_index = hash(word);

    // Access linked list at that index in hash table
    node *n = table[word_index];

    // Traverse linked list, looking for word (strcasecomp)
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
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
    // TODO: Improve this hash function
    //Set index at 0
    long index = 0;

    // Iterate over the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //Take the alphabetical number of the char and sum it to index
        index += tolower(word[i]);
    }

    return index % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    // Check if there is one
    if (file == NULL)
    {
        printf("Couldn't open dictionary\n");
        return false;
    }

    // Initialise word array
    char next_word[LENGTH + 1];

    // Read every word in the dictionary
    while (fscanf(file, "%s", next_word) != EOF)
    {
        // Create new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //Copy word into node
        strcpy(n->word, next_word);

        //Get hash value of the word
        int hash_value = hash(next_word);

        //Insert node into hash table at location
        n->next = table[hash_value];
        table[hash_value] = n;
        dict_size++;
    }

    //Close file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over hash table
    for (int i = 0; i < N; i++)
    {
        // Assign cursor
        node *cursor = table[i];

        // Loop through linked list
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
