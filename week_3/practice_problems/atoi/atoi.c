#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Base Case
    if (strlen(input) == 0)
    {
        return 0;
    }
    // Index of the last character
    int lastChar_index = strlen(input) - 1;

    // Numeric Value
    int num_val = input[lastChar_index] - '0';

    // Remove last char
    input[lastChar_index] = '\0';

    // Recursive call with the shortened string
    int remaining_value = convert(input);

    // Combine the value of the last character with the remaining value
    int combined_value = remaining_value * 10 + num_val;

    return combined_value;
}