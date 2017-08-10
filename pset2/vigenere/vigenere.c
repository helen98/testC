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
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    // check for alphabetical characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
        printf("Usage: ./vigenere k\n");
        return 1; 
        }
    }
    // get plaintext from a user
    printf("plaintext:  ");
    string p = get_string();
    int k = 0;
    printf("ciphertext: ");
    // iterate over strings in p
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // wrap round the key
        k = k % strlen(argv[1]);
        // if alpha, cipher. if not, leave as it is
        if (isalpha(p[i]))
        {
            //check 4 variants:
            // char of plaintext is small letter,char of key is small letter
            if (islower(p[i]) && islower(argv[1][k]))
                printf("%c", (((p[i] - 97) + (argv[1][k] - 97)) % 26) + 97);
            // char of plaintext is capital letter,char of key is small letter
            else if (isupper(p[i]) && islower(argv[1][k]))
                printf("%c", (((p[i] - 65) + (argv[1][k] - 97)) % 26) + 65);
            // char of plaintext is small letter,char of key is capital letter
            else if (islower(p[i]) && isupper(argv[1][k]))
                printf("%c", (((p[i] - 97) + (argv[1][k] - 65)) % 26) + 97);
            // char of plaintext is capital letter,char of key is capital letter
            else if (isupper(p[i]) && isupper(argv[1][k]))
                printf("%c", (((p[i] - 65) + (argv[1][k] - 65)) % 26) + 65);
            // iterate over the key
            k++;
        }
        else
        {
            printf("%c", p[i]);
        }

    }
    printf("\n");
    return 0;
}