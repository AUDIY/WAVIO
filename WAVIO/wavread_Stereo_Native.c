/* wavread_Stereo_Native.c */

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

/* Read and insert STEREO_PCM_NATIVE data */
void wavread_Stereo_Native(STEREO_PCM_NATIVE *stereo_pcm_native, char *filename){
    /* Define RIFF struct */
    RIFF *riff = (RIFF *)malloc(sizeof(RIFF));

    uint64_t i = 0; /* For loop */
    int32_t *L, *R; /* For initialize the data vector */

    /* get RIFF struct data */
    wavread_RIFF(riff, filename);

    /* copy pcm_spec */
    stereo_pcm_native->pcm_spec.fs = riff->fmt.samplesPerSec;
    stereo_pcm_native->pcm_spec.bits = riff->fmt.bitsPerSample;
    stereo_pcm_native->pcm_spec.length = riff->data.chunkSize / (2 * (riff->fmt.bitsPerSample / 8));

    /* initialize the data vector */
    stereo_pcm_native->data[0] = (int32_t *)calloc(stereo_pcm_native->pcm_spec.length, sizeof(int32_t));
    stereo_pcm_native->data[1] = (int32_t *)calloc(stereo_pcm_native->pcm_spec.length, sizeof(int32_t));
    L = &stereo_pcm_native->data[0][0];
    R = &stereo_pcm_native->data[1][0];

    /* copy data vector from riff */
    for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i += 2){
        *stereo_pcm_native->data[0] = riff->data.data[i];
        *stereo_pcm_native->data[1] = riff->data.data[i+1];

        /* For debug. */
        //printf("%d, %d\n", *stereo_pcm_native->data[0], *stereo_pcm_native->data[1]);

        stereo_pcm_native->data[0]++;
        stereo_pcm_native->data[1]++;
    }

    /* reset vector index */
    stereo_pcm_native->data[0] = L;
    stereo_pcm_native->data[1] = R;

    /* free RIFF struct */
    free_RIFF(riff);
}