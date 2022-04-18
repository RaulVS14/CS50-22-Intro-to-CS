// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26 * 10000 + 26 * 100 + LENGTH; //

// Hash table
node *table[N];

// Number of words
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get word possible position in hash table
    int position = hash(word);
    // Check dictionary contains provided hash
    if (table[position] == NULL)
    {
        return false;
    }

    // Assign first node for check
    node *toCheck = table[position];
    //
    while (toCheck != NULL)
    {
        if (strcasecmp(word, toCheck->word) == 0)
        {
            return true;
        }

        toCheck = toCheck->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char firstLetter = word[0];
    int wordLength = strlen(word);
    int firstLetterNumber = toupper(firstLetter) - 'A';
    int secondLetterNumber = 0;
    if (wordLength > 1)
    {
        secondLetterNumber = toupper(word[1]) - 'A';
    }
    // Assign spot: firstLetter(0-26), secondLetter(0-26), wordLength(0-45). Example: AAH = 003
    return firstLetterNumber * 10000 + abs(secondLetterNumber) * 100 + wordLength;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dictFile, "%s", word) != EOF)
    {
        // Allocate memory for node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Store word in a node
        strcpy(n->word, word);
        // Get position for storing the word from hash function
        int position = hash(word);
        // Add node into hash table
        if (table[position])
        {
            // If there is a node in the position at hash table, remap the node to the head
            n->next = table[position];
            table[position] = n;
        }
        else
        {
            // Fill position in hash table with a node
            table[position] = n;
            n->next = NULL;
        }
        wordCount ++;
    }
    fclose(dictFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        node *next = temp;
        while (next != NULL)
        {
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return true;
}
