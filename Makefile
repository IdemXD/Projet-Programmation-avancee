CC = gcc
CFLAGS = -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs  -L./SDL2_image/.libs
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm
INCLUDES =  -I./SDL2_ttf  -I./SDL2_image
EXEC = main
SRC = main.c personnages.c salle.c actions.c fonctions_SDL.c plateau.c
OBJ = $(SRC:.c=.o)

SRCPL = testPlateau.c personnages.c salle.c actions.c fonctions_SDL.c plateau.c
TPL = $(SRCPL:.c=.o)

SRCA = testActions.c actions.c personnages.c salle.c fonctions_SDL.c plateau.c
OBJA = $(SRCA:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)

testPlateau: $(TPL)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)

testActions: $(OBJA)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
