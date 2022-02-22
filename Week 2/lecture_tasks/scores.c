#include <stdio.h>
#include "cs50.h"
int main(void)
{
    int n = get_int("How many scores? ");
    int scores[n];
    int totalScore = 0;
    for(int i = 0; i < n; i++)
    {
        scores[i] = get_int("Score: ");
        totalScore += scores[i];
    }

    printf("AVG: %f\n)", (totalScore) / (float)n);
}