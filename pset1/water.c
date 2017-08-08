#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    int m;
    
    printf("Minutes: ");
    do 
    {
        n = get_int();
        m = n * 12;
        printf("Bottles: %i\n",m);
        break;
    }
    while (n>0);
}
