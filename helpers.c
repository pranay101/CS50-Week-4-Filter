#include "helpers.h"


// some usefull functions

void swap(RGBTRIPLE *add1, RGBTRIPLE *add2)
    {
        RGBTRIPLE temp = *add1;
        *add1 = *add2;
        *add2 = temp;
    };


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for(int i=0; i < height; i++)
    {
        for(int j=0; j < width ; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen )/ 3;

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int actual_width = width-1;
    for(int i=0; i < height; i++)
    {
        for(int j=0 ; j < width/2; j++)
        {
            swap(&image[i][j], &image[i][actual_width-j]);
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

