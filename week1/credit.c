// credit.c
// CS50x - Week 1, Problem Set 1
//
// Exercise: Credit Card Validator
// --------------------------------
// Validate a credit card number using Luhn's Algorithm,
// then identify whether it is AMEX, MASTERCARD, VISA, or INVALID.
//
// How to compile:  make credit
// How to run:      ./credit
// How to check:    check50 cs50/problems/2024/x/credit

#include <cs50.h>
#include <stdio.h>

// ---------------------------------------------------------------------------
// Luhn's Algorithm (overview)
// ---------------------------------------------------------------------------
// 1. Starting from the SECOND-TO-LAST digit, multiply every other digit by 2.
// 2. If any product >= 10, add its digits together (e.g. 14 → 1+4 = 5).
// 3. Sum all those results → call it sum_doubled.
// 4. Sum all the OTHER digits (the ones you didn't double) → call it sum_rest.
// 5. If (sum_doubled + sum_rest) % 10 == 0, the number is VALID.
// ---------------------------------------------------------------------------
// Card type detection:
//   AMEX:       15 digits, starts with 34 or 37
//   MASTERCARD: 16 digits, starts with 51–55
//   VISA:       13 or 16 digits, starts with 4
// ---------------------------------------------------------------------------

int main(void)
{
    // Prompt user for credit card number
    long card_number = get_long("Number: ");

    // STEP 1: Count length and extract digits for Luhn's
    int length = 0;
    long temp_card = card_number;
    int sum_doubled = 0;
    int sum_rest = 0;

    while (temp_card > 0)
    {
        int last_digit = temp_card % 10;

        // Luhn's Algorithm logic based on position (0 is last, 1 is second-to-last)
        if (length % 2 == 1) // ODD position (1st, 3rd, 5th from right)
        {
            int doubled = last_digit * 2;
            // If product >= 10, add digits (e.g., 12 -> 1 + 2 = 3)
            sum_doubled += (doubled / 10) + (doubled % 10);
        }
        else // EVEN position (0th, 2nd, 4th from right)
        {
            sum_rest += last_digit;
        }

        temp_card /= 10;
        length++;
    }

    // STEP 2: Check validity via Luhn's Sum
    if ((sum_doubled + sum_rest) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // STEP 3: Identify card type using first digits
    long first_digits = card_number;
    while (first_digits >= 100)
    {
        first_digits /= 10;
    }

    int first_digit = first_digits / 10;

    // Check AMEX: 15 digits, starts with 34 or 37
    if (length == 15 && (first_digits == 34 || first_digits == 37))
    {
        printf("AMEX\n");
    }
    // Check MASTERCARD: 16 digits, starts with 51-55
    else if (length == 16 && (first_digits >= 51 && first_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    // Check VISA: 13 or 16 digits, starts with 4
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
