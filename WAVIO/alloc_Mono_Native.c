/* alloc_Mono_Native.c */

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

/* Allocate MONO_PCM_NATIVE struct */
MONO_PCM_NATIVE *alloc_Mono_Native(void){
    /* allocate MONO_PCM_NATIVE struct */
    MONO_PCM_NATIVE *mono_pcm_native = (MONO_PCM_NATIVE *)malloc(sizeof(MONO_PCM_NATIVE));

    /* pointer for data vector */
    mono_pcm_native->data = NULL;

    return mono_pcm_native;
}