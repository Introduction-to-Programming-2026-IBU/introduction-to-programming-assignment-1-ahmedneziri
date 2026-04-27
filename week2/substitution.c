// substitution.c
// CS50x - Week 2, Problem Set 2
//
// Exercise: Substitution Cipher
// ------------------------------
// Encrypt a message using a 26-character substitution key.
// Each letter in the key maps to the corresponding letter of the alphabet:
//   Key:  VCHPRZGJNTLSKFBDQWAXEUYMOI
//   A→V, B→C, C→H, D→P, E→R, F→Z, ...
//
// Usage:
//   ./substitution KEY    (KEY = 26 unique letters, case-insensitive)
//   ./substitution        → prints usage error
//   ./substitution ABCD   → prints usage error (not 26 chars)
//   ./substitution AABCDE...  → prints usage error (duplicate letters)
//
// How to compile:  make substitution
// How to run:      ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
// How to check:    check50 cs50/problems/2024/x/substitution
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
bool is_valid_key(string key);

int main(int argc, string argv[])
{
    // STEP 1: Validate command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // STEP 2: Get the plaintext from the user
    string plaintext = get_string("plaintext:  ");
    string key = argv[1];

    // STEP 3: Encrypt and print ciphertext
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Find position (0-25), look up in key, ensure uppercase
            int pos = plaintext[i] - 'A';
            printf("%c", toupper(key[pos]));
        }
        else if (islower(plaintext[i]))
        {
            // Find position (0-25), look up in key, ensure lowercase
            int pos = plaintext[i] - 'a';
            printf("%c", tolower(key[pos]));
        }
        else
        {
            // Non-alphabetic characters remain unchanged
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}

// Check if the key is exactly 26 unique alphabetic characters
bool is_valid_key(string key)
{
    int len = strlen(key);
    if (len != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        // Convert char to index 0-25 for the 'seen' array
        int index = tolower(key[i]) - 'a';

        if (seen[index])
        {
            // Already encountered this letter in the key
            return false;
        }

        seen[index] = true;
    }

    return true;
}