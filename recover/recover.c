#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool isJPEG(BYTE buffer[])
{
    return buffer[0] == 0xff &&
           buffer[1] == 0xd8 &&
           buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0;
}
 
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 1;
    }

    char filename[8];
    BYTE buffer[512];
    int count = 0;
    FILE *img = NULL;
     
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
         if(isJPEG(buffer))
         {
            if(img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03d.jpg", count);
            img = fopen(filename, "w");
            count++;
         }

         if(img != NULL)
         {
            fwrite(buffer, sizeof(BYTE), 512, img);        
         }
            

    }

    if (img != NULL) {fclose(img);}
    
    fclose(file);
    return 0;
}