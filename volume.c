//volume.c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef int16_t TWO_BYTE;

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{   
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if(input == NULL)
    {
        printf("Could not open file. \n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if(output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);   

    BYTE header[HEADER_SIZE];
    TWO_BYTE sample;
    
    /*
    if (fread(&header, sizeof(BYTE), HEADER_SIZE, input) != HEADER_SIZE)
    {
        fprintf(stderr, "Error reading header.\n");
        fclose(input);
        fclose(output);
        return 1;
    }
    fwrite(&header, sizeof(BYTE), HEADER_SIZE, output);
    */

    fread(&header, sizeof(BYTE), HEADER_SIZE, input);
    fwrite(&header, sizeof(BYTE), HEADER_SIZE, output);

    
    /*
    while(fread(&sample, sizeof(TWO_BYTE), 1, input) == 1)
    {
        int temp = (int)(sample * factor);
        if (temp > 32767) temp = 32767;
        if (temp < -32768) temp = -32768;
        sample = (TWO_BYTE) temp;
        
        fwrite(&sample, sizeof(TWO_BYTE), 1, output);  
    }
    */

    while (fread(&sample, sizeof(sample), 1, input))
    {
        sample *= factor;
        fwrite(&sample, sizeof(sample), 1, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}