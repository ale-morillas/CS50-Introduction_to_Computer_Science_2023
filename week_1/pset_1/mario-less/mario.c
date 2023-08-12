#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt the pyramid height until its in range
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Create the pyramid
    for (int i = 1; i <= height; i++) //Iterate the rows
    {
        for (int j = 1; j <= height; j++) //Iterate the columns
        {
            if (i + j <= height)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}