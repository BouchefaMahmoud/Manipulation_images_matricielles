/*
 Ce module va contenir la structure qui va définir
 les composants d'une fenetre	
*/

#ifndef __SCREEN__
#define __SCREEN__

#include "../../commandes/parser.h"

// #define WIDTH 800
// #define HEIGHT 800

typedef struct screen
{
    //TODO:à verifier
    unsigned int id;
    SDL_Surface *surface_principale;
    SDL_Surface *surface_modif;
    SDL_Surface *surface_select;
    SDL_Window *window;
    char *title;
    SDL_bool selected;
    SDL_Rect *rect_select;
    taille size;
    struct screen *next;
} screen;

static unsigned int _id = 0;

static screen *_screens = NULL;

unsigned int _get_id();
screen *_get_screens();

void _set_id(unsigned int);

void SDL_ExitWithError(const char *message);
// static screen *_ecrans;

void init_screen(taille *size, const char *title);
void add_screen(screen **, screen *);
void delete_screen(screen **);
void update_screen();
void ctrl_z();
void select_zone(SDL_Rect);
screen *get_screen(screen *);
void save();
deslectionner();
recadrer();
void set_surface_screen(SDL_Surface *);
void display_window_surface();
void fermer_fenetre();
SDL_Rect *getRect(screen *);
void past(int x, int y);

void init_select_rect(screen *);

#endif
