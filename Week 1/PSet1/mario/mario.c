#include <cs50.h>
#include <stdio.h>

int main(void) {
    int height = 0;
    do {
        // Get user input for height
        height = get_int("Enter number between 1-8: ");
    } while (height < 1 || height > 8);
    for (int i = 0; i < height; i++) {
        // Add 2 for gap and i for dynamic row length
        for (int j = 0; j <= height + 2 + i; j++) {
            // Subtract 1 because index starts from 0, subtract i to make pyramid left steps change with line change
            int leftBoundary = height - 1 - i;
            // Middle Gap borders - left less than height and right border height + 1
            bool middleGapCondition = j < height || j > height + 1;

            if ((j >= leftBoundary) && middleGapCondition) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}