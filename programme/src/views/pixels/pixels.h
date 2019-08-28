/*
ce module va contenir les fonctions de manipulations  sur les pixels 
*/

#ifndef __PIXEL__
#define __PIXEL__

#include "../../options.h"
#include "../screen/screen.h"

#define LIMIT_LUM 25

void infoPixel(int x, int y);        
Uint8 contrastePixel(Uint8, double); 
void contraste(unsigned int);        
void luminosite(unsigned int);
void remplissage(SDL_Color);                               
void noir_blanc(unsigned int);                             
void negatif();                                            
void sym_h();                                              
void sym_v();                                              
void remplace_couleur(SDL_Color, SDL_Color, unsigned int); 
void zoom(unsigned int);                                   
void rotate(unsigned int);                                 

#endif