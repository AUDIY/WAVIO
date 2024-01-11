/* wavread_Stereo.c */

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

/* Read data and insert STEREO_PCM struct */
void wavread_Stereo(STEREO_PCM *stereo_pcm, char *filename){
    /* Define RIFF struct */
    RIFF *riff = (RIFF *)malloc(sizeof(RIFF));

    uint64_t i = 0; /* For loop */
    double *L, *R; /* for initialize the pointer */

    /* get RIFF struct data */
    wavread_RIFF(riff, filename);

    /* copy PCM properties */
    stereo_pcm->pcm_spec.fs = riff->fmt.samplesPerSec;
    stereo_pcm->pcm_spec.bits = riff->fmt.bitsPerSample;
    stereo_pcm->pcm_spec.length = riff->data.chunkSize / (2 * (riff->fmt.bitsPerSample / 8));

    /* initialize the data vector */
    stereo_pcm->data[0] = (double *)calloc(stereo_pcm->pcm_spec.length, sizeof(double));
    stereo_pcm->data[1] = (double *)calloc(stereo_pcm->pcm_spec.length, sizeof(double));
    L = stereo_pcm->data[0];
    R = stereo_pcm->data[1];

    /* copy data from riff */
    /* if 8bit, because its data have unsigned. */
    if(riff->fmt.bitsPerSample == 8){
        for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i += 2){
            *stereo_pcm->data[0] = (double)(riff->data.data[i] - 128);
            *stereo_pcm->data[1] = (double)(riff->data.data[i+1] - 128);

            /* For debug */
            //printf("%lf, %lf\n", *stereo_pcm->data[0], *stereo_pcm->data[1]);
            
            /* Convert to normalized float [-1.0, 1.0]. */
            /* Left */
            if(*stereo_pcm->data[0] >= 0){
                *stereo_pcm->data[0] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0) - 1.0);
            }else{
                *stereo_pcm->data[0] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0));
            }
            /* Right */
            if(*stereo_pcm->data[1] >= 0){
                *stereo_pcm->data[1] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0) - 1.0);
            }else{
                *stereo_pcm->data[1] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0));
            }
            
            /* For debug */
            //printf("%lf, %lf\n", *stereo_pcm->data[0], *stereo_pcm->data[1]);

            stereo_pcm->data[0]++;
            stereo_pcm->data[1]++;
        }
    }else{
        /* 16, 24, and 32bit */
        for (i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i += 2){
            *stereo_pcm->data[0] = (double)riff->data.data[i];
            *stereo_pcm->data[1] = (double)riff->data.data[i+1];

            /* For debug */
            //printf("%lf, %lf\n", *stereo_pcm->data[0], *stereo_pcm->data[1]);

            /* Convert to normalized float [-1.0, 1.0]. */
            /* Left */
            if(*stereo_pcm->data[0] >= 0){
                *stereo_pcm->data[0] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0) - 1.0);
            }else{
                *stereo_pcm->data[0] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0));
            }
            /* Right */
            if(*stereo_pcm->data[1] >= 0){
                *stereo_pcm->data[1] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0) - 1.0);
            }else{
                *stereo_pcm->data[1] /= (pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0));
            }
            
            /* For debug. */
            //printf("%lf, %lf\n", *stereo_pcm->data[0], *stereo_pcm->data[1]);

            stereo_pcm->data[0]++;
            stereo_pcm->data[1]++;
        }
    }

    /* reset vector index */
    stereo_pcm->data[0] = L;
    stereo_pcm->data[1] = R;

    /* free RIFF struct */
    free_RIFF(riff);

}