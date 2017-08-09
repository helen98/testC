#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    //if there are 2 words (including ./argv0)
    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, world\n");
    }
}