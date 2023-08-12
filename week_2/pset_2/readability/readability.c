#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);                              //Count the number of letters
int count_words(string text);                                //Count the number of words
int count_sentences(string text);                            //Count the number of sentences

int main(void)
{
    string text = get_string("Introduce the text: ");         // Prompt the user for the text

    float L = (count_letters(text) / (float) count_words(text)) * 100;    // Avg number of letters per 100 words in the text
    float S = (count_sentences(text) / (float) count_words(text)) * 100;  // Avg number of sentences per 100 words in the text
    
    float index = (0.0588 * L) - (0.296 * S) - 15.8;          // Coleman-Liau Index

    if (index < 1)                                            // Printing the Grade
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
        if (isalpha(text[i]))
        {
            count += 1;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
        if (isspace(text[i]))
        {
            count += 1;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count += 1;
        }
    }
    return count;
}