SOURCE = main.c app.c init_sdl.c canvas.c

all:
	gcc -I src/include -L src/lib -o main $(SOURCE) -lSDL3 -lSDL3_ttf