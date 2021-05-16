from cs50 import get_string
from sys import exit

letterCount = wordCount = sentenceCount = 0

inputString = get_string("Enter: ")
# Characters signifying end of sentence
endChars = "?!."

# Loop across the string
for c in inputString:
    # Check letter
    if c.isalpha():
        letterCount += 1
    # Check space
    if c == " ":
        # For first space encountered increment wordCount
        if (not wordCount):
            wordCount += 1
        wordCount += 1
    # Check if character is a sentenace endpoint
    if c in endChars:
        sentenceCount += 1

# Coleman-Liau formula
L = 100 * letterCount / wordCount
S = 100 * sentenceCount / wordCount
index = round(0.0588 * L - 0.296 * S - 15.8)

if (index < 1):
    print("Before Grade 1\n")
elif (index > 16):
    print("Grade 16+\n")
else:
    print(f"Grade {index}\n") 
