#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float get_100_word_avg(int count, int nr_of_words);
int get_grade(int letter_count, int sentence_count, int word_count);

int main(void)
{
    // Get user input
    string text = get_string("Text: ");
    // Get letters count
    int letter_count = count_letters(text);
    // Get words count
    int word_count = count_words(text);
    // Get sentence count
    int sentence_count = count_sentences(text);
    // Calculate grade
    int grade = get_grade(letter_count, sentence_count, word_count);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    // printf("%i %i %i Grade: %i\n", letter_count, word_count, sentence_count, grade);
}

int count_letters(string text)
{
    int letter_count = 0;
    // Loop through text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char text_element = text[i];
        // Increase count when char is letter
        if (isalpha(text_element))
        {
            letter_count++;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 0;
    // Loop through text
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        char text_element = text[i];
        // Check if char is space or null
        if (isspace(text_element) || i == n)
        {
            word_count ++;
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    int sentence_count = 0;
    // Loop through text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char text_element = text[i];
        // Check if character is punctuation
        if (text_element == '!' || text_element == '.' || text_element == '?')
        {
            sentence_count ++;
        }
    }
    return sentence_count;
}

float get_100_word_avg(int count, int nr_of_words)
{
    return count / (float)nr_of_words * 100.0;
}

int get_grade(int letter_count, int sentence_count, int word_count)
{
    return round(0.0588 * get_100_word_avg(letter_count, word_count) - 0.296 * get_100_word_avg(sentence_count, word_count) - 15.8);
}