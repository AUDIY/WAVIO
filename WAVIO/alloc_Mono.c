/* alloc_Mono.c */

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

/* Allocate MONO_PCM struct */
MONO_PCM *alloc_Mono(void){
    /* allocate MONO_PCM struct */
    MONO_PCM *mono_pcm = (MONO_PCM *)malloc(sizeof(MONO_PCM));

    /* pointer for data vector */
    mono_pcm->data = NULL;

    return mono_pcm;
}