#include "cs50.h"
#include "ctype.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

 
void meow();
void wusyaname(void);
void isBigger(void);

void print_column(int h);
void print_scores_variant(int amount);
float arr_avg(int lenght, int arr[]);
void print_scores(void);
int string_length(string s);
void uppercase_string(void);
void monopoly_characters(void);
void phone_book(void);
void draw(int n);
void try_malloc(void);
void swap(int* a, int* b);

typedef struct
{
    string name;
    string number;
} person;

//hw1:
void stair_way_to_heaven1();
void stair_way_to_heaven2();
void giveChange();
bool is_valid_luhn(long long n);
void credit();
    
//hw2:
int letter_points(char c);
void scrabble(void);
void readability(void);
void ceasar_salad(int key);
bool legit_substitution(string s);
int alpha_index(char c);
void substitution(string key);
void useless_shit(string key);


/*
int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        printf("Usage: ./program key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    ceasar_salad(key);
   
   

}
 */

/*
int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2 || !legit_substitution(key))
    {
        printf("Usage: ./program key\n");
        return 1;
    }
    useless_shit(key);
    substitution(key);
    return 0;
}
*/

//hw3:-----------------------------------------------------------------------------------------------------------
void plurality(string arr[], int n);
bool isExist(string arr[], string s, int n);
bool vote1(int voter, int rank, string name);
void tabulate();
bool print_winner1();
int find_min();
bool is_tie(int min);
bool eliminate(int min);
void runoff();
bool vote2(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs();
void sort_pairs();
void merge_sort_rf(int left, int right);
void merge_rf(int left, int mid, int right);
void lock_pairs();
bool creates_cycle(int winner, int loser);
void print_winner2();
void tideman();


/*
int main(int argc, string argv[])
{
    if (argc <= 3)
    {
        printf("Usage: ./program key\n");
        return 1;
    }
    
    
    string* arr = malloc((argc - 1) * sizeof(string));  // Correct

    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = argv[i];
    }
    
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < argc - 1; i++)
    {
        printf("Candidate %d: %s\n", i + 1, arr[i]);
    }

    plurality(arr, argc - 1);

    free(arr);
    return 0;
}
*/

/*
int main(int argc, string argv[])
{
    if (argc <= 3)
    {
        printf("Usage: ./program key\n");
        return 1;
    }

    candidate_count = argc - 1;

    for (int i = 0; i < argc - 1; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    if (candidates == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        printf("Candidate %d: %s\n", i + 1, candidates[i].name);
    }

    printf("\n");
    printf("\n");
    runoff();
}

*/

typedef struct
{
    string name;
    int votes;
} election;

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

typedef struct
{
    int winner;
    int loser;
}
pair;

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
#define MAX_RUNOFF 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];
bool locked[MAX_VOTERS][MAX_CANDIDATES];

candidate candidates[MAX_RUNOFF];
pair pairs[MAX_RUNOFF * (MAX_RUNOFF - 1) / 2];

// Number of candidates
int candidate_count;
int pair_count;
int voter_count;

/*
int main(int argc, string argv[])
{
    if (argc <= 3)
    {
        printf("Usage: ./program key\n");
        return 1;
    }

    candidate_count = argc - 1;

    for (int i = 0; i < argc - 1; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        printf("Candidate %d: %s\n", i + 1, candidates[i].name);
    }

    printf("\n");
    printf("\n");

    tideman();

}
*/

int main(int argc, string argv[])
{
    FILE* file = fopen("phonebook.csv", "a");

    char *name = get_string("Enter name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s,%s\n", name, number);

    fclose(file); 
 
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;

}

void try_malloc()
{
    char* s = get_string("s: ");
    char* t = malloc(strlen(s) + 1);

    if (t == NULL)
    {
        printf("problem with allocation nigga\n");
        return 1;
    }

    //strcpy(t, s);


    if (strlen(s) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("\n");
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
}

bool vote2(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
   
}

void add_pairs()
{
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j; 
                    pair_count++;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
           
        }
    } 
}

void sort_pairs()
{
    merge_sort_rf(0, pair_count - 1);
}

void merge_sort_rf(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort_rf(left, mid);
        merge_sort_rf(mid + 1, right);
        merge_rf(left, mid, right);
    }
}

void merge_rf(int left, int mid, int right)
{
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Create temporary arrays
    pair* left_arr = malloc(left_size * sizeof(pair));
    pair* right_arr = malloc(right_size * sizeof(pair));

    // Copy data to temp arrays
    for (int i = 0; i < left_size; i++)
        left_arr[i] = pairs[left + i];
    for (int j = 0; j < right_size; j++)
        right_arr[j] = pairs[mid + 1 + j];

    // Merge the temp arrays back into pairs[left..right]
    int i = 0;     // Initial index of left subarray
    int j = 0;     // Initial index of right subarray  
    int k = left;  // Initial index of merged subarray

    while (i < left_size && j < right_size)
    {
        // Compare by margin of victory (descending order)
        int left_margin = preferences[left_arr[i].winner][left_arr[i].loser];
        int right_margin = preferences[right_arr[j].winner][right_arr[j].loser];

        if (left_margin >= right_margin)
        {
            pairs[k] = left_arr[i];
            i++;
        }
        else
        {
            pairs[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left_arr[]
    while (i < left_size)
    {
        pairs[k] = left_arr[i];
        i++;
        k++;
    }

    // Copy remaining elements of right_arr[]
    while (j < right_size)
    {
        pairs[k] = right_arr[j];
        j++;
        k++;
    }

    free(left_arr);
    free(right_arr);
}

void lock_pairs()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }       
    }

}

bool creates_cycle(int winner, int loser)
{
    if (winner == loser) return true;
    

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) 
        {
            if(creates_cycle(winner, i))
            return true;
        }
    }

    return false;
}

void print_winner2()
{
 

    for (int j = 0; j < candidate_count; j++)
    {
        bool is_source = true;

        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                is_source = false;
                break;
            }
        }

        if (is_source)
        {
            printf("Winner is: %s\n", candidates[j].name);
            return;
        }
    }
}

void tideman()
{
    do
    {
        voter_count = get_int("number of voters: ");
    } while (voter_count < 1 || voter_count > MAX_VOTERS);

    int ranks[3];

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            string s;
            do
            {
                s = get_string("Rank %i: ", j + 1);
            } while (!vote2(j, s, ranks));
        }
        printf("\n");
        record_preferences(ranks);
    }

    
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner2();
}


void runoff()
{
    do
    {
        voter_count = get_int("number of voters: ");
    } while (voter_count < 1 || voter_count > MAX_VOTERS);


    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            string s;
            do
            {
                s = get_string("Rank %i: ", j + 1);
            } while (!vote1(i, j, s));

        }
        printf("\n");

    }

    // Initial tabulation
    tabulate();

    // Check for immediate winner
    if (print_winner1())
    {
        return;
    }

    // Runoff rounds
    while (true)
    {
        // Eliminate and recalculate
        int min = find_min();

        // Check for tie before eliminating
        if (is_tie(min))
        {
            printf("TIE between remaining candidates!\n");
            return;
        }

        eliminate(min);

        // Reset votes and tabulate
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
        tabulate();

        // Check for winner
        if (print_winner1())
        {
            return;
        }
    }

}


bool vote1(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

//i is the collum / voters
//j is the row / rank
void tabulate()
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];

            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

bool print_winner1()
{
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        count += candidates[i].votes;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (count / 2))
        {
            printf("Winner: %s\n", candidates[i].name);
            return true;
        }
           
    }
    return false;
}

int find_min()
{
    int min = candidates[0].votes;

    for (int i = 0; i < candidate_count; i++)
    {
        if (min > candidates[i].votes && !candidates[i].eliminated)
            min = candidates[i].votes;
    }
    return min;
}

bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }
    return true;
}


bool eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
            candidates[i].eliminated = true;
    }
}



//arr is the array of candidates
//num_cans is the number of candidates
void plurality(string arr[],int num_cans)
{
    int voters = get_int("number of voters: ");

    election* elects = malloc(num_cans * sizeof(election));

    int count = 0;
    int index = 0;

    for (int i = 0; i < num_cans; i++)
    {
        elects[i].name = arr[i];
        elects[i].votes = 0;
    }

    for (int i = 0; i < voters; i++)
    {
        string s;
        do
        {
            s = get_string("Vote: ");

        } while (!isExist(arr,s, num_cans));


        for (int j = 0; j < num_cans; j++)
        {
            if (strcmp(elects[j].name, s) == 0)
            {
                elects[j].votes++;
                break;
            }
                
        }
    }

    int max = 0;

    for (int i = 0; i < num_cans; i++)
    {
        if (elects[i].votes > max)
        {
            max = elects[i].votes;
            index = i;
        }
    }

    printf("Candidates: [");
    for (int i = 0; i < num_cans; i++)
    {
        printf("%s", elects[i].name);
        if (i < num_cans - 1)
            printf(", ");
    }
    printf("]\n");

    printf("Votes: [");
    for (int i = 0; i < num_cans; i++)
    {
        printf("%d", elects[i].votes);
        if (i < num_cans - 1)
            printf(", ");
    }
    printf("]\n");

    printf("\nWinner: %s\n", elects[index].name);
    free(elects);
}

bool isExist(string arr[],string s, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(s, arr[i]) == 0) 
        {
            return true;
        }
    }
    return false;
}

void draw(int n)
{
    if (n <= 0)
    {
        return;
    }

    draw(n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}

void phone_book()
{
    person ppl[3] = {
       {"Alice", "123-456-7890"},
       {"Bob", "987-654-3210"},
       {"Charlie", "555-123-4567"}
    };

    string s = get_string("enter name: ");

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(ppl[i].name, s) == 0)
        {
            printf("Found: %s\n", ppl[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;

}

void monopoly_characters()
{
    string strings[] = { "battleship" , "boot", "cannon", "iron", "thimble", "top hat" };

    string s = get_string("String: ");

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found\n");
            return 0;
        }

    }
    printf("Not found\n");
    return 1;
}

void useless_shit(string key)
{

    printf("\nkey: %s\n", key);

    printf("[");
    for (int i = 0; i < 25; i++)
    {
        printf("%c,", key[i]);
    }
    printf("%c]\n", key[25]);

    printf("[");
    for (int i = 0; i < 25; i++)
    {
        printf("%c,", 'A' + i);
    }
    printf("%c]\n\n", 'Z');
}



bool legit_substitution(string s)
{       
    if (strlen(s) != 26) { return false; }
  
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        
        for (int j = i + 1; j < 26; j++)
        {
            if (toupper(s[i]) == toupper(s[j]))
            {
                return false;
            }
        }
    }

    return true;

}

int alpha_index(char c)
{
    char alphabet[26];

    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = 'A' + i;
    }

    for (int i = 0; i < 26; i++)
    {
        if (toupper(c) == alphabet[i])
        {
            return i;
        }
    }

    return -1;  

}

void substitution(string key)
{
    string p_text = get_string("plaintext: ");
    int length = strlen(p_text);

    char* c_text = malloc(length + 1);

    if (c_text == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < length; i++)
    {
        int index = alpha_index(p_text[i]);
        
            if (islower(p_text[i])) 
            {
                c_text[i] = tolower(key[index]);
            }
            else if(isupper(p_text[i]))
            {
                c_text[i] = toupper(key[index]);
            }
        
            else
            {
            c_text[i] = p_text[i];
            }
        
    }

    c_text[length] = '\0';
    printf("ciphertext: %s\n", c_text);

    free(c_text);

}

void ceasar_salad(int key)
{
    string p_text = get_string("instert plain text: ", "\n");
    int length = strlen(p_text);

    char* c_text = malloc(length + 1);

    if (c_text == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < length; i++)
    {
        if (isalpha(p_text[i]))
        {
            if (isupper(p_text[i]))
            {
                c_text[i] = ((p_text[i] - 'A' + key) % 26) + 'A';
            }
            else if (islower(p_text[i]))
            {
                c_text[i] = ((p_text[i] - 'a' + key) % 26) + 'a';
            }
            else
            {
                c_text[i] = p_text[i];
            }
        }
    }

    c_text[length] = '\0';

    printf("ciphertext: %s\n", c_text);

    free(c_text);
    return 0;
}


    void readability()
    {
        string text = get_string("instert text: ");

        int letters = 0;
        int spaces = 0;
        int sentences = 0;

        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (isalpha(text[i])) 
            {
                letters++;
            }
            if (text[i] == ' ')
            {
                spaces++;
            }
            if(text[i] == '!' || text[i] == '.' || text[i] == '?')
            {
                sentences++;
            }
        }
        int words = spaces + 1;

        float L = (float) letters / words * 100;
        float S = (float) sentences / words * 100;

        int index = round(0.0588 * L - 0.296 * S - 15.8);

        if (index >= 16)
        {
            printf("Grade 16+\n");
        }
        else if(index < 1)
        {
            printf("Before Grade 1\n");
        }
        else
        {
            printf("Grade %i\n", index);
        }
    }

void scrabble()
{
    string s1 = get_string("Player 1: ");
    string s2 = get_string("Player 2: ");

    int score1 = 0;
    int score2 = 0;

    int big = (strlen(s1) > strlen(s2)) ? strlen(s1) : strlen(s2);
    for (int i = 0; i < big; i++)
    {
        score1 += letter_points(s1[i]);
        score2 += letter_points(s2[i]);
    }

    if (score1 > score2)
    {
        printf("Player 1 wins! the score is: %i \n", score1);
    }
    else if(score1 < score2)
    {
        printf("Player 2 wins! the score is: %i \n", score2);
    }
    else
    {
        printf("Tie! the score is: %i\n", score1);
    }

}


int letter_points(char c)
{
    char alphabet[26];

    for (int i = 0; i < 26; i++) 
    {
        alphabet[i] = 'A' + i; 
    }

    int scrabblePoints[26] = {
        1,  // A
        3,  // B
        3,  // C
        2,  // D
        1,  // E
        4,  // F
        2,  // G
        4,  // H
        1,  // I
        8,  // J
        5,  // K
        1,  // L
        3,  // M
        1,  // N
        1,  // O
        3,  // P
        10, // Q
        1,  // R
        1,  // S
        1,  // T
        1,  // U
        4,  // V
        4,  // W
        8,  // X
        4,  // Y
        10  // Z
    };  

    int n = 0;

    for (int i = 0; i < 26; i++)
    {
        if (alphabet[i] == toupper(c)) 
        {
            n = scrabblePoints[i];
        }
    }
    return n;
}

void uppercase_string()
{
    string s = get_string("Before: ");
    printf("After:  ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            //diffrence between uppercase and lower case letters is 32, u can also use 'a' - 'A'
            printf("%c", s[i] - 32);
        }
        else
        {
            printf("%c", s[i]);
        }
    }
}

int string_length(string s)
{
    int n = 0;

    while (s[n] != '\0')
    {
        n++;
    }

    return n;
}




void print_scores()
{
    enum { N = 3 };
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Avg: %f\n", arr_avg(N, scores));
}

float arr_avg(int lenght, int arr[])
{
    int sum = 0;
    for (int i = 0; i < lenght; i++)
    {
        sum += arr[i];
    }
    return sum / (float)lenght;
}


void print_scores_variant(int num)
{
    int scores = 0;

    for (int i = 0; i < num; i++)
    {
        scores += get_int("instert score number: %i\n", i + 1);
    }

    printf("Average: %f\n", scores / (float)num);
}

void print_column(int height)
{
    for (int i = 0; i < height; i++)
    {
        printf("#\n");
    }
}

bool is_valid_luhn(long long n)
{
    int sum = 0;
    bool alt = false;

    while (n > 0)
    {
        int digit = n % 10;
        if (alt)
        {
            digit *= 2;
            sum += (digit / 10) + (digit % 10);
        }
        else
        {
            sum += digit;
        }
        alt = !alt;
        n /= 10;
    }
    return(sum % 10 == 0);
}

void credit()
{
    long long n = get_long_long("hello my name is pattel, pls give your credit card number: ");
    string bad = "INVALID\n";

    if (!is_valid_luhn(n))              
    {
        printf(bad);
    }
    else
    {
        long long hold = n;
        int count = 0;

        while (hold > 0)
        {
            hold /= 10;
            count++;
        }
        printf("count is: %d\n", count);
        hold = n;

        long long first_two = n;
        while (first_two > 100)
        {
            first_two /= 10;
        }

        long long first_digit = first_two / 10;

        printf("first two digits: %lld\n", first_two);
        printf("first digit: %lld\n", first_digit);

        if (count == 15 && (first_two == 34 || first_two == 37))
        {
            printf("American Express");
        }
        else if (count == 16 && (first_two >= 51 || first_two <= 55))
        {
            printf("MasterCard");
        }
        else if ((count == 13 || count == 16) && first_digit == 4)
        {
            printf("Visa");
        }
        else
        {
            printf(bad);
        }
    }

}

void giveChange()
{
    int num;
    do
    {
        num = get_int("how much we owe u? "); 
    } 
    while (num < 0);
  
    int hold = 0;

    while (num > 0) 
    {
        if (num >= 25)
        {
            num -= 25;
        }
        else if (num >= 10)
        {
            num -= 10;
        }
        else if (num >= 5)
        {
            num -= 5;
        }
        else if (num >= 1)
        {
            num -= 1;
        }
        hold++;
    }
    
    printf("%i", hold);
}


void stair_way_to_heaven1()
{
    int hight;

    do
    {
        // Get valid input
        hight = get_int("how high are you? ");

    } while (hight < 1);

    // Build each row
    for (int row = 1; row <= hight; row++)
    {
        // Left spaces
        for (int s = 0; s < hight - row; s++)
        {
            printf(" ");
        }

        // Left hashes
        for (int h = 0; h < row; h++)
        {
            printf("#");
        }

        // Newline after each row
        printf("\n");

        
    }

}

void stair_way_to_heaven2()
{
    int hight;

    do
    {
        // Get valid input
        hight = get_int("how high are you? ");

    } while (hight < 1);

    // Build each row
    for (int row = 1; row <= hight; row++)
    {
        // Left spaces
        for (int s = 0; s < hight - row; s++)
        {
            printf(" ");
        }

        // Left hashes
        for (int h = 0; h < row; h++)
        {
            printf("#");
        }

        // Gap
        printf("");

        // Right hashes
        for (int h = 0; h < row; h++)
        {
            printf("#");
        }

        // Newline after each row
        printf("\n");


    }

}


void meow()
{
    int n;
    do
    {
        n = get_int("give number: ");
    } 
    while (n < 1);
    
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}

void wusyaname(void)
{
    string name = get_string("wusyaname girl friend? ");
    printf("hey, %s!", name);
}

void isBigger(void)
{
    int x = get_int("whats x? ");
    int y = get_int("whats y? ");

    if (x != y)
    {
        if (x > y)
        {
            printf("x is bigger than \n");
        }
        else
        {
            printf("y is bigger thann x\n");
        }
    }
    else
    {
        printf("x equals y");
    }
}
