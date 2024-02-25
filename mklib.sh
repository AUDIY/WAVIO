gcc -c -o ./alloc_Mono.o ./alloc_Mono.c
gcc -c -o ./alloc_Mono_Native.o ./alloc_Mono_Native.c
gcc -c -o ./alloc_RIFF.o ./alloc_RIFF.c
gcc -c -o ./alloc_Stereo.o ./alloc_Stereo.c
gcc -c -o ./alloc_Stereo_Native.o ./alloc_Stereo_Native.c
gcc -c -o ./free_Mono.o ./free_Mono.c
gcc -c -o ./free_Mono_Native.o ./free_Mono_Native.c
gcc -c -o ./free_RIFF.o ./free_RIFF.c
gcc -c -o ./free_Stereo.o ./free_Stereo.c
gcc -c -o ./free_Stereo_Native.o ./free_Stereo_Native.c
gcc -c -o ./getPCMINFO.o ./getPCMINFO.c
gcc -c -o ./wavread_Mono.o ./wavread_Mono.c
gcc -c -o ./wavread_Mono_Native.o ./wavread_Mono_Native.c
gcc -c -o ./wavread_RIFF.o ./wavread_RIFF.c
gcc -c -o ./wavread_Stereo.o ./wavread_Stereo.c
gcc -c -o ./wavread_Stereo_Native.o ./wavread_Stereo_Native.c
gcc -c -o ./wavwrite_Mono.o ./wavwrite_Mono.c
gcc -c -o ./wavwrite_Mono_Native.o ./wavwrite_Mono_Native.c
gcc -c -o ./wavwrite_RIFF.o ./wavwrite_RIFF.c
gcc -c -o ./wavwrite_Stereo.o ./wavwrite_Stereo.c
gcc -c -o ./wavwrite_Stereo_Native.o ./wavwrite_Stereo_Native.c

ar rusv libWAVIO.a *.o