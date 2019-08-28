CC = gcc
CFLAGS = -Wall 
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_gfx
SOURCE = $(wildcard *.c)
OBJ = $(SOURCE: %.c=%.o)
EX = p
LIB =  */*/*.a */*.a 

all : 
		make -C views
		make -C commandes
		make $(EX) 


 
$(EX) : $(OBJ) $(LIB) options.h
	$(CC) -o $@ $^  $(LDLIBS)
	
 
clean:
		make -C views clean
		make -C commandes clean 
		rm -f *.o $(EX)
