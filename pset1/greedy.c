#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float n;
    float h;
    int m;
    int k;
    int g;
    int l;
    int f;
    int p;
    int v;
    int s;
    
    printf("0 hai! ");
    do
    {
        printf("How much change is owed?\n");
        n = get_float();
    }
    while (n<0);
    
    h = (n*100);
    m = round (h);
 
    k = m/25;
    l = m%25;
    g = l/10;
    p = l%10;
    f = p/5;
    v = p%5;
    s = v/1;
  
    printf("%i\n",k+g+f+s);
}