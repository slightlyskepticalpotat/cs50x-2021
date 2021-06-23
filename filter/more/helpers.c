#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (double) 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    // Actually calculate the blurred values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgCount = 0;
            int avgBlue = 0;
            int avgGreen = 0;
            int avgRed = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        avgCount += 1;
                        avgBlue += old_image[k][l].rgbtBlue;
                        avgGreen += old_image[k][l].rgbtGreen;
                        avgRed += old_image[k][l].rgbtRed;
                    }
                }
            }
            image[i][j].rgbtBlue = round(avgBlue / (double) avgCount);
            image[i][j].rgbtGreen = round(avgGreen / (double) avgCount);
            image[i][j].rgbtRed = round(avgRed / (double) avgCount);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gxGreen = 0;
            int gxRed = 0;
            int gyBlue = 0;
            int gyGreen = 0;
            int gyRed = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        gxBlue += old_image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                        gxGreen += old_image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                        gxRed += old_image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                        gyBlue += old_image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                        gyGreen += old_image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                        gyRed += old_image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                    }
                }
            }
            image[i][j].rgbtBlue = fmin(255, round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue)));
            image[i][j].rgbtGreen = fmin(255, round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen)));
            image[i][j].rgbtRed = fmin(255, round(sqrt(gxRed * gxRed + gyRed * gyRed)));
        }
    }

    return;
}
