import sys
from cs50 import get_string
import re


def get_letter_count(text):
    # Counts number of letters in text, using built in method .isalpha()
    letter_count = 0
    for i in text:
        if i.isalpha():
            letter_count += 1
    return letter_count


def get_word_count(text):
    # Count words in text. Spaces and end of text will count as a delimiter for words
    word_count = 0
    for i, letter in enumerate(text):
        if letter.isspace() or (len(text) != 0 and i == len(text) - 1):
            word_count += 1
    return word_count


def get_sentence_count(text):
    # Count sentences in text. [!.?] are used as sentences delimiters
    sentence_count = 0
    for i, letter in enumerate(text):
        if letter == "!" or letter == "." or letter == "?":
            sentence_count += 1
    return sentence_count


def calculate_score(avg_letters, avg_sentences):
    # Calculates text score based on Coleman-Liau
    return round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)


def get_grade(score):
    # Evaluates Coleman-Liau score to grade
    if (score > 16):
        return "Grade 16+"
    elif (score >= 1 and score <= 16):
        return "Grade {}".format(score)
    else:
        return "Before Grade 1"


def get_hundred_word_avg(count, nr_of_words):
    return count / nr_of_words * 100.0


def get_grade_for_text(text):
    # Find counts required for the score calculation
    letter_count = get_letter_count(text)
    word_count = get_word_count(text)
    sentence_count = get_sentence_count(text)
    #  Calculate 100 word average counts
    letter_hundred_avg = get_hundred_word_avg(letter_count, word_count)
    sentences_hundred_avg = get_hundred_word_avg(sentence_count, word_count)
    # Calculate score based on Coleman-Liau
    score = calculate_score(letter_hundred_avg, sentences_hundred_avg)
    return get_grade(score)


def main():
    input_text = get_string("Text: ")
    print(get_grade_for_text(input_text))


if __name__ == "__main__":
    main()
    sys.exit(0)
