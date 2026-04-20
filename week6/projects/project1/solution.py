# Project 1 — Temperature Converter
# Author: your name here
# Date:   session date here
#
# Instructions:
#   1. Read the README.md in this folder first.
#   2. Fill in the missing lines below.
#   3. Test with: 0°C → 32°F | 100°C → 212°F | -40°C → -40°F

# ── Your solution goes here ───────────────────────────────────────────────────

# Direction menu (C→F or F→C)
direction = input("Choose conversion: [1] Celsius to Fahrenheit or [2] Fahrenheit to Celsius: ")

if direction == "1":
    celsius = float(input("Enter temperature in Celsius: "))
    fahrenheit = (celsius * 9 / 5) + 32
    print(f"{celsius}°C is equal to {fahrenheit:.1f}°F")
    
elif direction == "2":
    fahrenheit = float(input("Enter temperature in Fahrenheit: "))
    celsius = (fahrenheit - 32) * 5 / 9
    print(f"{fahrenheit}°F is equal to {celsius:.1f}°C")
    
else:
    print("Invalid input. Please restart the program and enter 1 or 2.")