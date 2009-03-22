CC = g++
CFLAGS = -g -Wall -Wextra -ansi -fPIC -pedantic
LDOPTS = -lGL -lX11 -lglut -lGLU
LDFLAGS = -I/usr/X11R6/include -I/opt/local/include -I~/src/computer-graphics/test -L/opt/local/lib  -L/usr/X11R6/lib  $(LDOPTS)
SOURCE = *.c
OUT = out 


default: fill

fill: SkPolygonFill.C
	$(CC) support.c SkPolygonFill.C testfill1.c -o testfill1 $(CFLAGS) $(LDFLAGS)
	$(CC) support.c SkPolygonFill.C testfill2.c -o testfill2 $(CFLAGS) $(LDFLAGS)
	$(CC) support.c SkPolygonFill.C truthfill2.c -o truthfill2 $(CFLAGS) $(LDFLAGS)



run: default
	./$(OUT)

clean:
	rm -rf testfill1
	rm -rf testfill2
    
