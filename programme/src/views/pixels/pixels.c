#include "pixels.h"

//Retrieves the rgba from a pixel at x and y
void infoPixel(int x, int y)
{
    screen *s = get_screen(_get_screens());
    if (x > s->size.WIDTH || y > s->size.HEIGTH)
    {
        puts("Error : Can not retrieve a pixel that is outside the window");
        return;
    }
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 pixel;
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint8 r, g, b, a;
        pixel = pixels[y * surface->w + x];

        SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
        printf("Red : %d\nGreen : %d\nBlue : %d\nAlpha : %d\n", r, g, b, a);
    }
    return;
}

//Function that allows to contrast a pixel
Uint8 contrastePixel(Uint8 color, double n)
{
    if (color <= 255 / 2)
        return (Uint8)((255 / 2) * SDL_pow((double)2 * color / 255, n));
    else
        return 255 - contrastePixel(255 - color, n);
}

//Function that allows to contrast an image
void contraste(unsigned int pourcentage)
{
    screen *s = get_screen(_get_screens());

    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint8 r, g, b, a;
        Uint32 pixel;
        Uint32 *pixels = (Uint32 *)surface->pixels;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;
        for (y = s->rect_select->y; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels[y * surface->w + x];

                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
                r = contrastePixel(r, (double)pourcentage);
                g = contrastePixel(g, (double)pourcentage);
                b = contrastePixel(b, (double)pourcentage);
                pixel = SDL_MapRGBA(surface->format, r, g, b, 255);
                pixels[y * surface->w + x] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
     
    }
}

//Function that allows you to change the brightness of a pixel
Uint8 ajout_pourcentage(Uint8 color, unsigned int pourcentage)
{
    if (color + pourcentage > 255)
        return 255;
    else if (color + pourcentage < 0)
        return 0;
    else
        return color + pourcentage;
}

//Function that allows you to change the brightness of an image
void luminosite(unsigned int pourcentage)
{
    screen *s = get_screen(_get_screens());

    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint8 r, g, b, a;
        Uint32 pixel;
        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels[y * surface->w + x];
                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

                r = ajout_pourcentage(r, pourcentage);
                g = ajout_pourcentage(g, pourcentage);
                b = ajout_pourcentage(b, pourcentage);

                pixel = SDL_MapRGBA(surface->format, r, g, b, a);
                pixels[y * surface->w + x] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
       
    }
}

//Function that allows to fill an image with a color
void remplissage(SDL_Color color)
{
    screen *s = get_screen(_get_screens());

    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint8 r, g, b, a;
        Uint32 pixel;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels[y * surface->w + x];
                pixel = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
                pixels[y * surface->w + x] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
     
    }
}

//Function that can put a black and white image
void noir_blanc(unsigned int pourcentage)
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint8 r, g, b, a, m;
        Uint32 pixel;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels[y * surface->w + x];

                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
                m = (r + g + b) / 3;                //Determine la couleur noir et blanc
                m = m * ((float)pourcentage / 100); //Nuance de gris
                pixel = SDL_MapRGBA(surface->format, m, m, m, a);
                pixels[y * surface->w + x] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
       
    }
}

//Function that allows to put the image in negative
void negatif()
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint8 r, g, b, a;
        Uint32 pixel;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels[y * surface->w + x];
                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
                r = 255 - r;
                g = 255 - g;
                b = 255 - b;
                pixel = SDL_MapRGBA(surface->format, r, g, b, a);
                pixels[y * surface->w + x] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
       
    }
}

void sym_v()
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint32 *pixels2 = (Uint32 *)surface->pixels;
        Uint32 pixel, p2;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y + 1; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x ; x < s->rect_select->w; x++)
            {
                pixel = pixels2[y * s->rect_select->w + x];
                pixels[y * s->rect_select->w - x ] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
        int res = SDL_BlitSurface(surface, NULL, s->surface_modif, NULL);
        if (res < 0)
        {
            SDL_Log("Erreur : %s > %s \n", "sdl_blit a echoue", SDL_GetError());
        }
    }
}


//Function that allows horizontal symmetry
void sym_h()
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint32 *pixels2 = (Uint32 *)surface->pixels;
        Uint32 pixel, p2;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y; y < s->rect_select->h / 2; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels2[y * s->rect_select->w + x];
                p2 = pixels[(s->rect_select->h - y - 1) * s->rect_select->w + x];
                pixels[(s->rect_select->h- y - 1) * s->rect_select->w + x] = pixel;
                pixels2[y * s->rect_select->w  + x] = p2;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
       
    }
}

//Function that allows to replace a color with another color with or without margin of tolerance
void remplace_couleur(SDL_Color old, SDL_Color new, unsigned int marge)
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint8 r, g, b, a;
        Uint32 pixel;

        if (SDL_MUSTLOCK(surface))
            SDL_LockSurface(surface);

        int x = 0, y = 0;

        for (y = s->rect_select->y; y < s->rect_select->h; y++)
        {
            for (x = s->rect_select->x; x < s->rect_select->w; x++)
            {
                pixel = pixels[y * surface->w + x];
                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
                if ((r >= (old.r - marge) && r <= (old.r + marge)) && (g >= (old.g - marge) && g <= (old.g + marge)) && (b >= (old.b - marge) && b <= (old.b + marge)))
                {
                    pixel = SDL_MapRGBA(surface->format, new.r, new.g, new.b, a);
                }
                pixels[y * surface->w + x] = pixel;
            }
        }
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(s->window);
       
    }
}

//Function that allows to zoom
void zoom(unsigned int pourcentage)
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        SDL_Surface *new_surface = rotozoomSurface(surface, 0, (float)pourcentage / 100, 1);

        SDL_Color color;
        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 255;
        remplissage(color);
        SDL_BlitSurface(new_surface, NULL, SDL_GetWindowSurface(s->window), NULL);

      
        SDL_UpdateWindowSurface(s->window);
    }
    return;
}

//Function that allows to rotate
void rotate(unsigned int degre)
{
    screen *s = get_screen(_get_screens());
    if (s != NULL)
    {
        SDL_Surface *surface = SDL_GetWindowSurface(s->window);
        SDL_Surface *new_surface = rotozoomSurface(surface, degre, 1, 1);

        SDL_BlitSurface(new_surface, NULL, SDL_GetWindowSurface(s->window), NULL);
        SDL_UpdateWindowSurface(s->window);
       
    }
    return;
}
