

scores = []

# Use a for loop to collect 5 scores and append each to the list
for i in range(5):
    while True:
        try:
            score = float(input(f"Enter score {i+1}: "))
            scores.append(score)
            break
        except ValueError:
            print("Invalid input. Please enter a number.")

# Calculate the average using sum() and len()
average = sum(scores) / len(scores)

# Determine the grade with if/elif/else (A/B/C/D/F)
if average >= 90:
    grade = "A"
elif average >= 80:
    grade = "B"
elif average >= 70:
    grade = "C"
elif average >= 60:
    grade = "D"
else:
    grade = "F"

# Print the average (1 decimal place) and the grade
print(f"Average: {average:.1f}")
print(f"Grade: {grade}")