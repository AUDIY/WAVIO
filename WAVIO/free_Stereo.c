/* free_Stereo.c */

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

/* Free STEREO_PCM struct */
void free_Stereo(STEREO_PCM *stereo_pcm){
    /* free STEREO_PCM data vector */
    free(stereo_pcm->data[0]);
    free(stereo_pcm->data[1]);

    /* free STEREO_PCM struct */
    free(stereo_pcm);
}