/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

// function
bool binary_search(int values[], int start, int end, int value)
{
    // while n > 0
    if (end >= start)
    {
        // look at the middle integer
        int mid = start + (end - start) / 2;
        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] > value)
        {
            // call the function again, setting integer mid - 1 as the end of array (search left)
            return binary_search(values, start, mid - 1, value);
        }
        else if (values[mid] < value)
        {
            // call the function again, setting integer mid + 1 as the start of array (search right)
            return binary_search(values, mid + 1, end, value);
        }
        
    }
    return false;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // call function binary_search
    return binary_search(values, 0, n - 1, value);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int min;
    // itarate over the array
    for(int i = 0; i <= n - 2; i++)
    {
        // set the first integer a minimum
        min = values[i];
        int j = i + 1;
        while (j <= n - 1)
        {
            // compare minimum with other integers in the array from left to right
            if (min > values[j])
            {
                // swap integers
                int acc = values[j];
                values[j] = min;
                min = acc;
                values[i] = min;
            }
            j++;
        }
    }
    return;
}
