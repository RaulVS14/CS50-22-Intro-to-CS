#include "../../../libcs50-10.1.1/src/cs50.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    long cardNumber = 0;
    do
    {
        cardNumber = get_long("Number: ");
        printf("%l", get_long("Number: "));
    }
    while (cardNumber < 1);
    // Calculate checksum
    int productSum = 0;
    int nonProductSum = 0;
    long workingNumber = cardNumber;
    int i = 0;
    string result = "INVALID";
    while (workingNumber > 0)
    {
        int currentNumber = workingNumber % 10;
        workingNumber = workingNumber / 10;
        if (i % 2 == 1)
        {
            // Multiply every other digit starting from second-to-last digit with 2
            int product = 2 * currentNumber;
            if (product / 10 == 0)
            {
                productSum += product;
            }
            else
            {
                productSum += product % 10;
                productSum += (product / 10) % 10;
            }
            // Add products together
        }
        else
        {
            // Sum digits that weren't multiplied
            nonProductSum += currentNumber;
        }
        i++;
    }

    // Add sum together
    int numbersSum = productSum + nonProductSum;
    // Check if last digit is 0, if it is, it is valid checksum
    // Check length and starting digits

    // AMEX: 15 digit, 34 || 37
    // MASTERCARD: 16 digit, starts with 51-55
    // VISA: 13 || 16, starts with 4
    // Get card number from input
    if (numbersSum % 10 == 0)
    {
        // Calculate powers for division to find first and second number
        long lengthFirst = pow(10, (i - 1));
        long lengthSecond = pow(10, (i - 2));
        // Calculate first and second number
        int firstNr = cardNumber / lengthFirst;
        int secondNr = (cardNumber / lengthSecond) % 10;
        if (i == 15 && firstNr == 3 && (secondNr == 4 || secondNr == 7))
        {
            // CHECK FOR AMEX
            result = "AMEX";
        }
        else if ((i == 16 || i == 13) && firstNr == 4)
        {
            // CHECK FOR VISA
            result = "VISA";
        }
        else if (i == 16 && firstNr == 5 && (secondNr >= 1 && secondNr <= 5))
        {
            // CHECK FOR MASTERCARD
            result = "MASTERCARD";
        }
    }

    // Print card
    printf("%s\n", result);

}
