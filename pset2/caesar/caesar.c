#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
    // check if the program is executed with a single command line argument. if not, give an error
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    // convert string in argv[1] into an integer
    int k = atoi(argv[1]);
    // get plaintext from a user
    printf("plaintext:  ");
    string p = get_string();
    printf("ciphertext: ");
    // print siphered text changing only alphabetical characters and leaving other charachters not changed
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i]))
        {
            // if input is alphabetical character, remain the output also an alphabetical character, wrapping around from Z to A
            if (p[i] >= 'A' && p[i] <= 'Z')
            {
            printf("%c", (p[i] - 'A' + k) %26 + 'A');
            }
            if (p[i] >= 'a' && p[i] <= 'z')
            {
                printf("%c", (p[i] - 'a' + k) %26 + 'a');
            }
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;
}