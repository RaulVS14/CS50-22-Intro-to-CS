#include <stdio.h>
#include "libcs50-10.1.1/src/cs50.h"

int main(void)
{
    // Ask for user input
    string answer = get_string("What's your name?\n");
    // Respond to user with provided input
    printf("Hello, %s!\n", answer);
}