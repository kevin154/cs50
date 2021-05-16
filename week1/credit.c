#include <stdio.h>
#include <cs50.h>

// Prototypes
bool checkDigits(long cardNum, int countDigits);
int sumDigits(int number);

int main(void)
{
    long cardNum, tmpNum;
    int countDigits = 0;
    short prevDigit, prevPrevDigit; 
    string cardType;

    // Get card number and copy to temporary variable
    cardNum = get_long("Enter credit card number: ");
    tmpNum = cardNum;

    // Get the digit count and the first two numbers for initial validation
    while (tmpNum > 0)
    {
        countDigits++;
        prevPrevDigit = prevDigit;
        prevDigit = tmpNum % 10;
        tmpNum /= 10;
    }

    // Initial validation
    if (countDigits == 15 && prevDigit == 3 && (prevPrevDigit == 4 || prevPrevDigit == 7))
    {
        cardType = "AMEX\n";
    }
    else if (countDigits == 16 && prevDigit == 5 && (prevPrevDigit > 0 && prevPrevDigit < 6))
    {
        cardType = "MASTERCARD\n";
    }
    else if ((countDigits == 13 || countDigits == 16) && prevDigit == 4)
    {  
        cardType = "VISA\n";
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

    if (checkDigits(cardNum, countDigits))
    {
        printf("%s", cardType);
    }
    else 
    {
        printf("INVALID\n");
    }
    return 0;
}

// Check calid number
bool checkDigits(long cardNum, int countDigits)
{

    int total = 0;
    short currentDigit;
    bool oddStep;
    
    // Loop from back of number
    for (int i = 0; i < countDigits; i++)
    {
        currentDigit = cardNum % 10;
        oddStep = (i % 2 == 1);

        // Add the sum of digits of double the number for every second number    
        if (oddStep)
        {
            total += sumDigits(2 * currentDigit);
        }
        // Simply add the current digit for every other number
        else
        {
            total += currentDigit;
        }
        cardNum /= 10;
    }
    // Check if total divisible by 10
    return total % 10 == 0;
}

// Utility function for summing digits
int sumDigits(int number)
{
    
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}
