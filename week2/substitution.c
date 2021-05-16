#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // Take the cipher from input
    string cipher = argv[1];
    
    // Ensure the cipher has a proper length 
    if (strlen(cipher) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // More cipher sanity checks
    for (int i = 0; i < strlen(cipher); i++)
    {
        char currentChar = cipher[i]; 
        // Check for non-alpha characters
        if (!isalpha(currentChar))
        {
            printf("Key must contain alphabet characters.\n");
            return 1;
        }
        // Check for duplicates
        int cnt = 0;
        for (int j = 0; j < strlen(cipher); j++)
        {
            if (tolower(cipher[j]) == tolower(currentChar))
            {
                cnt++;
            }
        }
        if (cnt > 1)
        {
            printf("Key must contain unique characters.\n");
            return 1;
        }
    }

    // Get input from user
    string inputString = get_string("plaintext: ");
    
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    printf("ciphertext: ");

    for (int i = 0; i < strlen(inputString); i++)
    {
        // If non alpha character print as is and move on
        if (!isalpha(inputString[i]))
        {
            printf("%c", inputString[i]);
            continue;
        }

        for (int j = 0; j <= strlen(alphabet); j++)
        {
            // Check if match found, ignore case
            if (toupper(inputString[i]) == alphabet[j])
            {
                // Lower the cipher if orig is lowercase
                if (islower(inputString[i]))
                {
                    printf("%c", tolower(cipher[j]));
                    continue;
                }
                // Else print the cipher in uppercase
                else 
                {
                    printf("%c", toupper(cipher[j]));
                    continue;
                }
            } 
        }
    }
    printf("\n");
    return 0;
}
