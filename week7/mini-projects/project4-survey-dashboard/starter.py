
import csv
import sqlite3

# ══════════════════════════════════════════════════════════════════════════════
# STEP 1 — CREATE THE DATABASE AND TABLE
# (Coder A)
# ══════════════════════════════════════════════════════════════════════════════

conn = sqlite3.connect("survey.db")
db   = conn.cursor()

# Create the responses table if it doesn't already exist
db.execute('''
CREATE TABLE IF NOT EXISTS responses (
    student_id TEXT, 
    faculty TEXT, 
    year INTEGER,
    satisfaction INTEGER, 
    favourite_tool TEXT, 
    comments TEXT
)
''')

csv_files = [
    "faculty_science.csv",
    "faculty_arts.csv",
    "faculty_business.csv",
]

for filename in csv_files:
    try:
        with open(filename, "r") as file:
            reader = csv.DictReader(file)
            for row in reader:
                # Insert each row into the responses table using placeholders
                db.execute(
                    "INSERT INTO responses VALUES (?, ?, ?, ?, ?, ?)", 
                    (
                        row["student_id"], 
                        row["faculty"], 
                        row["year"], 
                        row["satisfaction"], 
                        row["favourite_tool"], 
                        row["comments"]
                    )
                )
    except FileNotFoundError:
        print(f"Warning: {filename} not found. Skipping.")

conn.commit()
print("Database loaded successfully.\n")


# ══════════════════════════════════════════════════════════════════════════════
# STEP 3 — DASHBOARD QUERIES
# ══════════════════════════════════════════════════════════════════════════════

print("=" * 30)
print("  UNIVERSITY SURVEY DASHBOARD")
print("=" * 30)

# ── Query 1: Total responses by faculty (Coder B) ────────────────────────────
print("\n1. Total Responses by Faculty")

rows = db.execute("SELECT faculty, COUNT(*) AS n FROM responses GROUP BY faculty ORDER BY faculty").fetchall()
total = 0
for row in rows:
    faculty_name = row[0]
    count = row[1]
    print(f"   {faculty_name:<10}: {count}")
    total += count

print(f"   {'TOTAL':<10}: {total}")


# ── Query 2: Average satisfaction by year (Coder B) ──────────────────────────
print("\n2. Average Satisfaction by Year of Study")

rows = db.execute("SELECT year, ROUND(AVG(satisfaction), 1) AS avg_sat FROM responses GROUP BY year ORDER BY year").fetchall()
for row in rows:
    print(f"   Year {row[0]} : {row[1]} / 5")


# ── Query 3: Favourite tool popularity (Coder B) ─────────────────────────────
print("\n3. Favourite Tool Popularity")

rows = db.execute("SELECT favourite_tool, COUNT(*) AS n FROM responses GROUP BY favourite_tool ORDER BY n DESC").fetchall()
for row in rows:
    print(f"   {row[0]:<15}: {row[1]:>3}")


# ── Query 4: Faculty comparison table (Coder C) ──────────────────────────────
print("\n4. Faculty Comparison")
print(f"   {'Faculty':<12} | {'Avg Satisfaction':<18} | Most Popular Tool")
print("   " + "-" * 50)

faculties = ["Arts", "Business", "Science"]
for faculty in faculties:
    # Query average satisfaction for this faculty
    avg_row = db.execute(
        "SELECT ROUND(AVG(satisfaction), 1) AS avg FROM responses WHERE faculty = ?",
        (faculty,)
    ).fetchone()

    # Query the most popular tool for this faculty
    tool_row = db.execute('''
        SELECT favourite_tool 
        FROM responses 
        WHERE faculty = ? 
        GROUP BY favourite_tool 
        ORDER BY COUNT(*) DESC 
        LIMIT 1
    ''', (faculty,)).fetchone()

    avg_score = avg_row[0] if avg_row and avg_row[0] is not None else 0.0
    top_tool = tool_row[0] if tool_row else "None"
    
    print(f"   {faculty:<12} | {avg_score:<18} | {top_tool}")


# ── Query 5: Interactive filter (Coder C) ────────────────────────────────────
print()
try:
    min_score = int(input("Enter minimum satisfaction score (1-5): "))
except ValueError:
    print("Invalid input. Defaulting to 4.")
    min_score = 4

# Select records meeting the minimum satisfaction threshold
rows = db.execute('''
    SELECT student_id, faculty, year, favourite_tool
    FROM responses 
    WHERE satisfaction >= ?
    ORDER BY faculty, year
''', (min_score,)).fetchall()

print(f"\nStudents with satisfaction >= {min_score}:")
if not rows:
    print("  No results found.")
else:
    for row in rows:
        print(f"   {row[0]} | {row[1]:<8} | Year {row[2]} | {row[3]}")


# ══════════════════════════════════════════════════════════════════════════════
# CLEANUP
# ══════════════════════════════════════════════════════════════════════════════
conn.close()