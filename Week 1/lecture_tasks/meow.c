#include <cs50.h>
#include <stdio.h>

void multiMeow(int count);

void meow(void) {
    printf("meow\n");
}

int main(void) {
    multiMeow(20);
}

void multiMeow(int count) {
    int i = 0;
    while (i <= count) {
        meow();
        i++;
    }
}