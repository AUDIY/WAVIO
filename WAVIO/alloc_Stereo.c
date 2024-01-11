/* alloc_Stereo.c */

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

/* Allocate STEREO_PCM struct */
STEREO_PCM *alloc_Stereo(void){
    /* allocate STEREO_PCM struct */
    STEREO_PCM *stereo_pcm = (STEREO_PCM *)malloc(sizeof(STEREO_PCM));

    /* pointer for data vector */
    stereo_pcm->data[0] = NULL;
    stereo_pcm->data[1] = NULL;

    return stereo_pcm;
}