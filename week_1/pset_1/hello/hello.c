#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Enter the name: "); //Input the name
    printf("hello, %s\n", name); //Show hello, name
}