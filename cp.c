#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./copy source destination\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (dst == NULL)
    {
        printf("Could not create %s.\n", argv[2]);
        fclose(src);
        return 3;
    }

    BYTE b;
    while (fread(&b, sizeof(BYTE), 1, src) == 1)
    {
        fwrite(&b, sizeof(BYTE), 1, dst);
    }

    fclose(dst);
    fclose(src);

    return 0;
}
