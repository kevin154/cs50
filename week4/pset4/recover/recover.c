#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Number of bytes in memory block
const int BLOCK_SIZE = 512; 
// File name length
const int fileNameSize = 20;
// Buffer for images
uint8_t buffer[BLOCK_SIZE];


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover input\n");
        return 1;
    }

    // Open input file 
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = 0x00;
    char outputFileName[fileNameSize];
    int idx = 0;

    // Read data in chunks
    while(fread(&buffer, BLOCK_SIZE, 1, input))
    {
        // Check if buffer chunk is likely a jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // If new jpeg found close any open files
            if (output != NULL)
                fclose(output);
            
            // Generate new file name
            snprintf(outputFileName, sizeof(char) * fileNameSize, "file%i.jpeg", ++idx);

            // Open a new file for writing
            output = fopen(outputFileName, "w");
            if (output == NULL)
            {
                printf("Could not open output file.\n");
                return 1;
            }  
            // Write data into the buffer
            fwrite(&buffer, BLOCK_SIZE, 1, output);  
        }
        // If not a new jpeg then continue writing
        else if (output != NULL)
            fwrite(&buffer, BLOCK_SIZE, 1, output);
    }

    // Close input and output files
    fclose(input);
    fclose(output);
}
