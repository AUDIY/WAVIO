/* wavwrite_RIFF.c */

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

/* save WAV file from RIFF struct */
void wavwrite_RIFF(RIFF *riff, char *filename){
    /* variable */
    FILE *fp; /* for write wav file */
    uint64_t i = 0; /* for loop */
    int32_t *init_data; /* for initialize data vector */

    /* open file name with writing name */
    fp = fopen(filename, "wb");

    /* write each chunk */
    fwrite(riff->chunkID, 1, 4, fp); /* "RIFF" */
    fwrite(&riff->chunkSize, 4, 1, fp);
    fwrite(riff->formType, 1, 4, fp); /* "WAVE" */
    fwrite(riff->fmt.chunkID, 1, 4, fp); /* "fmt " */
    fwrite(&riff->fmt.chunkSize, 4, 1, fp);
    fwrite(&riff->fmt.waveFormatType, 2, 1, fp); /* PCM: 1 */
    fwrite(&riff->fmt.channel, 2, 1, fp); /* Mono: 1, Stereo: 2 */
    fwrite(&riff->fmt.samplesPerSec, 4, 1, fp); /* Sampling frequency */
    fwrite(&riff->fmt.bytesPerSec, 4, 1, fp);
    fwrite(&riff->fmt.blockSize, 2, 1, fp);
    fwrite(&riff->fmt.bitsPerSample, 2, 1, fp); /* Quantization bit */
    fwrite(riff->data.chunkID, 1, 4, fp);
    fwrite(&riff->data.chunkSize, 4, 1, fp); /* data */

    /* Define data vector */
    init_data = &riff->data.data[0];

    /* write data */
    switch(riff->fmt.bitsPerSample){
        case 8:
            /* 8bit integer(unsigned) */
            for(i = 0; i < riff->data.chunkSize; i++){
                /* clipping */
                if(riff->data.data[i] > 255){
                    riff->data.data[i] = 255;
                }else if(riff->data.data[i] < 0){
                    riff->data.data[i] = 0;
                }

                /* write data */
                fwrite(&riff->data.data[i], 1, 1, fp);
            }
            break;

        case 16:
            /* 16bit integer(signed) */
            for(i = 0; i < riff->data.chunkSize / 2; i++){
                /* clipping */
                if(riff->data.data[i] > 32767){
                    riff->data.data[i] = 32767;
                }else if(riff->data.data[i] < -32768){
                    riff->data.data[i] = -32768;
                }

                /* write data */
                fwrite(&riff->data.data[i], 2, 1, fp);
            }
            break;

        case 24:
            /* 24bit integer(signed) */
            for(i = 0; i < riff->data.chunkSize / 3; i++){
                /* clipping */
                if(riff->data.data[i] > 8388607){
                    riff->data.data[i] = 8388607;
                }else if(riff->data.data[i] < -8388608){
                    riff->data.data[i] = -8388608;
                }

                /* write data */
                fwrite(&riff->data.data[i], 3, 1, fp);
            }
            break;

        case 32:
            for(i = 0; i < riff->data.chunkSize / 4; i++){
                /* clipping */
                if(riff->data.data[i] > (int64_t)(pow(2.0, 31.0) - 1)){
                    riff->data.data[i] = (int32_t)(pow(2.0, 31.0) - 1);
                }else if(riff->data.data[i] < (int64_t)(-1 * pow(2.0, 31.0))){
                    riff->data.data[i] = -1 * (int32_t)(pow(2.0, 31.0));
                }

                /* write data */
                fwrite(&riff->data.data[i], 4, 1, fp);
            }
            break;

        default:
            printf("Error!: Inappropriate quantization bit number.\n");
            exit(1);
            break;
    }

    /* set the pointer to first */
    riff->data.data = init_data;

    /* save WAV file */
    fclose(fp);
}