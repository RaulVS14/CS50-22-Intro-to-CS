#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool validate_key(string key);
void encrypt(string message, string key);
int find_position(char character);

int main(int argc, string argv[])
{
    // Check provided args
    if (argc != 2)
    {
        // Check if correct nr of arguments
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argv[1] && strlen(argv[1]) != 26)
    {
        // Check if argument is of required length: 26
        printf("Key must contain 26 chars\n");
        return 1;
    }
    else if (argv[1] && !validate_key(argv[1]))
    {
        // if key exists and query fails stop program
        return 1;
    }
    string key = argv[1];
    // Prompt user to enter message
    string message = get_string("plaintext: ");

    // Output encryprted message
    printf("ciphertext: ");
    encrypt(message, key);
    return 0;
}
bool validate_key(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        char key_character = key[i];
        // Check if key character is letter
        if (!isalpha(key_character))
        {
            printf("Invalid key: %c not allowed\n", key_character);
            return false;
        }
        else
        {
            for (int j = i + 1; j < n; j++)
            {
                // Check for repeating character
                if (tolower(key_character) == tolower(key[j]))
                {
                    printf("Invalid key: %c is repeating character\n", key_character);
                    return false;
                }
            }
        }
    }
    // Everything valid
    return true;
}

void encrypt(string message, string key)
{

    for (int i = 0, n = strlen(message); i < n; i++)
    {
        char current_char = message[i];
        // check if letter
        if (isalpha(current_char))
        {
            // Find character responding key
            int key_position = find_position(current_char);
            char enc_character = key[key_position];
            // Ensure that case remains
            if (islower(current_char))
            {
                current_char = tolower(enc_character);
            }
            else
            {
                current_char = toupper(enc_character);
            }
        }
        printf("%c", current_char);
    }
    printf("\n");
}

int find_position(char character)
{
    return tolower(character) - 97;
}