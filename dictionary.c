// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

unsigned int dict_size = 0;

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

unsigned int hash(const char *word)
{
    unsigned int value = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        value = value + 37 * tolower(word[i]);
    }
    value = value % N;
    return value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
 
        int x = hash(word);
        node *node1 = malloc(sizeof(node));

        // freeing nodes with no value
        if(node1 == NULL){
            unload();
            return false;
        }
        else{
            node1->next = NULL; // this line for preventing memory related errors.
            strcpy(node1->word,word);

            if (hashtable[x] == NULL)
            {
                hashtable[x] = node1;
            }
            else
            {
                // inserting new node to the beginning
                node1->next = hashtable[x];
                // node1 is now points to whatever hashtable[word] points to
                hashtable[x] = node1;
            }
            dict_size ++;
        }

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return dict_size;

}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int x = hash(word);
    node *temp = hashtable[x];

    //traversing a linkedlist
    while(temp != NULL){
        int result = strcasecmp(temp->word,word);
        if(result == 0){
            return true;
        }
        temp = temp->next;
    }
    return false;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for(int i=0;i<N;i++){
        node *cursor = hashtable[i];

        while(cursor != NULL){
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
