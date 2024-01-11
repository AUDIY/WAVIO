/* wavwrite_Mono.c */

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
void wavwrite_Mono(MONO_PCM *mono_pcm, char *filename){
    /* variables */
    RIFF *riff;   /* for write wav file from RIFF struct */
    uint64_t i;   /* for loop */
    double *data; /* for initialize the pointer */

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
    riff->fmt.samplesPerSec = mono_pcm->pcm_spec.fs;

    /* fmt blocksize */
    riff->fmt.blockSize = (mono_pcm->pcm_spec.bits / 8);

    /* fmt bytespersec */
    riff->fmt.bytesPerSec = riff->fmt.blockSize * riff->fmt.samplesPerSec;

    /* fmt bitspersample(Quantization bit) */
    riff->fmt.bitsPerSample = mono_pcm->pcm_spec.bits;

    /* data chunk ID ("data") */
    riff->data.chunkID[0] = 'd';
    riff->data.chunkID[1] = 'a';
    riff->data.chunkID[2] = 't';
    riff->data.chunkID[3] = 'a';

    /* data chunk size */
    riff->data.chunkSize = mono_pcm->pcm_spec.length * (riff->fmt.bitsPerSample / 8);
    riff->chunkSize = riff->data.chunkSize + 36;

    /* set the pointer for initialize */
    data = &mono_pcm->data[0];

    /* define data vector */
    riff->data.data = (int32_t *)calloc(riff->data.chunkSize / (riff->fmt.bitsPerSample / 8), sizeof(int32_t));

    if(mono_pcm->pcm_spec.bits == 8){
        for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i++){
            /* clipping */
            if(*mono_pcm->data < -1.0){
                *mono_pcm->data = -1.0;
            }else if(*mono_pcm->data >1.0){
                *mono_pcm->data = 1.0;
            }

            /* copy data */
            riff->data.data[i] = (int32_t)(floor(floor(((*mono_pcm->data + 1.0) / 2.0) * (pow(2.0, (double)riff->fmt.bitsPerSample) - 1.0) + 0.5)));
        
            /* next pointer */
            mono_pcm->data++;
        }
    }else{
        for (i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i++){
            /* clipping */
            if (*mono_pcm->data < -1.0){
                *mono_pcm->data = -1.0;
            }else if (*mono_pcm->data > 1.0){
                *mono_pcm->data = 1.0;
            }

            /* copy data */
            riff->data.data[i] = (int32_t)(floor(((*mono_pcm->data + 1.0) / 2.0) * (pow(2.0, (double)riff->fmt.bitsPerSample) - 1.0) + 0.5) - (pow(2.0, (double)riff->fmt.bitsPerSample - 1.0)));
        
            /* next pointer */
            mono_pcm->data++;
        }
    }

    /* reset pointer */
    mono_pcm->data = data;

    /* save wav file from riff struct */
    wavwrite_RIFF(riff, filename);

    /* free riff struct */
    free_RIFF(riff);
}