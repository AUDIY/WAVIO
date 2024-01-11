/* wavwrite_Stereo_Native.c */

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

/* save WAV file from STEREO_PCM_NATIVE struct */
void wavwrite_Stereo_Native(STEREO_PCM_NATIVE *stereo_pcm_native, char *filename){
    /* variables */
    RIFF *riff; /* for make RIFF struct */
    uint64_t i; /* for loop */
    int32_t *L, *R; /* for initialize the pointer */

    /* Define RIFF struct */
    riff = (RIFF *)malloc(sizeof(RIFF));

    /* RIFF chunk ID ("RIFF") */
    riff->chunkID[0] = 'R';
    riff->chunkID[1] = 'I';
    riff->chunkID[2] = 'F';
    riff->chunkID[3] = 'F';

    /* RIFF format type ("WAVE") */
    riff->formType[0] = 'W';
    riff->formType[1] = 'A';
    riff->formType[2] = 'V';
    riff->formType[3] = 'E';

    /* fmt chunk ID ("fmt ") */
    riff->fmt.chunkID[0] = 'f';
    riff->fmt.chunkID[1] = 'm';
    riff->fmt.chunkID[2] = 't';
    riff->fmt.chunkID[3] = ' ';

    /* fmt chunksize (16) */
    riff->fmt.chunkSize = 16;

    /* fmt waveformattype (1: PCM) */
    riff->fmt.waveFormatType = 1;

    /* fmt channel (2: Stereo) */
    riff->fmt.channel = 2;

    /* fmt samplespersec (sampling frequency)*/
    riff->fmt.samplesPerSec = stereo_pcm_native->pcm_spec.fs;

    /* fmt blocksize */
    riff->fmt.blockSize = 2 * (stereo_pcm_native->pcm_spec.bits / 8);

    /* fmt bytespersec */
    riff->fmt.bytesPerSec = riff->fmt.blockSize * riff->fmt.samplesPerSec;

    /* fmt bitspersample */
    riff->fmt.bitsPerSample = stereo_pcm_native->pcm_spec.bits;

    /* data chunkID */
    riff->data.chunkID[0] = 'd';
    riff->data.chunkID[1] = 'a';
    riff->data.chunkID[2] = 't';
    riff->data.chunkID[3] = 'a';

    /* calculate each chunksize */
    riff->data.chunkSize = 2 * stereo_pcm_native->pcm_spec.length * (riff->fmt.bitsPerSample / 8);
    riff->chunkSize = riff->data.chunkSize + 36;

    /* copy data and calculate data chunk size */
    /* for initialize pointer */
    L = stereo_pcm_native->data[0]; 
    R = stereo_pcm_native->data[1];

    /* define riff data vector */
    riff->data.data = (int32_t *)calloc((unsigned)riff->data.chunkSize / (riff->fmt.bitsPerSample / 8), sizeof(int32_t));

    for (i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i += 2){
        /* copy data */
        riff->data.data[i] = *stereo_pcm_native->data[0];
        riff->data.data[i + 1] = *stereo_pcm_native->data[1];

        /* next pointer */
        stereo_pcm_native->data[0]++;
        stereo_pcm_native->data[1]++;
    }

    /* initialize the pointer */
    stereo_pcm_native->data[0] = L;
    stereo_pcm_native->data[1] = R;

    /* wavwrite from RIFF struct */
    wavwrite_RIFF(riff, filename);

    /* free RIFF struct */
    free_RIFF(riff);
}