#include "cs50.h"
#include "ctype.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void stair_way_to_heaven2(void);

int main(void)
{
    stair_way_to_heaven2();
}

void stair_way_to_heaven2()
{
    int hight;

    do
    {
        // Get valid input
        hight = get_int("how high are you? ");

    } while (hight < 1);

    // Build each row
    for (int row = 1; row <= hight; row++)
    {
        // Left spaces
        for (int s = 0; s < hight - row; s++)
        {
            printf(" ");
        }

        // Left hashes
        for (int h = 0; h < row; h++)
        {
            printf("#");
        }

        // Gap
        printf("");

        // Right hashes
        for (int h = 0; h < row; h++)
        {
            printf("#");
        }

        // Newline after each row
        printf("\n");


    }

}