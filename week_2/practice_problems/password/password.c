// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool upper, lower, digit, symbol = false;
    for (int i = 0; i < strlen(password); i++) //Iterate over the string and check every character
    {
        if isupper(password[i])
        {
            upper = true;
        }
        else if islower(password[i])
        {
            lower = true;
        }
        else if isdigit(password[i])
        {
            digit = true;
        }
        else if ispunct(password[i])
        {
            symbol = true;
        }
    }

    if (upper && lower && digit && symbol) //If the string achieve all the requirements return true
    {
        return true;
    }
    else                                   //False otherwise
    {
        return false;
    }
}
