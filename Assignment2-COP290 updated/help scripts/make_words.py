import random
import string

# Set the number of words to generate
num_words = 250000

# Generate a list of unique random words
words = set()
while len(words) < num_words:
    word = ''.join(random.choice(string.ascii_lowercase) for i in range(random.randint(8, 12)))
    words.add(word)

# Write the words to a text file
with open('unique_words.txt', 'w') as file:
    for word in words:
        file.write(word + '\n')