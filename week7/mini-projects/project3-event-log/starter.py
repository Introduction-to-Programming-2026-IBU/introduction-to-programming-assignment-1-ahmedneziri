import csv

# ── Step 1: Set up all data structures before the loop ───────────────────────
room_counts   = {}   # room_name  -> number of events
type_counts   = {}   # event_type -> number of events
day_attendees = {}   # date       -> total attendees that day
all_events    = []   # list of row dicts — used for filtering later

# ── Step 2: Single pass through the CSV — fill all four structures ────────────
with open("bookings.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        room       = row["room"]
        event_type = row["event_type"]
        date       = row["date"]
        attendees  = int(row["attendees"])   # always convert numeric strings!

        # Update room_counts for this room
        room_counts[room] = room_counts.get(room, 0) + 1

        # Update type_counts for this event_type
        type_counts[event_type] = type_counts.get(event_type, 0) + 1

        # Update day_attendees — ADD attendees to the running total for this date
        day_attendees[date] = day_attendees.get(date, 0) + attendees

        # Append the row dict to all_events
        all_events.append(row)

# ── Step 3: Find the busiest day ──────────────────────────────────────────────
busiest_day = max(day_attendees, key=day_attendees.get)
busiest_count = day_attendees[busiest_day]

# ── Step 4: Filter large events (> 50 attendees) and sort by attendees desc ───
large_events = [row for row in all_events if int(row["attendees"]) > 50]

# Sort large_events by attendees descending
large_events_sorted = sorted(large_events, key=lambda row: int(row["attendees"]), reverse=True)

# ── Step 5: Print the report ──────────────────────────────────────────────────
print("=== Community Centre Booking Report ===")

print("\nBookings by Room:")
for room in sorted(room_counts):
    print(f"  {room:<10}: {room_counts[room]}")

print("\nBookings by Event Type:")
for etype in sorted(type_counts):
    print(f"  {etype:<10}: {type_counts[etype]}")

print(f"\nBusiest Day: {busiest_day}  ({busiest_count} total attendees)")

print("\nLarge Events (> 50 attendees):")
for event in large_events_sorted:
    # Formatted output with explicit column alignment
    print(f"  {event['date']} | {event['room']:<8} | {event['event_type']:<9} | {event['attendees']:>3} attendees")