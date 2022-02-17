#include <cs50.h>
#include <stdio.h>

int main(void) {
    int n;
    do {
        // Get user input
        n = get_int("Width: ");
    } while (n < 1);
    // Loop through provided width
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((j + i) % 2 == 0) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}