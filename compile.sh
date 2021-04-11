/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o diver.o diver.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o metasprite.o metasprite.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o ink.o ink.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o collision_detector.o collision_detector.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -o main.gb main.o diver.o metasprite.o ink.o collision_detector.o