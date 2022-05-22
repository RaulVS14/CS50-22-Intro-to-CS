import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = []
    sub_sequences = []
    with open(sys.argv[1]) as f:
        csv_reader = csv.DictReader(f)
        sub_sequences = csv_reader.fieldnames[1:]
        for row in csv_reader:
            for sub_sequence in sub_sequences:
                row[sub_sequence] = int(row[sub_sequence])
            database.append(row)
    # Read DNA sequence file into a variable
    sequence = ''
    with open(sys.argv[2]) as f:
        sequence = f.readline().strip()

    # Find longest match of each STR in DNA sequence
    longest_sequences = {}
    for sub_sequence in sub_sequences:
        longest_sequences[sub_sequence] = longest_match(sequence, sub_sequence)

    # Check database for matching profiles
    match = False
    for entry in database:
        is_match = True
        for sub_sequence in sub_sequences:
            if entry[sub_sequence] != longest_sequences[sub_sequence]:
                is_match = False
                break
        if is_match:
            match = entry
    if match:
        print('{}'.format(match.get('name')))
    else:
        print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
