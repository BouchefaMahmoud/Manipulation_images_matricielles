CC = gcc
CFLAGS = -Wall -g
LIBS = -lcheck_pic -pthread -lrt -lm -lsubunit -lSDL2 -lSDL2_image -lSDL2_gfx
SOURCE = $(wildcard *.c)
OBJ = $(SOURCE: %.c=%.o)
EX = out
LIB =  ../src/*/*.a  ../src/*/*/*.a

all :
	
		make -C ../src/views
		make -C ../src/commandes
		make $(EX) 


 
$(EX) : $(OBJ) $(LIB) ../src/options.h
	$(CC) -o $@ $^ $(LIBS) 
	
 
clean:
		make -C ../src/commandes clean 
		make -C ../src/views clean
		rm -f *.o $(EX)
