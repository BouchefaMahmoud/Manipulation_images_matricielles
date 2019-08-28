#ifndef __OPTION__

#define __OPTION__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_rotozoom.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <SDL2/SDL_image.h>

#define MAX 100
#define TIMEOUT 1
#define FPS_LIMIT 16
#define BMP 43

typedef struct options options;

typedef enum FLAG FLAG;
enum FLAG
{
  FENETRE,
  CHARGER_IMAGE_MEMOIRE,
  CHARGER_IMAGE_FENETRE,
  PIVOTER_IMAGE,
  CHANGER_EXTENSION,
  SYMETRIE_IMAGE,
  ZOOM,
  REMPLIR_COULEUR,
  CONTRASTE,
  NOIR_BLANC,
  NEGATIF,
  LUMINOSITE,
  REMPLACER_COULEUR,
  SOURIS,
  SELECT_CLAVIER,
  SELECT_SOURIS,
  DESELECTIONNER,
  COPIER,
  COLLER,
  SAUVEGARDER,
  ANNULER_MODIF,
  SUPPRIMER_ZONE,
  EXIT,
  CLOSE_WIN,
  RECADRER,
  VERTICALE,
  HORIZONTALE,
  INFOPIXEL,
  EXPORT,
  HELP
};

typedef struct taille
{
  int WIDTH;
  int HEIGTH;
} taille;

struct options
{
  FLAG flag;
  int x;
  int y;

  char *path;
  taille *taille_fenetre;
  char *extension;

  SDL_Color couleur;
  SDL_Color couleur2;
  unsigned int valeur;
  SDL_Rect select;
};

#endif
