CC = gcc
CFLAGS = -Wall -std=c99
SRC = main.c
OUT = game

LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)
