#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Output the winner
    string output = "";
    if (score1 > score2)
    {
        output = "Player 1 wins!\n";
    }
    else if (score2 > score1)
    {
        output = "Player 2 wins!\n";
    }
    else
    {
        output = "Tie!\n";
    }
    printf("%s", output);
}

int compute_score(string word)
{
    int score_sum = 0;
    int word_length = strlen(word);
    // Loop through the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // char to lower case
        char letter_to_score = tolower(word[i]);
        int letter_score = 0;
        // Check if character is lowercase letter, will return false if not. Thus not a letter
        if (islower(letter_to_score))
        {
            int position = letter_to_score - 97;
            letter_score = POINTS[position];
        }
        // Add value to sum
        score_sum += letter_score;
    }
    // Return sum
    return score_sum;
}
