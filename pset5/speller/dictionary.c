/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"



//declare structure node
typedef struct node
    {
        bool is_word;
        struct node *children[27];
    }
    node;

struct node *root = NULL;
node *trav;
// words in dictionary counter
int n = 0;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    node *trav = root;

    char word_t[strlen(word)];
    // iterate over characters in input word
    for (int i = 0; word[i] != '\0'; i++)
    {
        word_t[i] = tolower(word[i]);
        // if character is apostrophe
        if (word_t[i] == '\'')
        {
            int index = 26;
            // check the value at children[index]
            if (trav -> children[index] != NULL)
            {
                // got to a new node
                trav = trav -> children[index];
            }
            else
            {
                return false;
            }
        }
        // if character is alphabetical
        else
        {
            int index = word_t[i] % 97;
            // check the value at children[index]
            if (trav -> children[index] != NULL)
            {
                // go to a new node
                trav = trav -> children[index];
            }
            else
            {
            return false;
            }
        }
    }
    return trav -> is_word;
}

/**
 * Creates a new node
 */
node* createNode(void)
{
    return (node*) calloc(1, sizeof(node));

}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *ptr = fopen (dictionary, "r");
    // if openning failed, report an error
    if (ptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    char word_d[LENGTH];

    // allocate memory for root to keep track of root
    root = createNode();
    node *trav = root;

    // scan dictionary file for words
    while (fscanf(ptr, "%s", word_d) != EOF)
    {
        // iterate over word in dictionary
        for (int i = 0; word_d[i] != '\0'; i++)
        {
            // transform a letter into index
            // if character is apostrophe
            if (word_d[i] == '\'')
            {
                int index = 26;
                // check the value at children[index]
                if (trav -> children[index] == NULL)
                {
                    // create a new node
                    trav -> children[index] = createNode();

                    // have children[index] point to a new node
                    trav = trav -> children[index];
                }
                else
                {
                    // move to a new node
                    trav = trav -> children[index];
                }
            }
            // if character is alphabetical
            else
            {
                int index = word_d[i] % 97;

                // check the value at children[index]
                if (trav -> children[index] == NULL)
                {
                    // create a new node
                    trav -> children[index] = createNode();
                    // have children[index] point to a new node
                    trav = trav -> children[index];
                }
                else
                {
                    // move to a new node
                    trav = trav -> children[index];
                }
            }

        }
        // update counter of words in dictionary
        n++;
        trav -> is_word = true;
        // go back to the root
        trav = root;
    }
    // success
    fclose(ptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return n;

}

void unloadNode(node* trav)
{
    // call unloadNode on every node
    for(int i = 0; i < 27; i++)
    {
        if(trav->children[i] != NULL)
        {
            unloadNode(trav->children[i]);
        }
    }

    // free this node
    free(trav);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // call the recursive algorithm 'unloadNode', starting with the root
    unloadNode(root);
    return true;
}
