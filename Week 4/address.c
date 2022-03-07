#include <stdio.h>

int main(void)
{
    int n = 50;
    printf("%p\n", &n);
    int *p = &n;
    int c = n; // creates new pointer and memory address
    printf("%i\n", *p);
}