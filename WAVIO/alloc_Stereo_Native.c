/* alloc_Stereo_Native.c */

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

//Allocate STEREO_PCM_NATIVE struct
STEREO_PCM_NATIVE *alloc_Stereo_Native(void){
    //allocate STEREO_PCM_NATIVE struct
    STEREO_PCM_NATIVE *stereo_pcm_native = (STEREO_PCM_NATIVE *)malloc(sizeof(STEREO_PCM_NATIVE));

    //pointer for STEREO_PCM_NATIVE data vector
    stereo_pcm_native->data[0] = NULL;
    stereo_pcm_native->data[1] = NULL;

    return stereo_pcm_native;
}