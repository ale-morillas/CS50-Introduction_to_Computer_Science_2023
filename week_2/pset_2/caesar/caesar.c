#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cipher(int k, string plaintext);

int main(int argc, string argv[])
{
    // Check the requisites of the input
    // Must be only one argument
    if (argc != 2)
    {
        printf("Error: Invalid number of arguments.\n");
        return 1;
    }
    // The argument must be just digits
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert the key to an int
    int key = atoi(argv[1]);

    // Ask for the input
    string plaintext = get_string("Plaintext:  ");

    // Print the ciphertext
    printf("Ciphertext: %s\n", cipher(key, plaintext));
}

string cipher(int k, string plaintext)
{
    // Allocate the string in memory
    string ciphertext = malloc(strlen(plaintext) + 1);

    // Iterate over the string
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Chheck if the char is alphabetical
        if (isalpha(plaintext[i]))
        {
            // Check if is uppercase
            if (isupper(plaintext[i]))
            {
                // Convert ASCII code to its alphabetical index
                int alpha_index_upper = plaintext[i] - 'A';
                // Formula
                int ci = (alpha_index_upper + k) % 26;
                // Convert from alphabetical index to ASCII code
                ciphertext[i] = ci + 'A';
            }
            // Check if is uppercase
            else if (islower(plaintext[i]))
            {
                // Convert ASCII code to its alphabetical index
                int alpha_index_lower = ((int) plaintext[i]) - 'a';
                // Formula
                int ci = (alpha_index_lower + k) % 26;
                // Convert from alphabetical index to ASCII code
                ciphertext[i] = ci + 'a';
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

