#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            float count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sum_red += copy[ni][nj].rgbtRed;
                        sum_green += copy[ni][nj].rgbtGreen;
                        sum_blue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sum_red / count);
            image[i][j].rgbtGreen = round(sum_green / count);
            image[i][j].rgbtBlue = round(sum_blue / count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long gx_r = 0, gy_r = 0;
            long gx_g = 0, gy_g = 0;
            long gx_b = 0, gy_b = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int weight_x = Gx[di + 1][dj + 1];
                        int weight_y = Gy[di + 1][dj + 1];

                        gx_r += weight_x * copy[ni][nj].rgbtRed;
                        gy_r += weight_y * copy[ni][nj].rgbtRed;
                        
                        gx_g += weight_x * copy[ni][nj].rgbtGreen;
                        gy_g += weight_y * copy[ni][nj].rgbtGreen;
                        
                        gx_b += weight_x * copy[ni][nj].rgbtBlue;
                        gy_b += weight_y * copy[ni][nj].rgbtBlue;
                    }
                }
            }

            int r = round(sqrt(gx_r * gx_r + gy_r * gy_r));
            int g = round(sqrt(gx_g * gx_g + gy_g * gy_g));
            int b = round(sqrt(gx_b * gx_b + gy_b * gy_b));

            image[i][j].rgbtRed = r > 255 ? 255 : r;
            image[i][j].rgbtGreen = g > 255 ? 255 : g;
            image[i][j].rgbtBlue = b > 255 ? 255 : b;
        }
    }
}