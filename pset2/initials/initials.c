#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>



int main(void)
{
    // prompt a user for their name
    string s = get_string();
    if (s != NULL)
    {
    // print the first letter of the first word in capital
    printf("%c",toupper(s[0]));
    // iterate along the string, looking for a space
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i-1] == ' ')
        {
            // print the first letter after the space in capital
            printf("%c", toupper(s[i]));
        }
        }
    }
    printf("\n");
}

