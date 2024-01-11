/* wavread_Mono.c */

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

/* Read data and insert MONO_PCM struct */
void wavread_Mono(MONO_PCM *mono_pcm, char *filename){
    /* Define RIFF struct */
    RIFF *riff = (RIFF *)malloc(sizeof(RIFF));

    uint64_t i = 0; /* For loop */
    double *M; /* for initialize the data vector pointer */

    /* get RIFF struct */
    wavread_RIFF(riff, filename);

    /* copy PCM_SPEC from RIFF */
    mono_pcm->pcm_spec.fs = riff->fmt.samplesPerSec;
    mono_pcm->pcm_spec.bits = riff->fmt.bitsPerSample;
    mono_pcm->pcm_spec.length = riff->data.chunkSize / (riff->fmt.bitsPerSample / 8);

    /* initialize the data vector */
    mono_pcm->data = (double *)calloc(mono_pcm->pcm_spec.length, sizeof(double));
    M = &mono_pcm->data[0];

    /* copy data from riff */
    /* if 8bit, because its data have unsigned. */
    if(riff->fmt.bitsPerSample == 8){
        for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i++){
            *mono_pcm->data = (double)(riff->data.data[i] - 128);

            /* Convert to normalized float [-1.0, 1.0]. */
            if(*mono_pcm->data >= 0){
                *mono_pcm->data /= (pow(2.0, (double)mono_pcm->pcm_spec.bits - 1.0) - 1.0);
            }else{
                *mono_pcm->data /= (pow(2.0, (double)mono_pcm->pcm_spec.bits - 1.0));
            }

            mono_pcm->data++;
        }
    }else{
        /* 16, 24, and 32bit */
        for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i++){
            *mono_pcm->data = (double)riff->data.data[i];

            /* Convert to normalized float [-1.0, 1.0]. */
            if(*mono_pcm->data >= 0){
                *mono_pcm->data /= (pow(2.0, (double)mono_pcm->pcm_spec.bits - 1.0) - 1.0);
            }else{
                *mono_pcm->data /= (pow(2.0, (double)mono_pcm->pcm_spec.bits - 1.0));
            }

            mono_pcm->data++;
        }
    }

    /* set the pointer to first */
    mono_pcm->data = M;

    /* free RIFF struct */
    free_RIFF(riff);
}