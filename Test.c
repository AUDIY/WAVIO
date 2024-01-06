#include <stdio.h>
#include "wavio.h"

int main(void){
    //RIFF *riff;
    STEREO_PCM *stereo_pcm;
    char *filename = "TestSound_48000_8.wav";

    stereo_pcm = alloc_Stereo();

    wavread_Stereo(stereo_pcm, filename);
    free_Stereo(stereo_pcm);

    return 0;
}