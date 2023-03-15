#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pxl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pxl = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);

            image[i][j].rgbtBlue = pxl;
            image[i][j].rgbtGreen = pxl;
            image[i][j].rgbtRed = pxl;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float pxl[3];
    int PXL[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pxl[0] = image[i][j].rgbtBlue;
            pxl[1] = image[i][j].rgbtGreen;
            pxl[2] = image[i][j].rgbtRed;

            PXL[0] = round(.272 * pxl[2] + .534 * pxl[1] + .131 * pxl[0]);
            image[i][j].rgbtBlue = (PXL[0] > 255) ? 255 : PXL[0];

            PXL[1] = round(.349 * pxl[2] + .686 * pxl[1] + .168 * pxl[0]);
            image[i][j].rgbtGreen = (PXL[1] > 255) ? 255 : PXL[1];

            PXL[2] = round(.393 * pxl[2] + .769 * pxl[1] + .189 * pxl[0]);
            image[i][j].rgbtRed = (PXL[2] > 255) ? 255 : PXL[2];

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE t_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                       image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                        image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                                      image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4);

            }
            else if (i == 0 && j == width-1){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                       image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                        image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                                                      image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4);

            }
            else if (i == height-1 && j == 0){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i-1][j].rgbtBlue +
                                        image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue)/ 4);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i-1][j].rgbtGreen +
                                        image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen)/ 4);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i-1][j].rgbtRed +
                                        image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed)/ 4);
            }
            else if (i == height-1 && j == width-1){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i-1][j].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue)/ 4);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i-1][j].rgbtGreen +
                                        image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen)/ 4);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i-1][j].rgbtRed +
                                        image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed)/ 4);
            }
            else if (i == 0){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue +
                                        image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue)/ 6);


                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                        image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen +
                                        image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen)/ 6);


                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                        image[i][j-1].rgbtRed + image[i+1][j].rgbtRed +
                                        image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed)/ 6);

            }
            else if (i == height-1){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue +
                                        image[i-1][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue)/ 6);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                        image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen +
                                        image[i-1][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen)/ 6);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                        image[i][j-1].rgbtRed + image[i-1][j].rgbtRed +
                                        image[i-1][j+1].rgbtRed + image[i-1][j-1].rgbtRed)/ 6);

            }
            else if (j == width-1){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j-1].rgbtBlue +
                                        image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue +
                                        image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue)/ 6);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j-1].rgbtGreen +
                                        image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen +
                                        image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen)/ 6);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j-1].rgbtRed +
                                        image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed +
                                        image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed)/ 6);

            }
            else if (j == 0){
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue +
                                        image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue)/ 6);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                        image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen +
                                        image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen)/ 6);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                        image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed +
                                        image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed)/ 6);

            }
            else
            {
                t_image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue +
                                        image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue +
                                        image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                                        image[i-1][j-1].rgbtBlue)/ 9);

                t_image[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                        image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen +
                                        image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen +
                                        image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                                        image[i-1][j-1].rgbtGreen)/ 9);

                t_image[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                                        image[i][j-1].rgbtRed + image[i+1][j].rgbtRed +
                                        image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed +
                                        image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                                        image[i-1][j-1].rgbtRed)/ 9);
            }
        }
    }

    for (int n = 0; n < height; n++){
        for (int m = 0; m < width; m++){
            image[n][m] = t_image[n][m];
        }

    }
    return;
}

