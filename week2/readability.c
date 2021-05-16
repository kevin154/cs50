#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int letterCount = 0, wordCount = 0, sentenceCount = 0;
    
    // Get input from user
    string inputString = get_string("Enter: ");
    
    // Special chars specifying end of sentence
    const char *endChars = "?!.";
    char *c = inputString;
    
    // Loop across each character 
    while (*c)
    {
        // Check letter
        if (isalpha(*c))
        {
            letterCount++;
        }
        // Check space
        if (isspace(*c))
        {
            // For first space encountered increment wordCount
            if (!wordCount)
            {
                wordCount++;
            }
            wordCount++;
        }
        // Check if character is a sentenace endpoint
        if (strchr(endChars, *c))
        {
            sentenceCount++;
        }
        c++;
    }  

    // Coleman-Liau formula
    float L = 100 * letterCount / (float) wordCount;
    float S = 100 * sentenceCount / (float) wordCount;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %i\n", index);
    }
}
