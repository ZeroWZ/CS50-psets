#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Can't open %s", argv[1]);
        return 1;
    }

    BYTE *block = malloc(sizeof(BYTE) * BLOCK_SIZE);
    if (block == NULL)
    {
        printf("There isn't enough memory.\n");
        fclose(card);
        return 1;
    }

    char *filename = calloc(8, sizeof(char));
    if (filename == NULL)
    {
        printf("There isn't enough memory.\n");
        fclose(card);
        free(block);
        return 1;
    }

    FILE *img = NULL;
    int i = 0;
    while (fread(block, BLOCK_SIZE, 1, card))
    {
        if (block[0] == 0xff && block[1] == 0xd8 &&  block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (i > 0)
                fclose(img);
            sprintf(filename, "%03i.jpg", i);
            img = fopen(filename, "w");
            i++;
            fwrite(block, 1, BLOCK_SIZE, img);
        }
        else if (i > 0)
        {
            fwrite(block, 1, BLOCK_SIZE, img);
        }
    }

    fclose(card);
    fclose(img);
    free(block);
    free(filename);
}