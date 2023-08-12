#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: "); //Min in range
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: "); //Top in range
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    for (int i = 2; i < number; i++) //Starting checking from 2 to number - 1
    {
        if (number % i == 0) //If the number is divisible by any other number that ain't 1 or itself return false
        {
            return false;
        }

    }
    return true; //Else return true
}
