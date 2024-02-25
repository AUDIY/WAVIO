# WAVIO
WAV File (*.wav) reader/writer library written in C.

## Note
[WAVIO](https://github.com/AUDIY/WAVIO) is no longer maintained and will be archived soon.  
This library is developped to make the author understood about WAV file structure.  
If you want to read & write audio files including WAV file, It is recommended to use [libsndfile](https://libsndfile.github.io/libsndfile/).  

## Example of making static library (on GCC)
execute [mklib.sh](https://github.com/AUDIY/WAVIO/blob/main/mklib.sh)
```
source ./mklib.sh
```

## Example Code
[Test.c](https://github.com/AUDIY/WAVIO/blob/main/Test.c) is an example to read audio aata into structs & copy to new audio files.
