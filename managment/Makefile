CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS = -lcheck_pic -pthread -lrt -lm -lsubunit -lSDL2  -lSDL2_image
SRC =  views/main.c views/screen.c views/pixels.c commandes/parser.c  
OBJ = views/main.o views/screen.o views/pixels.o commandes/parser.o
EX=p 


all : $(EX)

#p: bin/test.o bin/truc.o
#	$(CC) $(CFLAGS) -o p bin/*.o $(LDLIBS) 
#bin/truc.o : src/truc.c
#	$(CC) $(CFLAGS) -o bin/truc.o -c src/truc.c $(LDLIBS)	 
#bin/test.o : tests/test.c
#	$(CC) $(CFLAGS) -o bin/test.o -c tests/test.c $(LDLIBS)

$(EX) : $(OBJ)
	$(CC) $(CFLAGS) -o $(EX) $^ $(LDLIBS)
	
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c  $< $(LDLIBS)
	 	
clean:
	rm -rf $(EX) views/*.o commandes/*.o


#$@ : nom de la cible 
#$< : nom de la première dépendance 
#$^  : la liste des dépendances 
#$?  : liste dépendances plus récentes que la cible
#$*  : nom fichier, sans son extension
