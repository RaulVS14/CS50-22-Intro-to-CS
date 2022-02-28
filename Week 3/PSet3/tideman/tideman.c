#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
        pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // check if valid candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // rank
        int rank = ranks[i];
        // loop ranks to assign relations
        for (int j = i + 1; j < candidate_count; j++)
        {
            int next_rank = ranks[j];
            // update score
            preferences[rank][next_rank]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Avoid checking for self
            if (i != j)
            {
                int candidate_i_score = preferences[i][j];
                int candidate_j_score = preferences[j][i];
                // check if score is bigger, if it is add the pair and update count
                if (candidate_i_score > candidate_j_score)
                {
                    // printf("pair %i: %s to %s: votes - %i\n",pair_count, candidates[i], candidates[j], preferences[i][j]);
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int count = 0;
    while (count < pair_count)
    {
        bool swapped = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int score = preferences[pairs[i].winner][pairs[i].loser];
            int next_score = preferences[pairs[i + 1].winner][pairs[i + 1].loser];
            if (next_score > score)
            {
                pair temp_pair = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp_pair;
                swapped = true;
            }
        }
        count++;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!is_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // check if not looking for self cycle and has arrow pointed to it
            if ((i != j) && locked[j][i])
            {
                // if there is point directed to it, break the loop, because it is clear it's not the source
                source = false;
                break;
            }
        }
        // found single source and stop looking
        if (source)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}

bool is_cycle(int winner, int loser)
{
    // printf("\n%i, %i\n", winner, loser);
    // check for basic cases, element is refering to itself or the element has locked in pair that is already referring to it
    if (winner == loser || locked[loser][winner])
    {
        return true;
    }
    else
    {
        // loop through locked where 0 < i < candidate_count, to find any locked pair that is referencing existing one
        for (int i = 0; i < candidate_count; i++)
        {
            // if existing locked refers to the pair candidate already:
            if (locked[i][winner])
            {
                // run cycle again to check first if any refer to it or it finally reaches loser making it reduced version of the loop winner == loser case;
                if (is_cycle(i, loser))
                {
                    return true;
                }
            }
        }
    }
    // if no matches found in already locked
    return false;
}