
sentence = input("Enter a sentence: ")
words = sentence.lower().split()

# Total word count using len()
total_words = len(words)

# Character count (no spaces)
# Hint: sentence.replace(" ", "") removes all spaces, then use len()
total_chars = len(sentence.replace(" ", ""))

# Word frequency dictionary
frequency = {}
for word in words:
    if word in frequency:
        frequency[word] += 1
    else:
        frequency[word] = 1

# Print total words, total characters, then word frequency
print(f"Total words: {total_words}")
print(f"Total characters (no spaces): {total_chars}")
print("Word frequency:")
for word, count in frequency.items():
    print(f"  {word}: {count}")