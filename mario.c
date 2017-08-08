#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    
    // printf("Height: ");
    do
    {        
        printf ("Height: ");
        n = get_int();
    }
    while (n<0 || n>23);
    for (int i=0; i<n; i++)
        {
        for (int s=n-i-1; s>0; s--)
        {
            printf(" ");
        }
        for (int h=0; h<=i+1; h++)
        {
            printf("#");
        }
        printf("\n");
    }
   
}