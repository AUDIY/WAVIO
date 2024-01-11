/* free_RIFF.c */

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

/* Free RIFF struct */
void free_RIFF(RIFF *riff){
    /* free RIFF data vector */
    free(riff->data.data);

    /* free RIFF struct */
    free(riff);
}