/* wavread_Mono_Native.c */

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

/* Read data and insert MONO_PCM_NATIVE struct */
void wavread_Mono_Native(MONO_PCM_NATIVE *mono_pcm_native, char *filename){
    /* Define RIFF struct */
    RIFF *riff = (RIFF *)malloc(sizeof(RIFF));
    
    uint64_t i = 0; /* For loop */
    int32_t *M; /* for intitialize the data vector pointer */

    /* get RIFF struct */
    wavread_RIFF(riff, filename);

    /* copy pcm_spec from riff */
    mono_pcm_native->pcm_spec.fs = riff->fmt.samplesPerSec;
    mono_pcm_native->pcm_spec.bits = riff->fmt.bitsPerSample;
    mono_pcm_native->pcm_spec.length = riff->data.chunkSize / (riff->fmt.bitsPerSample / 8);

    /* initialize the data vector */
    mono_pcm_native->data = (int32_t *)calloc(mono_pcm_native->pcm_spec.length, sizeof(int32_t));
    M = &mono_pcm_native->data[0];

    /* copy data from riff data */
    for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i++){
        *mono_pcm_native->data = riff->data.data[i];

        /* For debug. */
        //printf("%d\n", *mono_pcm_native->data);

        mono_pcm_native->data++;
    }

    /* set the pointer to first */
    mono_pcm_native->data = M;

    /* free RIFF struct */
    free_RIFF(riff);
}