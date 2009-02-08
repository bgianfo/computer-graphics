CC = gcc
CFLAGS = -g -Wall -std=c99 -pedantic
LDOPTS = -lGL -lX11 -lglut -lGLU
LDFLAGS = -I/usr/X11R6/include -I/opt/local/include -I./headers -L/opt/local/lib  -L/usr/X11R6/lib  $(LDOPTS)
SOURCE = *.c
OUT = project3


default: project3

project3: project3.c
	$(CC) tga.c project3.c -o $(OUT) $(CFLAGS) $(LDFLAGS)

run: default
	./$(OUT)
clean:
	rm -rf $(OUT)
    
