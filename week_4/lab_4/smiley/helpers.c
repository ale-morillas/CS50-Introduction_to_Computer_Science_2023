#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // Iterate over each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                // Change the value of red, green and blue to change the color
                image[i][j].rgbtRed = 0x08;
                image[i][j].rgbtGreen = 0x03;
                image[i][j].rgbtBlue = 0x96;
            }
        }
    }
}
