
import csv

# ── Step 1: Read the CSV and count languages ──────────────────────────────────
counts = {}

with open("../../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # Get the language from the row
        language = row["language"]

        # Update counts — increment if exists, create if new
        if language in counts:
            counts[language] += 1
        else:
            counts[language] = 1

# ── Step 2: Sort by popularity (most popular first) ───────────────────────────
sorted_languages = sorted(counts, key=counts.get, reverse=True)

# ── Step 3: Print the report ──────────────────────────────────────────────────
print("=== Language Popularity Report ===")

# Loop over sorted_languages with enumerate() to get rank numbers (start=1)
# Format each line like: "1. Python  : 196 students"
for rank, language in enumerate(sorted_languages, start=1):
    # Using < to left-align the language name for cleaner formatting
    print(f"{rank}. {language:<10} : {counts[language]} students")

# Print the total number of responses
print(f"\nTotal responses: {sum(counts.values())}")