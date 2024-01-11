/* free_Mono.c */

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

/* Free MONO_PCM struct */
void free_Mono(MONO_PCM *mono_pcm){
    /* free MONO_PCM data vector */
    free(mono_pcm->data);

    /* free MONO_PCM struct */
    free(mono_pcm);
}