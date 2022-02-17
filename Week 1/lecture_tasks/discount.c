#include <cs50.h>
#include <stdio.h>

float discount(float price, int percent);

float getPercentage(int percent);

int main(void) {
    // Get user input
    float regular = get_float("Regular Price: ");
    int percent_off = get_int("Percent Off: ");
    // Output result
    printf("Sale Price: %.2f\n", discount(regular, percent_off));
}

float getPercentage(int percent) {
    // Calculate percentage from the provided integer
    return (100 - percent) / 100.0;
}

float discount(float price, int percent) {
    // Calculate sale price using initial price and provided integer
    return price * getPercentage(percent);
}