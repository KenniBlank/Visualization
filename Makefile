CFLAGS = -Wall -g -std=c99 -DSOURCE=\"$(SOURCE)\"
LIBS   = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

ifeq ($(OS),Windows_NT)
	GAME = "Executable.exe"
	CFLAGS += -L ./
else
	GAME = "Executable"
endif

all:
ifndef SOURCE
	$(error SOURCE is not defined. Run 'make SOURCE=<file.c>')
endif
ifeq ($(SOURCE), cli.c)
	gcc $(SOURCE) -o $(GAME) $(CFLAGS)
else
	gcc $(SOURCE) -o $(GAME) $(CFLAGS) $(LIBS)
endif
	./$(GAME)
	rm ./$(GAME)
	clear
