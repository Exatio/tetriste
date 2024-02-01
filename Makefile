export LD_LIBRARY_PATH=./raylib/lib:$LD_LIBRARY_PATH  # utile ??

CFLAGS=-Wall -I./raylib/include/
LDFLAGS=-L./raylib/lib/ -lraylib -lm -lpthread -ldl -lrt -lX11

all: tetriste

tetriste: src/tetriste.o src/cli/tetriste_cli.o src/gui/tetriste_gui.o src/gui/audio/audio.o src/gui/screens/screen_gameplay.o src/gui/screens/screen_title.o main.o raylib/lib/libraylib.a Makefile
	gcc -o tetriste src/tetriste.o src/cli/tetriste_cli.o src/gui/tetriste_gui.o src/gui/audio/audio.o src/gui/screens/screen_gameplay.o src/gui/screens/screen_title.o main.o raylib/lib/libraylib.a $(LDFLAGS)

src/tetriste.o: src/tetriste.c src/tetriste.h
	gcc -o src/tetriste.o -c src/tetriste.c $(CFLAGS)

src/cli/tetriste_cli.o: src/cli/tetriste_cli.c src/cli/tetriste_cli.h
	gcc -o src/cli/tetriste_cli.o -c src/cli/tetriste_cli.c $(CFLAGS)

src/gui/tetriste_gui.o: src/gui/tetriste_gui.c src/gui/tetriste_gui.h
	gcc -o src/gui/tetriste_gui.o -c src/gui/tetriste_gui.c $(CFLAGS)

src/gui/audio/audio.o: src/gui/audio/audio.c src/gui/audio/audio.h
	gcc -o src/gui/audio/audio.o -c src/gui/audio/audio.c $(CFLAGS)

src/gui/screens/screen_gameplay.o: src/gui/screens/screen_gameplay.c src/gui/screens/screens.h
	gcc -o src/gui/screens/screen_gameplay.o -c src/gui/screens/screen_gameplay.c $(CFLAGS)

src/gui/screens/screen_title.o: src/gui/screens/screen_title.c src/gui/screens/screens.h
	gcc -o src/gui/screens/screen_title.o -c src/gui/screens/screen_title.c $(CFLAGS)

main.o: main.c
	gcc -o main.o -c main.c $(CFLAGS)

clean:
	rm ./*.o src/*.o src/cli/*.o src/gui/*.o src/gui/audio/*.o src/gui/screens/*.o tetriste
