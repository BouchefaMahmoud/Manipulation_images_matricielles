#include "screen.h"
#include "../pixels/pixels.h"

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur : %s > %s \n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

unsigned int _get_id()
{
    return _id;
}
void _set_id(unsigned int id)
{
    if (id > 0)
    {
        _id = id;
    }
}

screen *_get_screens()
{
    /*    screen *s = malloc(sizeof(s));
    s = _screens;*/
    return _screens;
}

void init_screen(taille *size, const char *title)
{
    IMG_Init(IMG_INIT_JPG);
    SDL_Surface *surface = IMG_Load("start_image.jpg");
    if (!surface)
    {
        SDL_ExitWithError("Initialisation de la fenetre");
    }

    screen *s = malloc(sizeof(screen));

    if (s == NULL)
    {
        perror("Allocation de mémoire pour un screen");
        return NULL;
    }
    s->title = malloc(strlen(title));
    memcpy(s->title, title, strlen(title));
    s->surface_principale = surface;
    s->surface_modif = surface;
    s->surface_select = NULL;
    s->rect_select = malloc(sizeof(SDL_Rect));

    s->selected = SDL_FALSE;
    s->next = NULL;
    s->window = SDL_CreateWindow(s->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size->WIDTH, size->HEIGTH, 0);
    if (s->window == NULL)
    {
        SDL_ExitWithError("Initialisation de la fenetre");
    }

    SDL_Surface *image2 = zoomSurface(surface, (float)size->WIDTH / surface->w, (float)size->HEIGTH / surface->h, 1);
    if (image2 == NULL)
    {
        SDL_DestroyWindow(s->window);
        SDL_ExitWithError("Erreur : création de la texture");
    }

    s->id = SDL_GetWindowID(s->window);
    _set_id(s->id);
    add_screen(&_screens, s);

    int res = SDL_BlitSurface(image2, NULL, s->surface_modif, NULL);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue", SDL_GetError());
    }

    res = SDL_BlitSurface(image2, NULL, s->surface_principale, NULL);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue", SDL_GetError());
    }
    init_select_rect(s);
    display_window_surface();

    if (_screens == NULL)
        perror("Ajout de fenetree");
    SDL_FreeSurface(surface);
}

void add_screen(screen **s, screen *window)
{
    if (*s == NULL)
    {
        *s = window;
    }
    else
    {
        window->next = *s;
        *s = window;
    }
}

void delete_screen(screen **s)
{
    screen *p = NULL;
    if (*s != NULL)
    {

        if ((*s)->id == _get_id())
        {
            p = *s;
            (*s) = (*s)->next;
            free(p);
            return;
        }

        screen *l = *s;
        p = l->next;
        while (p != NULL)
        {

            if ((*s)->id == _get_id())
            {
                l->next = p->next;
                free(p);
                return;
            }
            l = l->next;
            p = p->next;
        }
    }
}

screen *get_screen(screen *s)
{
    if (s == NULL)
    {
        return NULL;
    }

    while (s != NULL)
    {

        if (s->id == _get_id())
            return s;
        s = s->next;
    }
    return NULL;
}

void update_screen()
{
    screen *s = get_screen(_get_screens());

    //TODO: vérifier is on doit d'abord free l'ancienne surface

    //TODO: we may use blitSurface

    int res = SDL_BlitSurface(s->surface_modif, NULL, SDL_GetWindowSurface(s->window), NULL);
    if (res < 0)
    {
        printf("sdl_blit a echoue\n");
    }

    // s->surface_select = surface_select;
}


void fermer_fenetre()
{

    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        //TODO: gestion de libération de mémoire
        if (s->surface_principale == s->surface_modif)
            SDL_FreeSurface(s->surface_principale);
        else
        {
            SDL_FreeSurface(s->surface_principale);
            SDL_FreeSurface(s->surface_modif);
        }
        if (s->selected == SDL_TRUE)
            SDL_FreeSurface(s->surface_select);

        SDL_DestroyWindow(s->window);
        delete_screen(&_screens);
    }
    else
    {
        puts("IL n'y a pas de fenetre ouverte !");
    }
}

void set_surface_screen(SDL_Surface *surface)
{

    screen *s = get_screen(_get_screens());
    int *hauteur = malloc(sizeof(int)), *largeur = malloc(sizeof(int));
    SDL_Surface *image2 = NULL;

    if (surface == NULL)
    {
        puts("Image null");
        return;
    }

    if (s != NULL)
    {

        SDL_GetWindowSize(s->window, largeur, hauteur);

        /*   if (s->surface_modif != NULL)
        {
            SDL_FreeSurface(s->surface_modif);
        }*/

        image2 = zoomSurface(surface, (float)(*largeur) / surface->w, (float)(*hauteur) / surface->h, 1);
        if (image2 == NULL)
        {
            SDL_DestroyWindow(s->window);
            SDL_ExitWithError("Erreur : création de la texture");
        }

        int res = SDL_BlitSurface(image2, NULL, s->surface_modif, NULL);
        if (res < 0)
        {
            SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue1", SDL_GetError());
        }
        /*res = SDL_BlitSurface(image2, NULL, s->surface_principale, NULL);
        if (res < 0)
        {
            SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue2", SDL_GetError());
        }*/

        /*res = SDL_BlitSurface(surface, NULL, s->surface_select, NULL);
        if (res < 0)
        {
            SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue3", SDL_GetError());
        }*/
    }
}

void display_window_surface()
{
    int res = 0;
    screen *s = get_screen(_get_screens());
    

    if (!SDL_MUSTLOCK(s->surface_modif))
    {
    }

    // SDL_UnlockSurface(SDL_GetWindowSurface(s->window));
    // SDL_UnlockSurface(s->surface_modif);

    res = SDL_BlitSurface(s->surface_modif, NULL, SDL_GetWindowSurface(s->window), NULL);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue", SDL_GetError());
    }
    SDL_UpdateWindowSurface(s->window);
}

void ctrl_z()
{

    screen *s = get_screen(_get_screens());
    if (s->surface_modif == NULL || s->surface_principale == NULL)
    {
        puts("nothing to cancel ");
        return;
    }
    else
    {
        // SDL_FreeSurface(s->surface_modif);
    }

    int res = SDL_BlitSurface(s->surface_modif, NULL, s->surface_principale, NULL);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue", SDL_GetError());
    }

    res = SDL_BlitSurface(s->surface_modif, NULL, SDL_GetWindowSurface(s->window), NULL);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue", SDL_GetError());
    }
    SDL_UpdateWindowSurface(s->window);
}

void select_zone(SDL_Rect rect)
{
    screen *p = _get_screens();
    while (p != NULL)
    {
        if (p->selected == SDL_TRUE)
        {
            p->selected = SDL_FALSE;
            ctrl_z();
        }
        p = p->next;
    }

    screen *s = get_screen(_get_screens());
    char path[20];
    sprintf(path,"exports/%d.png\n", s->id);
    IMG_SavePNG(SDL_GetWindowSurface(s->window), path);
    IMG_Init(IMG_INIT_PNG);
    s->surface_select = IMG_Load(path);

    int *h = malloc(sizeof(int)), *w = malloc(sizeof(int)), *x = malloc(sizeof(int)), *y = malloc(sizeof(int));
    *h = rect.h;
    *w = rect.w;
    *x = rect.x;
    *y = rect.y;
    s->surface_select->h = *h;
    s->surface_select->w = *w;

    s->rect_select->h = (*h) + (*x);
    s->rect_select->w = *w + *y;
    s->rect_select->x = *x;
    s->rect_select->y = *y;
    int res = SDL_BlitSurface(s->surface_select, &rect, s->surface_select, &rect);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue select", SDL_GetError());
    }

    s->selected = SDL_TRUE;

    luminosite(80);
}

void past(int x, int y)
{

    screen *p = _get_screens();
    screen *s = get_screen(_get_screens());
    int res;
    SDL_Rect rect;
    while (p != NULL)
    {
        if (p->selected == SDL_TRUE)
        {
            rect.x = x;
            rect.y = y;
            rect.w = p->surface_select->w;
            rect.h = p->surface_select->h;

            res = SDL_BlitSurface(p->surface_select, NULL, SDL_GetWindowSurface(s->window), &rect);
            if (res < 0)
            {
                SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue select", SDL_GetError());
            }
            init_select_rect(p);
        }
        p = p->next;
    }
    //display_window_surface();

    SDL_UpdateWindowSurface(s->window);
}

void init_select_rect(screen *p)
{
    int *h = malloc(sizeof(int)), *w = malloc(sizeof(int));
    SDL_GetWindowSize(p->window, w, h);
    p->rect_select->x = 0;
    p->rect_select->y = 0;
    p->rect_select->h = *h;
    p->rect_select->w = *w;
}

deslectionner()
{

    screen *p = _get_screens();

    while (p != NULL)
    {
        if (p->selected == SDL_TRUE)
        {
            p->selected = SDL_FALSE;
            init_select_rect(p);
        }
        p = p->next;
    }

    ctrl_z();
}

recadrer()
{

    screen *s = get_screen(_get_screens());
    if (!s->selected)
    {
        perror("please select Zone");
        return;
    }
    set_surface_screen(s->surface_select);
    init_select_rect(s);
    display_window_surface();
}

void save()
{
    screen *s = get_screen(_get_screens());
    int *w = malloc(sizeof(int)), *h =malloc(sizeof(int)) ; 
    SDL_GetWindowSize(s->window,w,h);
    s->surface_principale = zoomSurface(SDL_GetWindowSurface(s->window), (float) *w/ s->surface_principale->w, (float)*h/ s->surface_principale->h, 1);
    if (s->surface_principale == NULL)
    {
        SDL_DestroyWindow(s->window);
        SDL_ExitWithError("Erreur : création de la texture");
    }
    /*int res = SDL_BlitSurface(SDL_GetWindowSurface(s->window), NULL, s->surface_principale, NULL);
    if (res < 0)
    {
        SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue save", SDL_GetError());
    }*/
}

SDL_Surface* resize( SDL_Surface * surface, int h , int w){
    screen *s = get_screen(_get_screens());
      SDL_Surface *image2 = zoomSurface(SDL_GetWindowSurface(s->window), (float) w/ surface->w, (float)h/ surface->h, 1);
    if (image2 == NULL)
    {
        SDL_DestroyWindow(s->window);
        SDL_ExitWithError("Erreur : création de la texture");
    }
    SDL_FreeSurface(surface);
    return image2;
}