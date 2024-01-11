/* free_Stereo_Native.c */

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

/* Free STEREO_PCM_NATIVE struct */
void free_Stereo_Native(STEREO_PCM_NATIVE *stereo_pcm_native){
    /* free STEREO_PCM_NATIVE data vector */
    free(stereo_pcm_native->data[0]);
    free(stereo_pcm_native->data[1]);

    /* free STEREO_PCM_NATIVE struct */
    free(stereo_pcm_native);
}