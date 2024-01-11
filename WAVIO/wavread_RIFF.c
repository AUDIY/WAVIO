/* wavread_RIFF.c */

/*----------------------------------------------------
  Copyright (c) 2024 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* include standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

/* include prototype header file */
#include "wavio.h"

/* Read RIFF, fmt, and data chunks */
void wavread_RIFF(RIFF *riff, char *filename){
    FILE *fp; /* File pointer */
    uint64_t i = 0; /* for loop */
    int32_t *init_data; /* For initialize the pointer */
    int32_t x;
    int16_t xx;

    /* open the file */
    fp = fopen(filename, "rb");

    /* judge if the file equals to RIFF chunk */
    fread(riff->chunkID, 1, 4, fp);

    /* if the file doesn't have RIFF format */
    if(strncmp(riff->chunkID, "RIFF", 4) != 0){
        /* Throw the error and end the program. */
        printf("Error!: The file does not have RIFF chunk.\n");
        free(riff);
        exit(1);
    }

    /* Read each chunk */
    fread(&riff->chunkSize, 4, 1, fp);
    fread(riff->formType, 1, 4, fp);

    /* if the file is not WAV file. */
    if(strncmp(riff->formType, "WAVE", 4) != 0){
        /* Throw the error and end the program. */
        printf("Error!: The file is not WAV file.\n");
        free(riff);
        exit(1);
    }

    /* jump unnecessary chunks. */
    fread(riff->fmt.chunkID, 1, 4, fp);
    while(strncmp(riff->fmt.chunkID, "fmt ", 4) != 0){
        /* jump every 1 bite until find the "fmt " chunk */
        fseek(fp, -3, SEEK_CUR);
        fread(riff->fmt.chunkID, 1, 4, fp);
    }

    /* Read fmt chunk */
    fread(&riff->fmt.chunkSize, 4, 1, fp);
    fread(&riff->fmt.waveFormatType, 2, 1, fp);
    fread(&riff->fmt.channel, 2, 1, fp);
    fread(&riff->fmt.samplesPerSec, 4, 1, fp);
    fread(&riff->fmt.bytesPerSec, 4, 1, fp);
    fread(&riff->fmt.blockSize, 2, 1, fp);
    fread(&riff->fmt.bitsPerSample, 2, 1, fp);

    /* jump unnecessary chunks. */
    fread(riff->data.chunkID, 1, 4, fp);
    while (strncmp(riff->data.chunkID, "data", 4) != 0){
        fseek(fp, -3, SEEK_CUR);
        fread(riff->data.chunkID, 1, 4, fp);
    }

    /* Read data chunk */
    fread(&riff->data.chunkSize, 4, 1, fp);

    /* Define data vector */
    riff->data.data = (int32_t *)calloc((unsigned)riff->data.chunkSize / (riff->fmt.bitsPerSample / 8), sizeof(int32_t));
    init_data = &riff->data.data[0];

    switch (riff->fmt.bitsPerSample)
    {
        /* 8bit (unsigned) */
        case 8:
            for(i = 0; i < riff->data.chunkSize; i++){
                xx = 0;
                fread(&xx, 1, 1, fp);
                *riff->data.data = xx;
                //printf("%d\n", *riff->data.data);
                riff->data.data++;
            }
            riff->data.data = init_data;
            break;
    
        /* 16bit (signed) */
        case 16:
            for(i = 0; i < riff->data.chunkSize / 2; i++){
                xx = 0;
                fread(&xx, 2, 1, fp);
                *riff->data.data = xx;
                //printf("%d\n", *riff->data.data);
                riff->data.data++;
            }
            riff->data.data = init_data;
            break;

        /* 24bit (signed) */
        case 24:
            for(i = 0; i < riff->data.chunkSize / 3; i++){
                x = 0;
                fread(&x, 3, 1, fp);

                if(x >= 0x800000){
                    x -= 0x1000000;
                }

                *riff->data.data = x;
                //printf("%d\n", *riff->data.data);
                riff->data.data++;
            }
            riff->data.data = init_data;
            break;

        /* 32bit (signed) */
        case 32:
            for(i = 0; i < riff->data.chunkSize / 4; i++){
                x = 0;
                fread(&x, 4, 1, fp);
                *riff->data.data = x;
                //printf("%d\n", *riff->data.data);
                riff->data.data++;
            }
            riff->data.data = init_data;
            break;

        /* Error */
        default:
            printf("Error!: Inappropriate quantization bit number.\n");
            free_RIFF(riff);
            exit(1);
            break;
    }

    /* Close file */
    fclose(fp);
}