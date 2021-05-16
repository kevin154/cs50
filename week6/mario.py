from cs50 import get_int

while True:
    height = get_int("Height:")
    if height > 0 and height < 9:
        break

for i in range(1, height + 1):
    # Print (height - i) blanks 
    for j in range(height - i):
        print(" ", end="")
    # Print i hashes
    for j in range(i):
        print("#", end="")
    # Print two blanks in the middle
    print("  ", end="")
    # Print i more hashes
    for j in range(i):
        print("#", end="")
    # Print newline
    print()
