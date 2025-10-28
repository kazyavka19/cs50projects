#include "helpers.h"
#include <math.h>

int avg_rgb(RGBTRIPLE pixel)
{
    float temp = (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0;
    return (int) (temp + 0.5);
}

void reverse_array(RGBTRIPLE  arr[], int length)
{
    for (int i = 0; i < length / 2; i++)
    {
       RGBTRIPLE  temp = arr[i];
       arr[i] = arr[length - i - 1];
       arr[length - i - 1] = temp;
    }
}

int clamp(int value, int min, int max)
{
    if(value < min )
    {
        return min;
    }
    else if( value > max )
    {
        return max;
    }
    else
    {
        return value;
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = avg_rgb(image[i][j]);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
         RGBTRIPLE *row = image[i];
     reverse_array(row, width);
    }

    
}

// Blur image
    void blur(int height, int width, RGBTRIPLE image[height][width])
    {
        RGBTRIPLE temp[height][width];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                temp[i][j] = image[i][j];
            }
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int redSum = 0;
                int greenSum = 0;
                int blueSum = 0;
                int count = 0;
                
                for(int di = -1; di <= 1; di++)
                {
                    for(int dj = -1; dj <= 1; dj++)
                    {
                        int ni = i + di;
                        int nj = j + dj;
                        if(clamp(ni, 0, height - 1) == ni && clamp(nj, 0, width - 1) == nj)
                        {
                            redSum += temp[ni][nj].rgbtRed;
                            greenSum += temp[ni][nj].rgbtGreen;
                            blueSum += temp[ni][nj].rgbtBlue;
                            count++;
                        }
                    }
                }

                temp[i][j].rgbtRed = (int)(redSum / (float)count + 0.5);
                temp[i][j].rgbtGreen = (int)(greenSum / (float)count + 0.5);
                temp[i][j].rgbtBlue = (int)(blueSum / (float)count + 0.5);
            
            }
        }
        
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j] = temp[i][j];
            }
        }

        return;
    }

    
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
        };

        int Gy[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
        };

        RGBTRIPLE temp[height][width];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                temp[i][j] = image[i][j];
            }
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int count_red_Y = 0;
                int count_green_Y = 0;
                int count_blue_Y = 0;

                int count_red_X = 0;
                int count_green_X = 0;
                int count_blue_X = 0;
                
                for(int di = -1; di <= 1; di++)
                {
                    for(int dj = -1; dj <= 1; dj++)
                    {
                        int ni = i + di;
                        int nj = j + dj;
                        if(clamp(ni, 0, height - 1) == ni && clamp(nj, 0, width - 1) == nj)
                        {
                            count_red_Y += temp[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                            count_green_Y += temp[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                            count_blue_Y += temp[ni][nj].rgbtBlue * Gy[di + 1][dj + 1]; 

                            count_red_X += temp[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                            count_green_X += temp[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                            count_blue_X += temp[ni][nj].rgbtBlue * Gx[di + 1][dj + 1]; 
                        }
                    }
                }

                int red = (int)(sqrt((count_red_X * count_red_X) + (count_red_Y * count_red_Y)) + 0.5);
                int green = (int)(sqrt((count_green_X * count_green_X) + (count_green_Y * count_green_Y)) + 0.5);
                int blue = (int)(sqrt((count_blue_X * count_blue_X) + (count_blue_Y * count_blue_Y)) + 0.5);

                temp[i][j].rgbtRed = clamp(red, 0, 255);
                temp[i][j].rgbtGreen = clamp(green, 0, 255);
                temp[i][j].rgbtBlue = clamp(blue, 0, 255);     
            }
        }
        
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j] = temp[i][j];
            }
        }

        return;
}
