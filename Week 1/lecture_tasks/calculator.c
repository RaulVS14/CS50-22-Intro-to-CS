#include <cs50.h>
#include <stdio.h>

long calcSum(long x, long y) {
    return x + y;
}

int main(void) {
    // Get user input
    long x = get_long("x: ");
    long y = get_long("y: ");
    long z = calcSum(x, y);
    // Output the sum to user
    printf("sum of x and y is: %li\n", z);
}
