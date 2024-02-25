gcc -c -o ./WAVIO/alloc_Mono.o ./alloc_Mono.c
gcc -c -o ./WAVIO/alloc_Mono_Native.o ./alloc_Mono_Native.c
gcc -c -o ./WAVIO/alloc_RIFF.o ./alloc_RIFF.c
gcc -c -o ./WAVIO/alloc_Stereo.o ./alloc_Stereo.c
gcc -c -o ./WAVIO/alloc_Stereo_Native.o ./alloc_Stereo_Native.c
gcc -c -o ./WAVIO/free_Mono.o ./free_Mono.c
gcc -c -o ./WAVIO/free_Mono_Native.o ./free_Mono_Native.c
gcc -c -o ./WAVIO/free_RIFF.o ./free_RIFF.c
gcc -c -o ./WAVIO/free_Stereo.o ./free_Stereo.c
gcc -c -o ./WAVIO/free_Stereo_Native.o ./free_Stereo_Native.c
gcc -c -o ./WAVIO/getPCMINFO.o ./getPCMINFO.c
gcc -c -o ./WAVIO/wavread_Mono.o ./wavread_Mono.c
gcc -c -o ./WAVIO/wavread_Mono_Native.o ./wavread_Mono_Native.c
gcc -c -o ./WAVIO/wavread_RIFF.o ./wavread_RIFF.c
gcc -c -o ./WAVIO/wavread_Stereo.o ./wavread_Stereo.c
gcc -c -o ./WAVIO/wavread_Stereo_Native.o ./wavread_Stereo_Native.c
gcc -c -o ./WAVIO/wavwrite_Mono.o ./wavwrite_Mono.c
gcc -c -o ./WAVIO/wavwrite_Mono_Native.o ./wavwrite_Mono_Native.c
gcc -c -o ./WAVIO/wavwrite_RIFF.o ./wavwrite_RIFF.c
gcc -c -o ./WAVIO/wavwrite_Stereo.o ./wavwrite_Stereo.c
gcc -c -o ./WAVIO/wavwrite_Stereo_Native.o ./wavwrite_Stereo_Native.c

ar rusv libWAVIO.a *.o
