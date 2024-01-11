/* wavwrite_Mono_Native.c */

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

/* save WAV file from MONO_PCM_NATIVE struct */
void wavwrite_Mono_Native(MONO_PCM_NATIVE *mono_pcm_native, char *filename){
    /* variables */
    RIFF *riff; /* for write wav file from RIFF struct */
    uint64_t i; /* for loop */
    int32_t *data;  /* for initialize the pointer */

    /* initialize RIFF struct */
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

    /* fmt chunk size (16) */
    riff->fmt.chunkSize = 16;

    /* fmt wavefmttype (1: PCM) */
    riff->fmt.waveFormatType = 1;

    /* fmt channel (1: Mono) */
    riff->fmt.channel = 1;

    /* fmt samplespersec (sampling frequency) */
    riff->fmt.samplesPerSec = mono_pcm_native->pcm_spec.fs;

    /* fmt blocksize */
    riff->fmt.blockSize = (mono_pcm_native->pcm_spec.bits / 8);

    /* fmt bytespersec */
    riff->fmt.bytesPerSec = riff->fmt.blockSize * riff->fmt.samplesPerSec;

    /* fmt bitspersample(Quantization bit) */
    riff->fmt.bitsPerSample = mono_pcm_native->pcm_spec.bits;

    /* data chunk ID ("data") */
    riff->data.chunkID[0] = 'd';
    riff->data.chunkID[1] = 'a';
    riff->data.chunkID[2] = 't';
    riff->data.chunkID[3] = 'a';

    /* data chunk size */
    riff->data.chunkSize = mono_pcm_native->pcm_spec.length * (riff->fmt.bitsPerSample / 8);
    riff->chunkSize = riff->data.chunkSize + 36;

    /* set the pointer for initialize */
    data = &mono_pcm_native->data[0];

    /* define data vector */
    riff->data.data = (int32_t *)calloc((unsigned)riff->data.chunkSize / (riff->fmt.bitsPerSample / 8), sizeof(int32_t));

    for (i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i++){
        /* copy data */
        riff->data.data[i] = *mono_pcm_native->data;

        /* next pointer */
        mono_pcm_native->data++;
    }

    /* reset pointer */
    mono_pcm_native->data = data;

    /* save wav file from riff struct */
    wavwrite_RIFF(riff, filename);

    /* free riff struct */
    free_RIFF(riff);
}