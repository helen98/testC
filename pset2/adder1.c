// includes
#include <cs50.h>
#include <stdio.h>

// declare functions
int add_two_ints(int a, int b);

int main(void)
{
    // ask user for input
    printf("Give me an integer: ");
    int x = get_int();
    printf("Give me an integer: ");
    int y = get_int();
    
    // add the two numbers togethet via a function call
    int z = add_two_ints(x, y);
    
    // output the result
    printf("The sum of %i and %i is %i\n", x, y, z);
}

int add_two_ints(int x, int y)
{
    return x + y;
}