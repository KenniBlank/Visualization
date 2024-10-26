CFLAGS = -Wall -g -std=c99
LIBS   = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

ifeq ($(OS),Windows_NT)
	GAME = "game.exe"
	CFLAGS += -L ./
else
	GAME = "game"
endif

all:
ifndef SOURCE
	$(error SOURCE is not defined. Run 'make SOURCE=<file.c>')
endif
	gcc $(SOURCE) -o $(GAME) $(CFLAGS) $(LIBS)
	./$(GAME)
	rm ./$(GAME)
