/* wavwrite_Stereo.c */

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

/* save WAV file from STEREO_PCM struct */
void wavwrite_Stereo(STEREO_PCM *stereo_pcm, char *filename){
    /* variables */
    RIFF *riff;    /* riff struct */
    uint64_t i;    /* for loop */
    double *L, *R; /* for initialize index */

    /* initialize riff struct */
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

    /* fmt channel (2: Stereo) */
    riff->fmt.channel = 2;

    /* fmt samplespersec (sampling frequency) */
    riff->fmt.samplesPerSec = stereo_pcm->pcm_spec.fs;

    /* fmt blocksize */
    riff->fmt.blockSize = 2 * (stereo_pcm->pcm_spec.bits / 8);

    /* fmt bytespersec */
    riff->fmt.bytesPerSec = riff->fmt.blockSize * riff->fmt.samplesPerSec;

    /* fmt bitspersample (Quantization bits) */
    riff->fmt.bitsPerSample = stereo_pcm->pcm_spec.bits;

    /* data chunk ID ("data") */
    riff->data.chunkID[0] = 'd';
    riff->data.chunkID[1] = 'a';
    riff->data.chunkID[2] = 't';
    riff->data.chunkID[3] = 'a';

    /* data chunk size */
    riff->data.chunkSize = 2 * stereo_pcm->pcm_spec.length * (riff->fmt.bitsPerSample / 8);
    riff->chunkSize = riff->data.chunkSize + 36;

    /* For initialize pointer */
    L = stereo_pcm->data[0];
    R = stereo_pcm->data[1];

    /* Define riff data vector */
    riff->data.data = (int32_t *)calloc((unsigned)riff->data.chunkSize / (riff->fmt.bitsPerSample / 8), sizeof(int32_t));

    /* copy data */
    if(stereo_pcm->pcm_spec.bits == 8){
        /* 8bit (unsigned) */
        for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i += 2){
            /* For debug */
            //printf("%p: %f, %f\n", stereo_pcm->data[0], *stereo_pcm->data[0], *stereo_pcm->data[1]);

            /* clipping */
            /* Left */
            if(*stereo_pcm->data[0] < -1.0){
                *stereo_pcm->data[0] = -1.0;
            }else if(*stereo_pcm->data[0] > 1.0){
                *stereo_pcm->data[0] = 1.0;
            }
            /* Right */
            if (*stereo_pcm->data[1] < -1.0){
                *stereo_pcm->data[1] = -1.0;
            }else if(*stereo_pcm->data[1] > 1.0){
                *stereo_pcm->data[1] = 1.0;
            }

            /* 8bit (unsigned) */
            riff->data.data[i] = (int32_t)(floor(((*stereo_pcm->data[0] + 1.0) / 2.0) * (pow(2.0, (double)stereo_pcm->pcm_spec.bits) - 1.0) + 0.5));
            riff->data.data[i + 1] = (int32_t)(floor(((*stereo_pcm->data[1] + 1.0) / 2.0) * (pow(2.0, (double)stereo_pcm->pcm_spec.bits) - 1.0) + 0.5));

            /* For debug*/
            //printf("%lf -> %d, %lf -> %d\n", *stereo_pcm->data[0], riff->data.data[i], *stereo_pcm->data[1], riff->data.data[i+1]);

            /* next pointer */
            stereo_pcm->data[0]++;
            stereo_pcm->data[1]++;
        }
    }else{
        /* 16, 24, and 32bit */
        for(i = 0; i < riff->data.chunkSize / (riff->fmt.bitsPerSample / 8); i += 2){

            /* clipping */
            /* Left */
            if (*stereo_pcm->data[0] < -1.0){
                *stereo_pcm->data[0] = -1.0;
            }else if (*stereo_pcm->data[0] > 1.0){
                *stereo_pcm->data[0] = 1.0;
            }

            if (*stereo_pcm->data[1] < -1.0){
                *stereo_pcm->data[1] = -1.0;
            }else if (*stereo_pcm->data[1] > 1.0){
                *stereo_pcm->data[1] = 1.0;
            }

            /* copy data */
            riff->data.data[i] = (int32_t)(floor(((*stereo_pcm->data[0] + 1.0) / 2.0) * (pow(2.0, (double)stereo_pcm->pcm_spec.bits) - 1.0) + 0.5) - pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0));
            riff->data.data[i + 1] = (int32_t)(floor(((*stereo_pcm->data[1] + 1.0) / 2.0) * (pow(2.0, (double)stereo_pcm->pcm_spec.bits) - 1.0) + 0.5) - pow(2.0, (double)stereo_pcm->pcm_spec.bits - 1.0));
            
            /* For debug. */
            //printf("%lf -> %d, %lf -> %d\n", *stereo_pcm->data[0], riff->data.data[i], *stereo_pcm->data[1], riff->data.data[i+1]);

            /* next pointer */
            stereo_pcm->data[0]++;
            stereo_pcm->data[1]++;
        }
    }

    /* initialize the pointer */
    stereo_pcm->data[0] = L;
    stereo_pcm->data[1] = R;

    /* wavwrite from riff struct */
    wavwrite_RIFF(riff, filename);

    /* free riff struct */
    free_RIFF(riff);
}