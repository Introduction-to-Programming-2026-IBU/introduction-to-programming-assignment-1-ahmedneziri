// scrabble.c
// CS50x - Week 2, Problem Set 2
//
// Exercise: Scrabble
// -------------------
// Two players each enter a word. Compute each word's Scrabble score
// and announce the winner (or a tie).
//
// How to compile:  make scrabble
// How to run:      ./scrabble
// How to check:    check50 cs50/problems/2024/x/scrabble
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute scores for each player
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;

    // Loop through each character of word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Check if the character is a letter
        if (isupper(word[i]))
        {
            // Subtract 'A' (65) to get index 0-25
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            // Subtract 'a' (97) to get index 0-25
            score += POINTS[word[i] - 'a'];
        }
        // Non-letter characters are ignored (score stays 0)
    }

    return score;
}