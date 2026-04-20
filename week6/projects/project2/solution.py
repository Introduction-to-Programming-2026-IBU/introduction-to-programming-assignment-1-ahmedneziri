# Project 2 — Number Guessing Game
# Author: your name here

import random

# Generate a random secret number between 1 and 10
secret_number = random.randint(1, 10)

# Set up a guesses counter
guesses = 0

# Get the user's first guess
try:
    guess = int(input("Guess a number between 1 and 10: "))
except ValueError:
    guess = 0 # Fallback to enter the loop if input is not a number
guesses += 1

# While loop — keep asking until the guess is correct
while guess != secret_number:
    # Print "Too low!" or "Too high!" on each wrong guess
    if guess < secret_number:
        print("Too low!")
    elif guess > secret_number:
        print("Too high!")
    
    # Get the next guess and count it
    try:
        guess = int(input("Guess again: "))
    except ValueError:
        print("Invalid input. Please enter a number.")
        continue
        
    guesses += 1

# Print the congratulations message with the number of guesses
print(f"Congratulations! You guessed the secret number in {guesses} guesses.")