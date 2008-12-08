CC = gcc
CFLAGS = -Wall -std=c99
LDOPTS = -lGL -lX11 -lglut -lglu
LDFLAGS = -I/usr/X11R6/include -I/opt/local/include -L/opt/local/lib  -L/usr/X11R6/lib  $(LDOPTS)
SOURCE = project1.c
OUT = out 

default:
	$(CC) $(SOURCE) -o $(OUT) $(CFLAGS) $(LDFLAGS)
run: default
	./$(OUT)
clean:
	rm -f $(OUT)
    
