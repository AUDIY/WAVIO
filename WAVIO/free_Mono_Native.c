/* free_Mono_Native.c */

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

/* Free MONO_PCM_NATIVE struct */
void free_Mono_Native(MONO_PCM_NATIVE *mono_pcm_native){
    /* free MONO_PCM_NATIVE data vector */
    free(mono_pcm_native->data);

    /* free MONO_PCM_NATIVE struct */
    free(mono_pcm_native);
}