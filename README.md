# CS50 Intro to Computer Science

## WEEK 0 - Scratch

### Problem Set 0

[Scratch - CS50x 2022](https://scratch.mit.edu/)

Requirements:

* Your project must use at least two sprites, at least one of which must not be
  a cat.
* Your project must have at least three scripts total (i.e., not necessarily
  three per sprite).
* Your project must use at least one conditional, at least one loop, and at
  least one variable.
* Your project must use at least one custom block that you have made yourself (
  via Make a Block), which must take at least one input.
* Your project should be more complex than most of those demonstrated in
  lecture (many of which, though instructive, were quite short) but it can be
  less complex than Oscartime and Ivy’s Hardest Game.

Once finished with your project, select File > Save now one last time. Then
select File > Save to your computer and keep that file so that you can submit
it. If prompted by your computer to Open or Save the file, be sure to Save it.

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

#### Mario (More)

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
    * Uses variable named POINTS array for assigning score for each letter in
      word
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

## WEEK 3 - Algorithms

### LAB 3

[Lab 3: Sort - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/3/)

Requirements:

* Run three provided compiled C programs sort1, sort2, sort3
* Determine which sorting algorithm they are running
* Provide answers to answers.txt file

### Problem Set 3

#### Plurality

[Plurality - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/3/plurality/)
Requirements:

* Complete vote function
    * single argument, string name(Candidate name)
    * if a match, increase corresponding vote count
    * returns true or false
* Complete print_winner function
    * print out name of the candidate who received the most votes in the
      election
    * in case of tie print out names of each winning candidates, each on
      separate line

#### Tideman

[Tideman - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/3/tideman/)

* Complete vote function
    * function takes arguments int rank, string name, array ranks
    * updates the ranks array to indicate voter preference
        * ranks[i] represents user i'th preference
    * return true or false
* Complete the record_preference function
    * called for each voter once
    * takes argument array ranks
    * should update global preferences array to add current voter preference
        * preference[i][j] - voters who prefer i candidate over candidate j
* Complete the add_pairs function
    * should add the pair of candidates where one is preferred to other to pairs
      array
    * when tied don't add
    * update global pair_count
* Complete the sort_pairs function
    * sort pairs array in decreasing order of strength of victory
    * if equal order doesn't matter
* Complete the lock_pairs function
    * create locked graph
        * add all edges in decreasing order of victory strength so long as the
          edge would not create a cycle
* Complete the print_winner function
    * print out the name of the candidate who is the source(no arrows lead to
      it) of the graph

## WEEK 4 - Memory

### Lab 4

[Lab 4: Volume - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/4/)

Requirements:

* 3 cmd arguments
    * input - original file
    * output - new file
    * factor - how much original audio should be scaled
* first read and write header to output file
    * number of bytes is defined in HEADER_SIZE
* read rest of data by sample of 2-bytes at a time
    * multiply sample with factor
    * write it to output
* if malloc used
    * must not leak any memory

### Problem Set 4

#### Filter(More)

Requirements

* Implement following functions in helpers.c
    * grayscale
        * should turn image into black and white image
    * reflect
        * should reflect image horizontally
    * blur
        * should turn image into a box-blurred version of the same image
    * edges
        * should highlight edges between objects

#### Recover

Requirements:

* Implement program recover in file called recover/recover.c
    * Accepts 1 command-line argument
        * name of the image from which to recover JPEGs
        * If one is not provided
            * Remind correct usage
            * Return 1
    * If the image cannot be opened
        * inform the user
        * Return 1
    * Files you generate
        * name pattern: ***.jpg
        * *** - three-digit number 000(zero-padded) - %03i
    * If malloc is used
        * must not leak any memory
    * All opened files should be closed

## WEEK 5 - Data structures

### Lab 5

[Lab 5: Inheritance - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/5/)

Requirements

* implement function create_family
    * takes 1 argument
        * int generation
    * should allocate one person for each member of the family of specified
      number of generations
    * returns pointer to the person in the youngest generation
    * each person should have alleles assigned to them
        * oldest generation randomly chosen
        * younger generation should inherit one allele(random) from each parent
    * each person should have parents assigned to them
        * oldest generation should have both parents set to NULL
        * younger generation should have parents array of two pointers, each
          pointing to different parent
    * Functionality logic
        * malloc sizeof(person)
        * generations > 1
            * set parent pointers
            * assign alleles
        * generation == 1
            * no parent pointers
            * random alleles
* implement function free_family
    * accept 1 argument
        * pointer to person
    * then free memory for that person
    * then recursively free memory for all their ancestors
        * free both parents before freeing child
        * free child

### Problem Set 5

#### Speller

[Speller - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/5/speller/)

Requirements:

* Implement load, hash, size, check and unload
    * Effectively as you can use hash table
* Don’t change speller.c or Makefile
* Can alter dictionary.c to complete the implementations
    * Can’t alter declarations
* Check
    * must be case-insensitive
    * return true for words actually in dictionary
    * don’t hardcode common words
    * Possessive is only allowed if it is in dictionary
    * can take only text variable
    * any preprocessed dictionary can’t be saved on disc to improve efficiency
* Assumptions that can be made
    * any dictionary passed will be alphabetically sorted - one word per line,
      each ending with \n
    * Dictionary contains at least one word
    * Words in dictionary won't exceed the LENGTH constant
    * No word will appear twice
    * Each word will contain lowercase alphabetical characters
    * Possibly apostrophes
    * No word will start with apostrophes
    * Check will be passed only words that correspond to required rules, defined
      here before - apostrophe, lowercase, uppercase, alphabetical
* Must not leak any memory, use valgrind
* Hash function should be your own, not from online

## WEEK 6 - Python

### Lab 6

[Lab 6: World Cup - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/6/)

Requirements:

* Complete the implementation of tournament.py
    * Simulates N number of tournaments and outputs each team’s probability of
      winning
    * In _main_ function read team data from CSV
        * Add each team to the list teams
        * File will be provided as a command-line argument
        * Access it using sys.arg[1]
        * Use csv.DictReader for reading
        * By default all values read from the file will be strings
        * Append each team to teams dictionary
    * Implement _simulate_tournament_ function
        * should accept single argument teams as input
        * it is list of teams
        * should repeatedly simulate rounds until you're left with one team
        * returns name of the winner
        * you should not assume the number of teams in the tournament, but you
          may assume it will be a power of 2
    * Implement _simulate_tournament_ in _main_ function
        * run N number of tournament simulations
        * keep track how many times each team wins in the counts dictionary

### Problem Set 6

#### Hello

[Hello - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/6/hello/)

Requirements:

* write program hello.py that prompts for user's name and prints `hello, {name}`

#### Mario (More)

[Mario - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/6/mario/more/)

Requirements:

* Write `mario.py` program
    * recreates half-pyramids using `#`
    * prompts user with `get_int` to get half-pyramid height (1-8, inclusive)
        * if user fails to provide positive integer, re-prompt
    * generate desired half-pyramids(height: 4 hashes, width: 4 hashes(for each
      half-pyramid), gap: 2 spaces)
    * no additional spaces afeter the last set of hashes on each row
    * bottom-left corner aligned with left-hand edge of your terminal window

#### Credit

[Credit - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/6/credit/)

Requirements:

* Implement `credit.py` program
    * prompts user for credit card number
    * prints where it is valid or invalid using Luhn's algorithm and card
      specific parameters
        * AMEX\n - starts with 34 or 37 and is 15 characters long
        * MASTERCARD\n - starts with 51, 52, 53, 54 or 55 and is 16 characters
          long
        * VISA\n - starts with 4 and is 13 or 16 characters long
        * INVALID\n
    * you may assume the user's input will be entirely numeric

#### Readability

[Readability - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/6/readability/)

Requirements:

* Implement `readability.py`
    * prompts user to input some text
        * get_string to capture user input
    * outputs the grade level for the text
        * uses Coleman-Liau index to valuate
        * count letters, words and sentences
            * letter is any character from a to z or A to Z
            * character seperated by spaces count as a word
            * occurrence of period, exclamation point, or question mark
              indicates end of sentence
        * formula: 0.0588 * L - 0.296 * S - 15.8
            * L - average number of letters per 100 words in the text
            * S 0 average number of sentences per 100 words in the text
        * prints value: "Before Grade 1" (<1), "Grade X" (X - rounded to nearest
          integer 1-16) ,"Grade 16+" (>16)

#### DNA

[DNA - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/6/dna/)

Requirements:

* implement `dna.py`
    * program should require
        * first command-line argument the name of a CSV file containing STR
          counts for list of individuals
        * second command-line argument the name of a text file containing the
          DNA sequence to identify
        * if correct number of arguments is provided, you can assume that the
          files provided are correct (structure, name, type)
    * program should print error
        * when command-line argument count is incorrect
    * program should
        * open CSV and read contents into memory
            * you may assume that the first row of CSV will be the column names
            * first column will be word `name` and the remaining columns will be
              the STR sequences themselves
        * open the DNA sequence and read contents into memory
        * compute the longest run of consecutive repeats of the STR in the DNA
          sequence to identify. Utilize the helper function - `longest_match`
        * output name of the matching individual when STR counts match exactly
            * you may assume that STR counts will not match more than one
              individual
        * output `No match`, when STR do not match exactly with any of the
          individuals in the CSV file

## Week 7 - SQL

### Lab 7

[Lab 7: Songs - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/7/)

Requirements:

* **1.sql** - write a SQL query to list **the names of all songs** in the
  database
    * Your query should output a table with a **single column** for the name of
      each song
* **2.sql** - write a SQL query to list **the names of all songs** in **
  increasing order of tempo**
    * Your query should output a table with a **single column** for the name of
      each song****
* **3.sql** - write a SQL query to list **the names of the top 5 longest songs**
  , in **descending order of length**
    * Your query should output a table with a **single column** for the name of
      each song
* **4.sql** - write a SQL query that lists **the names of any songs** that
  have **danceability, energy, and valence greater than 0.75**
    * Your query should output a table with a **single column** for the name of
      each song
* **5.sql** - write a SQL query that returns **the average energy of all the
  songs**
    * Your query should output a table with **a single column and a single row**
      containing the **average energy**
* **6.sql** - write a SQL query that lists **the names of songs that are by Post
  Malone**
    * Your query should output a table with a **single column** for the name of
      each song
    * You **should not make any assumptions** about what **Post Malone’s
      artist_id** is
* **7.sql** - write a SQL query that returns **the average energy of songs that
  are by Drake**
    * Your query should output a table with **a single column and a single row**
      containing the **average energy**
    * You **should not make any assumptions** about what **Drake’s artist_id**
      is
* **8.sql** - write a SQL query that lists **the names of the songs that feature
  other artists**
    * Songs that feature other artists will include **“feat.” in the name of the
      song**
    * Your query should output a table with a **single column** for the name of
      each song

### Problem set 7

#### Movies

[Movies - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/7/movies/)

Requirements:

- In 1.sql, write a SQL query to list the titles of all movies released in 2008.

    - Your query should output a table with a single column for the title of
      each movie.

- In 2.sql, write a SQL query to determine the birth year of Emma Stone.

    - Your query should output a table with a single column and a single row (
      not including the header) containing Emma Stone's birth year.

    - You may assume that there is only one person in the database with the name
      Emma Stone.

- In 3.sql, write a SQL query to list the titles of all movies with a release
  date on or after 2018, in alphabetical order.

    - Your query should output a table with a single column for the title of
      each movie.

    - Movies released in 2018 should be included, as should movies with release
      dates in the future.

- In 4.sql, write a SQL query to determine the number of movies with an IMDb
  rating of 10.0.

    - Your query should output a table with a single column and a single row (
      not including the header) containing the number of movies with a 10.0
      rating.

- In 5.sql, write a SQL query to list the titles and release years of all Harry
  Potter movies, in chronological order.

    - Your query should output a table with two columns, one for the title of
      each movie and one for the release year of each movie.

    - You may assume that the title of all Harry Potter movies will begin with
      the words "Harry Potter", and that if a movie title begins with the
      words "Harry Potter", it is a Harry Potter movie.

- In 6.sql, write a SQL query to determine the average rating of all movies
  released in 2012.

    - Your query should output a table with a single column and a single row (
      not including the header) containing the average rating.

- In 7.sql, write a SQL query to list all movies released in 2010 and their
  ratings, in descending order by rating. For movies with the same rating, order
  them alphabetically by title.

    - Your query should output a table with two columns, one for the title of
      each movie and one for the rating of each movie.

    - Movies that do not have ratings should not be included in the result.

- In 8.sql, write a SQL query to list the names of all people who starred in Toy
  Story.

    - Your query should output a table with a single column for the name of each
      person.

    - You may assume that there is only one movie in the database with the title
      Toy Story.

- In 9.sql, write a SQL query to list the names of all people who starred in a
  movie released in 2004, ordered by birth year.

    - Your query should output a table with a single column for the name of each
      person.

    - People with the same birth year may be listed in any order.

    - No need to worry about people who have no birth year listed, so long as
      those who do have a birth year are listed in order.

    - If a person appeared in more than one movie in 2004, they should only
      appear in your results once.

- In 10.sql, write a SQL query to list the names of all people who have directed
  a movie that received a rating of at least 9.0.

    - Your query should output a table with a single column for the name of each
      person.

    - If a person directed more than one movie that received a rating of at
      least 9.0, they should only appear in your results once.

- In 11.sql, write a SQL query to list the titles of the five highest rated
  movies (in order) that Chadwick Boseman starred in, starting with the highest
  rated.

    - Your query should output a table with a single column for the title of
      each movie.

    - You may assume that there is only one person in the database with the name
      Chadwick Boseman.

- In 12.sql, write a SQL query to list the titles of all movies in which both
  Johnny Depp and Helena Bonham Carter starred.

    - Your query should output a table with a single column for the title of
      each movie.

    - You may assume that there is only one person in the database with the name
      Johnny Depp.

    - You may assume that there is only one person in the database with the name
      Helena Bonham Carter.

- In 13.sql, write a SQL query to list the names of all people who starred in a
  movie in which Kevin Bacon also starred.

    - Your query should output a table with a single column for the name of each
      person.

    - There may be multiple people named Kevin Bacon in the database. Be sure to
      only select the Kevin Bacon born in 1958.

    - Kevin Bacon himself should not be included in the resulting list.

#### Fiftyville

[Fiftyville - CS50x 2022](https://cs50.harvard.edu/x/2022/psets/7/fiftyville/)
[SQL style guide indentation](https://www.sqlstyle.guide/#indentation)

Requirements:

- Solve the mystery using security logs

- Log your SQL queries in log.sql

    - Add labels for queries as a comments:--

    - Explain why you are running that query and what information you are hoping
      to get

    - You can add additional notes on the thought process

    - Indent your queries, as they may get complex

- Add answers to answers.txt file by filling in the blanks

- Recent theft took place in Humphrey Street, on 28th July

## Week 8 - HTML, CSS, JavaScript

### Lab 8

[Lab 8: Trivia - CS50x 2022](https://cs50.harvard.edu/x/2022/labs/8/)

Requirements:
* Part 1
    * use h3 heading for question text
    * button for each possible answer choices
        * at least 3
        * 1 correct
    * add JS logic
        * clicked on incorrect answer, button should turn red and display text beneath the question “Incorrect”
        * clicked on the correct answer, button should turn green and display text beneath the question“Correct!”
* Part 2
    * add part 2 question for text-based answer
        * use h3 heading for question
        * input field for user response
        * button to confirm their answer
    * add JS logic that validates user answer after confirmation
        * the text field should turn red, and display text beneath the question “Incorrect”
        * the text field should turn green and display text beneath the question “Correct!”
* Additionally you can
    * Edit styles.css
    * Add additional trivia questions
