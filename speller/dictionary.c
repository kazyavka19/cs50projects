// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> 
#include "dictionary.h"
#include <string.h> 

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 47697

// Hash table
node *table[N];

unsigned int word_count = 0;

bool same_word_case_insensitive(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {   if (tolower(a[i]) != tolower(b[i]))
        {   
          return false;
        }
        i++;        
    }
    return a[i] == '\0' && b[i] == '\0';
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO 
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if(same_word_case_insensitive(cursor->word, word))
        {
            return true;
        }
        cursor = cursor->next;
    }
       
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        count = (count * 37 + tolower(word[i]));
    }
    
    return count % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)    
    {
        fprintf(stderr, "Could not open file %s\n", dictionary);
        return false;
    }
    char word[LENGTH + 1];

    while (fscanf(file,"%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            fprintf(stderr, "Could not allocate memory for new node\n");
            fclose(file);
            return false;
        }
        int index = hash(word);
        strcpy(new_node->word, word);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
