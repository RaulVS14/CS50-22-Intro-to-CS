#include <cs50.h>
#include <stdio.h>

int main(void) {
    const int POINTBREAK = 2;
    int points = get_int("How many points did you lose? ");
    if (points < POINTBREAK) {
        printf("You lost fewer points than me.\n");
    } else if (points > POINTBREAK) {
        printf("You lost more points than me.\n");
    } else {
        printf("You lost more points than me.\n");
    }
}