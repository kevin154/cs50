#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"

// Min and max functions
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;

    // Loop across pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
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
    BYTE tmpR, tmpG, tmpB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {    
            tmpR = image[i][width - j].rgbtRed;
            tmpG = image[i][width - j].rgbtGreen;
            tmpB = image[i][width - j].rgbtBlue;
 
            image[i][width - j].rgbtRed = image[i][j].rgbtRed;
            image[i][width - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j].rgbtBlue = image[i][j].rgbtBlue;
       
            image[i][j].rgbtRed = tmpR;
            image[i][j].rgbtGreen = tmpG;
            image[i][j].rgbtBlue = tmpB;
        }
    }
    return;
}

// Box blur algorithm
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int cnt, totalR, totalG, totalB;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {    
            // Reset values
            cnt = totalR = totalG = totalB = 0;

            // Loop across 3x3 grid around the pixel
            for (int m = i - 1; m <= i + 1; m++)
            {
                // Stay within the image borders
                if (m < 0 || m >= height)
                {
                    continue;
                }

                for (int n = j - 1; n <= j + 1; n++)
                {
                    if (n < 0 || n >= width)
                    {
                        continue;
                    }
                        
                    totalR += image[m][n].rgbtRed;
                    totalG += image[m][n].rgbtGreen;
                    totalB += image[m][n].rgbtBlue;
                    cnt++;
                }
            }
            image[i][j].rgbtRed = totalR / cnt;
            image[i][j].rgbtGreen = totalG / cnt;
            image[i][j].rgbtBlue = totalB / cnt;
        }
    }
    return;
}


// Matrices for edge detection
int Gx[3][3] = 
{
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

int Gy[3][3] = 
{
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{  
    // Keep track of the total Sobel number in each cell
    int rGx, rGy, gGx, gGy, bGx, bGy;
    
    // Store the active numbers in Sobel matrices
    int gxVal, gyVal;

    // Keep track of maximum values
    int bMax, gMax, rMax = 0;
    
    // Matrix for storing temporary values following Sobel calculation
    int (*tmpMtx)[height][width];
    tmpMtx = malloc(3 * sizeof * tmpMtx); 

    for (int i = 0; i < height; i++)
    {    
        for (int j = 0; j < width; j++)
        {
            // Reset values
            rGx = rGy = gGx = gGy = bGx = bGy = 0;

            // Loop across outer cells
            for (int m = i - 1; m <= i + 1; m++)
            {    
                // Stay within image height
                if (m < 0 || m >= height)
                {
                    continue;
                }

                for (int n = j - 1; n <= j + 1; n++)
                {
                    // Stay within image width
                    if (n < 0 || n >= width)
                    {
                        continue;
                    }

                    gxVal = Gx[1 + m - i][1 + n - j];
                    gyVal = Gy[1 + m - i][1 + n - j];

                    // Multiply RGB channels by the corresponding Sobel element   
                    rGx += image[m][n].rgbtRed * gxVal;
                    rGy += image[m][n].rgbtRed * gyVal;

                    gGx += image[m][n].rgbtGreen * gxVal;
                    gGy += image[m][n].rgbtGreen * gyVal;

                    bGx += image[m][n].rgbtBlue * gxVal;
                    bGy += image[m][n].rgbtBlue * gyVal;
                }
            }
            
            // Populate temp matrix with new values and update max values
            tmpMtx[0][i][j] = (int) hypot(rGx, rGy);
            rMax = MAX(rMax, tmpMtx[0][i][j]);
            
            tmpMtx[1][i][j] = (int) hypot(gGx, gGy);
            gMax = MAX(gMax, tmpMtx[1][i][j]);
            
            tmpMtx[2][i][j] = (int) hypot(bGx, bGy);
            bMax = MAX(bMax, tmpMtx[2][i][j]);
        }
    }

    // Loop across cells and update values
    for (int i = 0; i < height; i++)
    {    
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = (tmpMtx[0][i][j] * 255) / rMax;
            image[i][j].rgbtGreen = (tmpMtx[1][i][j] * 255) / gMax;
            image[i][j].rgbtBlue = (tmpMtx[2][i][j] * 255) / bMax;
        }
    }
    free(tmpMtx);
    return;
}
