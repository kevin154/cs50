#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int height;
    
    // Ensure that the given number is beteen 1 and 8 inclusive
    do 
    {
        height = get_int("Enter height: ");
    } 
    while (height < 1 || height > 8);

    // Loop across each row
    for (int i = 1; i <= height; i++)
    {
    
        // Print (height - i) blanks 
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
       
        // Print i hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        // Print two blanks in the middle
        printf("  ");

        // Print i more hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        // Print newline
        printf("\n");
    }
}
