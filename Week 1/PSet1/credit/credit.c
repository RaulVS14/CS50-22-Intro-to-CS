#include <cs50.h>
#include <stdio.h>

bool checkCardChecksum(long cardNumber);

int main(void) {

    // Print card
    // AMEX: 15 digit, 34 || 37
    // MASTERCARD: 16 digit, starts with 51-55
    // VISA: 13 || 16, starts with 4
    // Get card number from input
    long cardNumber = 0;
    do {
        cardNumber = get_long("Number: ");
    } while (cardNumber < 1);
    // Calculate checksum
    bool checkSum = checkCardChecksum(cardNumber);
    // Check length and starting digits
    printf("%s", checkSum ? "true" : "false");

}

bool checkCardChecksum(long cardNumber) {
    int productSum = 0;
    int nonProductSum = 0;
    long workingNumber = cardNumber;
    int i = 1;
    while (workingNumber > 0) {
        int currentNumber = workingNumber % 10;
        workingNumber = workingNumber / 10;
        if (i % 2 == 0) {
            // Multiply every other digit starting from second-to-last digit with 2
            int product = 2 * currentNumber;
            if (product / 10 == 0) {
                productSum += product;
            } else {
                productSum += product % 10;
                productSum += (product / 10) % 10;
            }
            // Add products together
        } else {
            // Sum digits that weren't multiplied
            nonProductSum += currentNumber;
        }
        i++;
    }
    // Add sum together
    printf("%i, %i", productSum, nonProductSum);
    int numbersSum = productSum + nonProductSum;
    // Check if last digit is 0, if it is, it is valid checksum
    return numbersSum % 10 == 0;
}