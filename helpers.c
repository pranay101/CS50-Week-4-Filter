#include "helpers.h"


// some usefull functions

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
    return;
}

