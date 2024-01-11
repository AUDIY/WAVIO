/* alloc_RIFF.c */

/*----------------------------------------------------
  Copyright (c) 2024 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

/* Include wavio.h */
#include "wavio.h"

/* Allocate RIFF struct */
RIFF *alloc_RIFF(void){
    /* allocate RIFF struct */
    RIFF *riff = (RIFF *)malloc(sizeof(RIFF));

    /* pointer for RIFF data vector */
    riff->data.data = NULL;

    return riff;
}