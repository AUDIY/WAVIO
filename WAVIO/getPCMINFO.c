/* getPCMINFO.c */

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

/* Read PCMINFO */
void getPCMINFO(PCMINFO *pcminfo, char *filename){
    /* Define RIFF struct */
    RIFF *riff = (RIFF *)malloc(sizeof(RIFF));

    /* get RIFF struct data */
    wavread_RIFF(riff, filename);

    /* copy properties */
    pcminfo->filename = filename;
    pcminfo->fs = riff->fmt.samplesPerSec;
    pcminfo->bits = riff->fmt.bitsPerSample;
    pcminfo->channel = riff->fmt.channel;

    /* free RIFF struct */
    free_RIFF(riff);
}