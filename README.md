# CS50 Intro to Computer Science

## WEEK 0 - Scratch

### Problem Set 0

[Scratch - CS50x 2022](https://scratch.mit.edu/)

Requirements:
* Your project must use at least two sprites, at least one of which must not be a cat.
* Your project must have at least three scripts total (i.e., not necessarily three per sprite).
* Your project must use at least one conditional, at least one loop, and at least one variable.
* Your project must use at least one custom block that you have made yourself (via Make a Block), which must take at least one input.
* Your project should be more complex than most of those demonstrated in lecture (many of which, though instructive, were quite short) but it can be less complex than Oscartime and Ivy’s Hardest Game.

Once finished with your project, select File > Save now one last time. Then select File > Save to your computer and keep that file so that you can submit it. If prompted by your computer to Open or Save the file, be sure to Save it.

Result: [Skelly's Hell Loop](https://scratch.mit.edu/projects/644202571)

## WEEK 1 - C
### Windows
For local setup download CS50 library:
```
https://github.com/cs50/libcs50
```
Include it in your CMakeLists.txt file
```
add_executable(CS50_22_Intro_to_CS
        "Week 2/hello_world.c"
        "Week 2/libcs50-10.1.1/src/cs50.c")
```
### Linux
```
$ curl -s https://packagecloud.io/install/repositories/cs50/repo/script.deb.sh | sudo bash
$ sudo apt-get install libcs50
```
### Problem Set 1

#### Hello
[Hello - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/1/hello/)

Requirements:

* Get user input
* join input into output string
* output "hello, {input}"

#### Mario
[Mario - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/1/mario/more/)

Requirements:
Program takes input integer between 1 and 8, inclusive
Outputs pyramid corresponding to Mario game
```
   #  #
  ##  ##
 ###  ###
####  ####
```
Height must be the amount entered by user

#### Credit
[Credit - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/1/credit/)

Requirements:
* Get user input long int
* Validate checksum - Luhn’s Algorithm
* Check if card validates to corresponding card rules:
  * // AMEX: 15 digit, 34 || 37
  * // MASTERCARD: 16 digit, starts with 51-55
  * // VISA: 13 || 16, starts with 4

## WEEK 2 - Arrays

### LAB 2
[Lab 2: Scrabble - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/2/)

Requirements:
* Fill in the logic for compute_score function
  * Uses variable named POINTS array for assigning score for each letter in word
  * All characters that are not letters are worth 0 points
  * Lower- and uppercase are worth the equal amount of points
  * Function returns score result for the word provided as argument
* Main function needs to provide output depending on players scores
  * Player 1 wins!
  * Player 2 wins!
  * Tie!

### Problem Set 2

#### Readability
[Readability - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/2/readability/)

Requirements:
* Get user input text
* Count the letters in the text
  * Only letters - no numbers, punctuation or other symbols
  * function name **count_letters**
    * takes argument **string text**
    * returns **int letter_count**
* Count words in the text
  * Word is any sequence of characters separated by space
  * function name count_words
    * takes argument **string text**
    * returns **int word_count**
* Count sentences in the text
  * Sentence ends with ., !, ?
  * function name count_sentences
    * takes **argument string text**
    * returns **int sentence_count**
* Calculate 100 word averages
  * count/nr_words * 100
* Calculate grade using formula
  * index = 0.0588 * letter_avg - 0.296 * sentence_avg - 15.8
* Output result
  * if grade equal or higher than 16 - "Grade 16+"
  * if grade lower than 1 - "Before Grade 1"

#### Substitution
[Substitution - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/2/substitution/)

Requirements:
* Provide key via command-line argument
  * If key not long enough - "Key must contain 26 chars"
  * If the key is missing or too many keys - "Usage: ./substitution key"
  * Validate key
    * Only letters
    * No repeating letters
* Encrypt provided message using the key
  * Prompting for - "plaintext: "
* Return result
  * Prefixed by - "ciphertext: "
  * Case remains same after encryption
  * Only replace alphabetical characters