CC=gcc

# Change this to y to compile with audio support
COMPILE_AUDIO=y

CFLAGS=-std=gnu99 $(shell sdl2-config --cflags) -Wall -Wextra -Isrc/include/ -g
LDFLAGS= $(shell sdl2-config --cflags --libs) -lm

ifeq ($(COMPILE_AUDIO), y)
	CFLAGS := $(CFLAGS) -DDO_AUDIO
	LDFLAGS := $(LDFLAGS) -lSDL2_mixer
endif

EXE=Asteroids
EXET=asteroids_test
LD=gcc

all: main.o pixels.o ship.o bullet.o text.o asteroid.o saucers.o audio.o collisions.o
	cd build && \
	$(LD) -o ../$(EXE) $(LDFLAGS) $^

#tests: asteroid_test.o
	#cd build && \
	#$(LD) $(LDFLAGS) -o ../$(EXET) $<

clean:
	rm -rf build
	rm -f $(EXE)
	rm -f $(EXET)

#%_test.o: tests/%_test.c
	#mkdir -p build
	#$(CC) -c $(CFLAGS) -o build/$@ $< tests/unity_src/unity.c

%.o: src/%.c
	mkdir -p build
	$(CC) -c $(CFLAGS) -o build/$@ $<

mem_check:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes -v ./$(EXE)
