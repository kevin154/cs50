from cs50 import get_string
from sys import exit

# Function for checking digits
def checkDigits(number):

    revNumber = number[::-1]
    total = 0

    for i in range(countDigits):

        oddStep = (i % 2 == 1)
        currentDigit = int(revNumber[i])    
        # Add the sum of digits of double the number for every second number
        if (oddStep):
            total += sumDigits(str(2 * currentDigit))
        # Simply add the current digit for every other number
        else:
            total += currentDigit
    return total % 10 == 0 


# Utility function for summing digits 
def sumDigits(number):
    total = 0
    for n in number:
        total += int(n)
    return total


# Get input from user
cardNum = get_string("Number: ")
countDigits = len(cardNum)

# Initial check for valid number
if countDigits < 13:
    print("INVALID")
    exit(0)

firstDigit = int(cardNum[0])
secondDigit = int(cardNum[1])

# Initial validation
if countDigits == 15 and firstDigit == 3 and secondDigit in [4, 7]:
    cardType = "AMEX"
elif countDigits == 16 and firstDigit == 5 and secondDigit > 0 and secondDigit < 6:
    cardType = "MASTERCARD"
elif countDigits in [13, 16] and firstDigit == 4:
    cardType = "VISA"
else:
    print("INVALID")
    exit(0)

if checkDigits(cardNum):
    print(cardType)
else:
    print("INVALID")

exit(0)
