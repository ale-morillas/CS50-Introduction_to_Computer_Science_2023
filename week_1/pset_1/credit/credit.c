#include <cs50.h>
#include <stdio.h>

void card_type(long card);
bool check_sum(long card);

int main(void)
{
    long credit_card = get_long("Credit Card Number: ");

    //Conditional to solve the problem
    if (check_sum(credit_card) == true)
    {
        card_type(credit_card);
    }
    else
    {
        printf("INVALID\n");
    }
}

void card_type(long card)
{
    //Check what type of credit card is or if its invalid
    if (card / 1000000000000 == 4 || card / 1000000000000000 == 4) //Check if it's a VISA
    {
        printf("VISA\n");
    }
    else if (card / 10000000000000 == 34 || card / 10000000000000 == 37) //Check if it's a AMERICAN EXPRESS
    {
        printf("AMEX\n");
    }
    else if (card / 100000000000000 >= 51 && card / 100000000000000 <= 55) //Check if it's a MASTERCARD
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_sum(long card)
{
    //Checks if the credit card meets Luhn's algorithm
    int pairs = 0;
    int odds = 0;

    //Sum of every pair digit multipliyed by 2
    int d2 = (((card / 10) % 10) * 2 / 10) + (((card / 10 % 10) * 2) % 10);
    int d4 = (((card / 1000) % 10) * 2 / 10) + (((card / 1000 % 10) * 2) % 10);
    int d6 = (((card / 100000) % 10) * 2 / 10) + (((card / 100000 % 10) * 2) % 10);
    int d8 = (((card / 10000000) % 10) * 2 / 10) + (((card / 10000000 % 10) * 2) % 10);
    int d10 = (((card / 1000000000) % 10) * 2 / 10) + (((card / 1000000000 % 10) * 2) % 10);
    int d12 = (((card / 100000000000 % 10) * 2) / 10) + (((card / 100000000000 % 10) * 2) % 10);
    int d14 = (((card / 10000000000000) % 10) * 2 / 10) + (((card / 10000000000000 % 10) * 2) % 10);
    int d16 = (((card / 1000000000000000) % 10) * 2 / 10) + (((card / 1000000000000000 % 10) * 2) % 10);

    //Sum of every odd digit
    int d1 = (card % 10);
    int d3 = ((card / 100) % 10);
    int d5 = ((card / 10000) % 10);
    int d7 = ((card / 1000000) % 10);
    int d9 = ((card / 100000000) % 10);
    int d11 = ((card / 10000000000) % 10);
    int d13 = ((card / 1000000000000) % 10);
    int d15 = ((card / 100000000000000) % 10);

    int sum_p = d2 + d4 + d6 + d8 + d10 + d12 + d14 + d16;
    int sum_o = d1 + d3 + d5 + d7 + d9 + d11 + d13 + d15;
    int sum = sum_p + sum_o;

    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}