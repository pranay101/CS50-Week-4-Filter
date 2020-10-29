#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// some usefull functions

int check(int a)
{
    if (a>255)
    {
        return a=255;
    }
    else
    {
        return a;
    }
}

void swap(RGBTRIPLE *add1, RGBTRIPLE *add2)
    {
        RGBTRIPLE temp = *add1;
        *add1 = *add2;
        *add2 = temp;
    };
// void calc_average(int startRow,int endRow,int startColumn,int endColumn,int row,int col)
// {

//     for(int i=startRow; i<=endRow; i++)
//     {
//         for(int j= startColumn; j<=endColumn; j++)
//         {
//             averagered += image[i][j].rgbtRed;
//             averagegreen += image[i][j].rgbtGreen;
//             averageblue += image[i][j].rgbtBlue;
//             count++;
//         }
//     }

//     image[row][col].rgbtRed = averagered/count;
//     image[row][col].rgbtBlue= averageblue/count;
//     image[row][col].rgbtGreen averagegreen/count;
// }


// compute edges
int compute_edge(int a , int b)
{
  return sqrt((a*a + b*b));
}


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
    int averagered=0, averagegreen=0,averageblue=0,count=0;
    //void calc_average(int , int ,int ,int);
    int startRow,endRow,startColumn,endColumn;
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
          if(i - 1 < 0)
            startRow = i;
          else
            startRow = i-1;
          if(i + 1 >= height)
            endRow = i;
          else
            endRow = i+1;
          if(j - 1 < 0)
            startColumn = j;
          else
            startColumn = j-1;
          if(j + 1 >= width)
            endColumn = j;
          else
            endColumn = j+1;


    //   (i - 1 < 0) ? i : i - 1;
    //     endRow = (i + 1 >= height) ? i : i + 1;
    //     startColumn = (j - 1 < 0) ? j : j - 1;
    //     endColumn = (j + 1 >= width) ? j : j + 1;
            for(int k=startRow; k<=endRow; k++)
            {
                averagered=0;
                averagegreen=0;
                averageblue=0;
                count=0;
                for(int l= startColumn; l<=endColumn; l++)
                {
                    averagered += image[k][l].rgbtRed;
                    averagegreen += image[k][l].rgbtGreen;
                    averageblue += image[k][l].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = averagered/count;
            image[i][j].rgbtBlue= averageblue/count;
            image[i][j].rgbtGreen = averagegreen/count;

        //calc_average(startRow,endRow,startColumn,endColumn,i,j);
      }
    }
    return;
}





// Detect edges

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float GxRed, GxBlue, GxGreen;
    float GyRed, GyBlue, GyGreen;
    float X,Y;
    //create a temporary image 2d array to not change calculation after every loop
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            GyBlue = 0.0;
            GyGreen = 0.0;
            GyRed = 0.0;
            GxBlue = 0.0;
            GxGreen = 0.0;
            GxRed = 0.0;

            // sums values of the pixel and 8 neighboring ones after applying a modifier, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    // calculates modifiers for vertical and horizantal borders
                    X = (k + 1 * k - k * abs(h));
                    Y = (h + 1 * h - h * abs(k));

                    GxBlue += image[j + k][i + h].rgbtBlue * X;
                    GxGreen += image[j + k][i + h].rgbtGreen * X;
                    GxRed += image[j + k][i + h].rgbtRed * X;

                    GyBlue += image[j + k][i + h].rgbtBlue * Y;
                    GyGreen += image[j + k][i + h].rgbtGreen * Y;
                    GyRed += image[j + k][i + h].rgbtRed * Y;
                }
            }

            // obtains the final values of the pixels combining X and Y calculations
            temp[j][i].rgbtBlue = check(round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue)));
            temp[j][i].rgbtGreen = check(round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)));
            temp[j][i].rgbtRed = check(round(sqrt(GxRed * GxRed + GyRed * GyRed)));
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
    return;
}

