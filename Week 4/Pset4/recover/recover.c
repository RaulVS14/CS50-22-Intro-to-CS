#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Check if user provided correct amount of command-line arguments
    if (argc != 2)
    {
        printf("Usage ./recover IMAGE\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");

    // Check if file can be opened
    if (file == NULL)
    {
        printf("IMAGE cannot be opened! Please make sure the IMAGE name is correct\n");
        return 1;
    }
    char name_buffer[8];
    BYTE file_buffer[BLOCK_SIZE];
    int counter = 0;
    FILE *new_file;
    int found_jpg = 0;
    // Add current file name to buffer
    sprintf(name_buffer, "%03d.jpg", counter);
    while (fread(&file_buffer, 1, BLOCK_SIZE, file) != 0)
    {
        if ((file_buffer[0] == 0xff) && (file_buffer[1] == 0xd8) && (file_buffer[2]  == 0xff) && ((file_buffer[3] & 0xf0) == 0xe0))
        {
            found_jpg = 1;
            // Check if it is the first time file was found
            if (counter == 0)
            {
                new_file = fopen(name_buffer, "w");
                fwrite(&file_buffer, BLOCK_SIZE, 1, new_file);
                // Increase counter to prepare for when next file is found
                counter ++;
            }
            else
            {
                // Add new file name to the buffer
                sprintf(name_buffer, "%03d.jpg", counter);
                // Close previous file
                fclose(new_file);
                // Open new file
                new_file = fopen(name_buffer, "w");
                // Write already read buffer to the new file
                fwrite(&file_buffer, BLOCK_SIZE, 1, new_file);
                counter ++;
            }
        }
        else
        {
            // Check if jpeg files start has been found
            if (found_jpg != 0)
            {
                // Write to already open file
                fwrite(&file_buffer, BLOCK_SIZE, 1, new_file);
            }
        }
    }
    // Close the last file
    fclose(new_file);
    // Close the raw file
    fclose(file);
}