#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string substitution(string key, string plaintext);

int main(int argc, string argv[])
{
    // Check the requisites of the input
    // Must be only one argument
    if (argc != 2)
   {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // The argument must be just aplhabetical characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }
    }
    // The argument isn't 26 letters long
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // There is a repeated letter in the key
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Store the key
    string key = argv[1];
    // Get plaintext
    string plaintext = get_string("Plaintext:  ");

    // Print the ciphertext
    printf("ciphertext: %s\n", substitution(key, plaintext));
}


string substitution(string key, string plaintext)
{
    // Allocate the string in memory
    string ciphertext = malloc(strlen(plaintext) + 1);

    // Iterate over the string
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Check if the char is alphabetical
        if (isalpha(plaintext[i]))
        {
            // Check if is uppercase
            if (isupper(plaintext[i]))
            {
                int alpha_index_upper = plaintext[i] - 'A';
                // Get the char from the key
                ciphertext[i] = toupper(key[alpha_index_upper]);
            }
            // Check if is lowercase
            else if (islower(plaintext[i]))
            {
                // Convert ASCII code to its alphabetical index
                int alpha_index_lower = plaintext[i] - 'a';
                // Get the char from the key
                ciphertext[i] = tolower(key[alpha_index_lower]);
            }
        }
        else
        {
            // Keep the char if is not alphabetical
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}

