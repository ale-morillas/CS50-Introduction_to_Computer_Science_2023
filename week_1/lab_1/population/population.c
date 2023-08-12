#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int init_pop;
    do
    {
        init_pop = get_int("Enter the initial population: \n");
    }
    while (init_pop < 9);

    // Prompt for end size
    int ending_pop;
    do
    {
        ending_pop = get_int("Enter the ending population: \n");
    }
    while (init_pop > ending_pop);

    // Calculate number of years until we reach threshold
    bool stop = true;
    int n;
    int years = 0;
    while (stop)
    {
        if (init_pop == ending_pop)
        {
            break;
        }
        n = init_pop + (init_pop / 3) - (init_pop / 4);
        years += 1;
        init_pop = n;
        if (n >= ending_pop)
        {
            stop = false;
        }
    }

    // Print number of years
    printf("Years: %i\n", years);
}
