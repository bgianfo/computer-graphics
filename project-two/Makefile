CC = gcc
CFLAGS = -g -Wall -std=c99 -pedantic
LDOPTS = -lGL -lX11 -lglut -lGLU
LDFLAGS = -I/usr/X11R6/include -I/opt/local/include -I./headers -L/opt/local/lib  -L/usr/X11R6/lib  $(LDOPTS)
SOURCE = *.c
OUT = out 


default: fill

clip: clipPolygon.c
	$(CC) support.c testclip1.c clipPolygon.c -o testclip1 $(CFLAGS) $(LDFLAGS)

fill: drawFilledPolygon.c
	$(CC) support.c drawFilledPolygon.c testfill1.c -o testfill1 $(CFLAGS) $(LDFLAGS)
	$(CC) support.c drawFilledPolygon.c testfill2.c -o testfill2 $(CFLAGS) $(LDFLAGS)
line: drawLine.c
	$(CC) support.c testclip1.c clipPolygon.c -o testclip1 $(CFLAGS) $(LDFLAGS)


run: default
	./$(OUT)
clean:
	rm -f $(OUT)
    
