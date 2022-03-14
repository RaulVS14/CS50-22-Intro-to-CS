#include "helpers.h"
#include "stdio.h"
#include "math.h"

RGBTRIPLE calc_avg_pixel(RGBTRIPLE list[9], int counter);
int calc_combined_x_y(int gx, int gy);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create variables for RGBTRIPLE values
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            // Calculate average and round it to int
            int avg = round((red + blue + green) / 3.0);
            // Grayscale: R = G = B = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int last_element = width - 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            // Create temporary variables to hold right side RGBTRIPLE
            RGBTRIPLE tmpRed = image[i][j];
            // Replace right side value with the value on left side
            image[i][j] = image[i][last_element - j];
            // Replace in the temporary value
            image[i][last_element - j] = tmpRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create duplicate of existing image, so pixels could be used correctly for the updated image
    RGBTRIPLE stored_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            stored_image[i][j] = image[i][j];
        }
    }
    // Apply filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int n_counter = 0;

            RGBTRIPLE square[9];
            // Add memembers to the neighbors square: MAX 3 = Top row 3
            if (i > 0)
            {
                // Top left
                if (j > 0)
                {
                    square[n_counter] = stored_image[i - 1][j - 1];
                    n_counter++;
                }

                // Top middle
                square[n_counter] = stored_image[i - 1][j];
                n_counter++;

                // Top right
                if (j < (width - 1))
                {
                    square[n_counter] = stored_image[i - 1][j + 1];
                    n_counter++;
                }
            }
            // Left side, next to main element
            if (j > 0)
            {
                square[n_counter] = stored_image[i][j - 1];
                n_counter++;
            }

            // Element itself
            square[n_counter] = stored_image[i][j];
            n_counter++;

            // Right side, next to main element
            if (j < (width - 1))
            {
                square[n_counter] = stored_image[i][j + 1];
                n_counter++;
            }

            // Add memembers to the neighbors square: MAX 3 = Bottom row 3
            if (i < (height - 1))
            {
                // Bottom left
                if (j > 0)
                {
                    square[n_counter] = stored_image[i + 1][j - 1];
                    n_counter++;
                }

                // Bottom middle
                square[n_counter] = stored_image[i + 1][j];
                n_counter++;

                // Bottom right
                if (j < (width - 1))
                {
                    square[n_counter] = stored_image[i + 1][j + 1];
                    n_counter++;
                }
            }
            // Replace pixcel with new value
            image[i][j] = calc_avg_pixel(square, n_counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create duplicate of existing image, so pixels could be used correctly for the updated image
    RGBTRIPLE stored_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            stored_image[i][j] = image[i][j];
        }
    }
    RGBTRIPLE empty_pixel;
    empty_pixel.rgbtRed = 0;
    empty_pixel.rgbtGreen = 0;
    empty_pixel.rgbtBlue = 0;
    // X Kernel for x direction
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Y Kernel for y direction
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Variables for total x kernel values
            int x_rgbtRed = 0;
            int x_rgbtGreen = 0;
            int x_rgbtBlue = 0;

            // Variables for total y kernel values
            int y_rgbtRed = 0;
            int y_rgbtGreen = 0;
            int y_rgbtBlue = 0;

            // Go through neighbours
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    RGBTRIPLE current_neighbour;
                    // Get current neighbour
                    if (((i + k) >= 0) && ((i + k) < height) && ((j + l) >= 0) && ((j + l) < width))
                    {
                        current_neighbour = stored_image[i + k][j + l];
                    }
                    else
                    {
                        // If neighbour is out of bounds, mark it as empty pixel
                        current_neighbour = empty_pixel;
                    }
                    // printf("element(%i, %i) neigbour(%i, %i): %i, %i, %i\n", i, j, k, l, current_neighbour.rgbtRed,  current_neighbour.rgbtGreen,  current_neighbour.rgbtBlue);
                    int x_multiplier = Gx[k + 1][l + 1];
                    int y_multiplier = Gy[k + 1][l + 1];
                    // Apply multiplier and sum the result
                    x_rgbtRed += (current_neighbour.rgbtRed * x_multiplier);
                    x_rgbtGreen += (current_neighbour.rgbtGreen * x_multiplier);
                    x_rgbtBlue += (current_neighbour.rgbtBlue * x_multiplier);
                    y_rgbtRed += (current_neighbour.rgbtRed * y_multiplier);
                    y_rgbtGreen += (current_neighbour.rgbtGreen * y_multiplier);
                    y_rgbtBlue += (current_neighbour.rgbtBlue * y_multiplier);
                }
            }
            // printf("Neighbors: %i %i %i\n", sum_pixel_x.rgbtRed, sum_pixel_x.rgbtGreen, sum_pixel_x.rgbtBlue);
            // Combine x and y via sqrt of x^2 + y^2
            image[i][j].rgbtRed = calc_combined_x_y(x_rgbtRed, y_rgbtRed);
            image[i][j].rgbtGreen = calc_combined_x_y(x_rgbtGreen, y_rgbtGreen);
            image[i][j].rgbtBlue = calc_combined_x_y(x_rgbtBlue, y_rgbtBlue);
            //printf("(%i, %i) pixel: R - %i, G - %i, B - %i\n", i, j, image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
    }
    return;
}
int calc_combined_x_y(int gx, int gy)
{
    int result = round(sqrt(pow(gx, 2) + pow(gy, 2)));
    if (result > 255)
    {
        return 255;
    }
    return result;
}

RGBTRIPLE calc_avg_pixel(RGBTRIPLE list[9], int counter)
{
    RGBTRIPLE avg_pixel;
    float divider = counter;
    int red = 0;
    int green = 0;
    int blue = 0;
    for (int i = 0; i < counter; i++)
    {
        red += list[i].rgbtRed;
        green += list[i].rgbtGreen;
        blue += list[i].rgbtBlue;
    }
    avg_pixel.rgbtRed = round(red / divider);
    avg_pixel.rgbtGreen = round(green / divider);
    avg_pixel.rgbtBlue = round(blue / divider);
    return avg_pixel;
}