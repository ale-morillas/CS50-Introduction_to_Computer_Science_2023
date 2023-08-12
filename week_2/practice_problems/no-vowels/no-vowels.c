// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string argv);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error, your enter none or more than one argument.\n"); //Error message
        return 1;
    }
    else
    {
        printf("%s\n", replace(argv[1])); //Printing result
    }
}

string replace(string argv)
{
    for (int i = 0; i < strlen(argv); i++)
    {
        switch (argv[i])
        {
            case 'a':
                argv[i] = '6';
                break;
            case 'e':
                argv[i] = '3';
                break;
            case 'i':
                argv[i] = '1';
                break;
            case 'o':
                argv[i] = '0';
                break;
            default:
                break;
        }
    }
    return argv;
}
