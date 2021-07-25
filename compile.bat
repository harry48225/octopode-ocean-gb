@echo off
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -c -o diver.o diver.c
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -c -o metasprite.o metasprite.c
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -c -o ink.o ink.c
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -c -o collision_detector.o collision_detector.c
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -c -o constants.o constants.c
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
C:\\gbdk\\bin\\lcc -Wa-l -Wl-m -Wl-j -o main.gb main.o diver.o metasprite.o ink.o collision_detector.o constants.o