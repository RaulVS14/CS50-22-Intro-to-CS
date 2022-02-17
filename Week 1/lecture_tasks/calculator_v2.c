#include <cs50.h>
#include <stdio.h>

int main(void) {
    // Ask user input
    float x = get_float("x: ");
    float y = get_float("y: ");

    // Divide
    float z = x / y;
    printf("%.2f\n", z);
}