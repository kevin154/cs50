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
    // Loop across candidates and check validity
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Valid vote
            ranks[rank] = i; 
            return true;
        }
    }
    // No valid candidate then return false
    return false;
}

// Update preferences given one voter's ranking
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
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
            // Check the candidate with the best overall head to head
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Swap elements in-place
void swap(pair *xp, pair *yp)
{
    pair temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Returns the strength of difference in a pair
int pair_strength(pair p)
{
    return preferences[p.winner][p.loser];
}

// A function to implement bubble sort in descending order
void bubbleSort(pair arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)      
        // Last i elements are already in place   
        for (j = 0; j < n - i - 1; j++) 
            if (pair_strength(arr[j]) < pair_strength(arr[j + 1]))
            {
                swap(&arr[j], &arr[j + 1]);
            }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bubbleSort(pairs, pair_count);        
    return;
}

// Check for cycles in the graph
bool check_cycle(winner, loser)
{
    if (locked[loser][winner])
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // Check what candidates have beaten the winner
        if (locked[i][winner])
        {
            // For candidates that have beaten winner, ensure loser hasn't beaten them
            return check_cycle(i, loser);
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Lock graph if cycle hasnt been created
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner(s) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Variable to keep track of false elements within each column 
        int cnt = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            // Add a count of the falses
            cnt += (locked[j][i] == false);
        }
        // If column has all false then that candidate is the winner
        if (cnt == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}    

