#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average the pixels values
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set the avg value to the pixel
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel of half image
    for (int i = 0; i < height; i++)
    {
        // If width is even
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                RGBTRIPLE swap = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = swap;
            }
        }
        // If width is odd
        else if (width % 2 != 0)
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                RGBTRIPLE swap = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = swap;
            }
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of the image
    RGBTRIPLE copy_image[height][width];

    // Iterate over each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sum of each color
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            float counter = 0;

            // Check if the pixel is in the border
            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }

                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    // Sum the colors
                    sumBlue += image[i + r][j + c].rgbtBlue;
                    sumGreen += image[i + r][j + c].rgbtGreen;
                    sumRed += image[i + r][j + c].rgbtRed;
                    counter++;
                }
            }

            // Average the colors
            copy_image[i][j].rgbtBlue = round(sumBlue / counter);
            copy_image[i][j].rgbtGreen = round(sumGreen / counter);
            copy_image[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy_image[i][j].rgbtRed;
        }

    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of image
    RGBTRIPLE image_copy[height][width];

    // Sobel Operator
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sum of colors in Gx
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;

            // Sum of colors in Gy
            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;

            // Check if the pixel is in the border
            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }

                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }

                    // Pass the pixel through Gx
                    gx_red += image[i + row][j + col].rgbtRed * Gx[row + 1][col + 1];
                    gx_green += image[i + row][j + col].rgbtGreen * Gx[row + 1][col + 1];
                    gx_blue += image[i + row][j + col].rgbtBlue * Gx[row + 1][col + 1];

                    // Pass the pixel through Gy
                    gy_red += image[i + row][j + col].rgbtRed * Gy[row + 1] [col + 1];
                    gy_green += image[i + row][j + col].rgbtGreen * Gy[row + 1][col + 1];
                    gy_blue += image[i + row][j + col].rgbtBlue * Gy[row + 1][col + 1];
                }
            }

            // Amount of Red, Green and Blue of that pixel
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            image_copy[i][j].rgbtRed = (red > 255) ? 255 : red;
            image_copy[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image_copy[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    // Iterate over the image to apply changes
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
        }
    }

    return;
}
