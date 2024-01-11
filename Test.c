#include <stdio.h>
#include <stdlib.h>

#include "wavio.h"

int main(void){
    RIFF *riffS;
    RIFF *riffM;
    PCMINFO *pcminfo;
    STEREO_PCM *stereo_pcm;
    STEREO_PCM_NATIVE *stereo_pcm_native;
    MONO_PCM *mono_pcm;
    MONO_PCM_NATIVE *mono_pcm_native;

    char *Stereo_filename = "TestSound_96000_24.wav";
    char *Stereo_filenameW = "Test_Stereo.wav";
    char *Stereo_filenameNative = "Test_Stereo_Native.wav";
    char *Stereo_filenameRIFF = "Test_Stereo_RIFF.wav";

    char *Mono_filename = "TestSound_96000_24_Mono.wav";
    char *Mono_filenameW = "Test_Mono.wav";
    char *Mono_filenameNative = "Test_Mono_Native.wav";
    char *Mono_filenameRIFF = "Test_Mono_RIFF.wav";

    /* PCMINFO Check */
    pcminfo = (PCMINFO *)malloc(sizeof(PCMINFO));
    getPCMINFO(pcminfo, Stereo_filename);
    printf("File Name: %s\n", pcminfo->filename);
    printf("Sampling Frequency: %u Hz\n", pcminfo->fs);
    printf("Bits: %u bit\n", pcminfo->bits);
    printf("Channels: %u\n", pcminfo->channel);

    /* STEREO_PCM check */
    stereo_pcm = alloc_Stereo();
    wavread_Stereo(stereo_pcm, Stereo_filename);
    wavwrite_Stereo(stereo_pcm, Stereo_filenameW);
    free_Stereo(stereo_pcm);

    /* STEREO_PCM_NATIVE check */
    stereo_pcm_native = alloc_Stereo_Native();
    wavread_Stereo_Native(stereo_pcm_native, Stereo_filename);
    wavwrite_Stereo_Native(stereo_pcm_native, Stereo_filenameNative);
    free_Stereo_Native(stereo_pcm_native);

    /* MONO_PCM check */
    mono_pcm = alloc_Mono();
    wavread_Mono(mono_pcm, Mono_filename);
    wavwrite_Mono(mono_pcm, Mono_filenameW);
    free_Mono(mono_pcm);

    /* MONO_PCM_NATIVE check */
    mono_pcm_native = alloc_Mono_Native();
    wavread_Mono_Native(mono_pcm_native, Mono_filename);
    wavwrite_Mono_Native(mono_pcm_native, Mono_filenameNative);
    free_Mono_Native(mono_pcm_native);

    /* RIFF check */
    riffS = alloc_RIFF();
    wavread_RIFF(riffS, Stereo_filename);
    wavwrite_RIFF(riffS, Stereo_filenameRIFF);
    free_RIFF(riffS);

    riffM = alloc_RIFF();
    wavread_RIFF(riffM, Mono_filename);
    wavwrite_RIFF(riffM, Mono_filenameRIFF);
    free_RIFF(riffM);

    return 0;
}