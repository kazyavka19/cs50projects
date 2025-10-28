#include "helpers.h"

int avg_rgb(RGBTRIPLE pixel)
{
    float temp = (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0;
    return (int) (temp + 0.5);
}

int sepiaRed(RGBTRIPLE pixel)
{
    float temp = 0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue;
    if (temp > 255.0)
    {
        return 255;
    }
    return (int) (temp + 0.5);
}

int sepiaGreen(RGBTRIPLE pixel)
{
    float temp = 0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue;
    if (temp > 255.0)
    {
        return 255;
    }
    return (int) (temp + 0.5);
}
int sepiaBlue(RGBTRIPLE pixel)
{
    float temp = 0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue;
    if (temp > 255.0)
    {
        return 255;
    }
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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = sepiaRed(image[i][j]);
            int green = sepiaGreen(image[i][j]);
            int blue = sepiaBlue(image[i][j]);
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
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
    return;
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
