/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o diver.o diver.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o metasprite.o metasprite.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -o main.gb main.o diver.o metasprite.o