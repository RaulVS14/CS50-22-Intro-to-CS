#include <stdio.h>
#include <cs50.h>

int main(void) {
    // Ask for user input
    string answer = get_string("What's your name?\n");
    // Respond to user with provided input
    printf("Hello, %s!\n", answer);
}