
#include "views/screen/screen.h"
#include "views/pixels/pixels.h"

//List all the commands that were implemented
void help()
{
    puts("{ ");
    puts("Ligne de commande :");

    puts("screen : permet de lancer une autre fenetre");
    puts("image [path] : Permet de charger une image");
    puts("set-image : Permet d'afficher l'image en memoire");
    puts("negatif : Permet de rendre l'image negatif");
    puts("black-white [pourcentage] : Permet de mettre l'image en noir et blanc, et nuancer le noir et blanc par un pourcentage");
    puts("horizontal : Permet de tourner une image horizontalement");
    puts("vertical : Permet de tourner une image verticalement");
    puts("cancel : Permet de remettre l'image à sa derniere position");
    puts("fermer : Permet de fermer une fenetre");
    puts("brightness [pourcentage] : Permet de manipuler la luminosite d'une image");
    puts("replaceColor [OldR OldG OldB NewR NewG NewB marge] : Permet de remplacer une couleur par une autre couleur (avec ou sans(= 0) marge de tolerance)");
    puts("contrast [pourcentage] : Permet de constraster une image en fonction d'un pourcentage;");
    puts("select [x] [y] [w] [h] : Permet de selectionner une zone avec les coordonnes");
    puts("deselect : Permet de deselectionner la region en question");
    puts("removeZone : Efface la zone");
    puts("quite : Sortir du programme");
    puts("save : sauvegarder l'image");
    puts("paste [x] [y]: coller la region sur l'image en cours");
    puts("selectMouse : selectionne la souris (reprise de la main par la souris)");
    puts("mouse  : prend la souris");
    puts("fillColor [R] [G] [B] : remplie par la couleur donnée");
    puts("zoom [x] : zoom x-fois sur l'image");
    puts("changeExtensio [path & extension] : change l'extension d'une image par la nouvelle donnée en argument");
    puts("rotate [degree] : effectue une rotation de i-fois sur l'image");
    puts("reframe : recadre l'image en cours de traitement");
    puts("info [x] [y] : donne les informations RGB du pixel en x et/ou du pixel en y");
    puts("export : exporte l'image");
    puts("help : Donne les informations sur toutes les commandes implementees");

    puts("} ");

    puts("Ouvrez une fenetre pour commencer ...");
}

int getFormatImage(const char *path)
{
    if (strstr(path, ".jpg"))
    {
        return IMG_INIT_JPG;
    }
    else if (strstr(path, ".png"))
    {
        return IMG_INIT_PNG;
    }
    else if (strstr(path, ".tif"))
    {
        return IMG_INIT_TIF;
    }
    else if (strstr(path, ".webp"))
    {
        return IMG_INIT_WEBP;
    }
    else if (strstr(path, "bmp"))
    {
        return BMP;
    }
    else
    {
        return -1;
    }
}

/************************************/
/* Lancement du programme           */
/* Boucle principale                */
/************************************/
start()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Erreur d'initialisation de la SDL");
    }

    char commande[MAX];
    options op;
    op.flag = -1;
    int play = SDL_TRUE;

    SDL_Surface *image = NULL;
    SDL_Rect rect_image;

    SDL_Window *targetWindow;
    screen *s = NULL;
    SDL_Event e;
    struct timeval tv;
    int ret;
    int fd = 0;
    int rc = fcntl(fd, F_GETFL);
    if (rc < 0)
    {
        perror("");
    }
    rc = fcntl(fd, F_SETFL, rc | O_NONBLOCK);
    if (rc < 0)
    {
    }
    fd_set rdfs;
    // tos: time out s , toms : time out mili s
    int tos = 1;
    int toms = 0;
    int ext;
    SDL_Rect rect = {0, 0, 0, 0};
    /***********************************/
    SDL_Rect conteneur;
    //SDL_Rect rect;
    /*************************************/
    while (play)
    {
        tv.tv_sec = tos;
        tv.tv_usec = toms;
        FD_ZERO(&rdfs);
        FD_SET(fd, &rdfs);
        ret = select(8, &rdfs, NULL, NULL, &tv);

        if (ret > 0)
        {
            rc = read(fd, commande, MAX);
            if (rc > 0)
            {
                commande[rc - 1] = '\0';
                parser(&op, commande);
            }
        }

        rect.h = 0;
        rect.w = 0;

        switch (op.flag)
        {
        case FENETRE:
            init_screen(op.taille_fenetre, "Fenetre");

            break;
        case EXIT:
            puts("exit");
            s = _get_screens();
            while (s != NULL)
            {
                if (s->surface_principale == s->surface_modif)
                    SDL_FreeSurface(s->surface_principale);
                else
                {
                    SDL_FreeSurface(s->surface_principale);
                    SDL_FreeSurface(s->surface_modif);
                }
                if (s->selected == SDL_TRUE)
                    SDL_FreeSurface(s->surface_select);

                s = s->next;
            }
            if (image != NULL)
            {
                SDL_FreeSurface(image);
            }

            while (_screens != NULL)
            {
                screen *p = _screens;
                _screens = _screens->next;
                free(p);
            }
            SDL_Quit();
            exit(0);
            break;
        case CLOSE_WIN:
            fermer_fenetre();

            break;
        case CHARGER_IMAGE_MEMOIRE:
            ext = getFormatImage(op.path);
            image = NULL;

            if (ext == BMP)
            {
                image = SDL_LoadBMP(op.path);
            }
            else
            {
                IMG_Init(ext);
                image = IMG_Load(op.path);
            }
            if (image == NULL)
            {
                perror("Enable to load image");
            }
            break;
        case CHARGER_IMAGE_FENETRE:
            set_surface_screen(image);
            display_window_surface();

            break;
        case NEGATIF:
            negatif();
            break;
        case NOIR_BLANC:
            noir_blanc(op.valeur);

            break;
        case HORIZONTALE:
            sym_h();

            break;
        case VERTICALE:
            sym_v();

            break;
        case SAUVEGARDER:
            save();

            break;
        case ANNULER_MODIF:
            ctrl_z();

            break;
        case SELECT_SOURIS:
            // s = get_screen(_get_screens());
            // fenetre(s->surface_modif);

            break;
        case SELECT_CLAVIER:
            select_zone(op.select);

            break;
        case COLLER:
            past(op.x, op.y);

        case ZOOM:
            zoom(op.valeur);

            break;
        case LUMINOSITE:
            luminosite(op.valeur);

            break;
        case REMPLACER_COULEUR:
            remplace_couleur(op.couleur, op.couleur2, op.valeur);

            break;
        case REMPLIR_COULEUR:
            remplissage(op.couleur);

            break;
        case CONTRASTE:
            rect.x = 0;
            rect.y = 0;
            contraste(op.valeur);

            break;
        case INFOPIXEL: //Gerer le cas ou x est superieur à la width de la fenetre et de meme pour height
            infoPixel(op.x, op.y);

            break;
        case PIVOTER_IMAGE:
            rotate(op.valeur);

            break;
        case EXPORT:
            //Fonction d'export
            s = get_screen(_get_screens());
            if (strstr(op.path, ".png"))
            {
                IMG_SavePNG(s->surface_principale, op.path);
            }
            else if (strstr(op.path, ".bmp"))
            {
                SDL_SaveBMP(s->surface_principale, op.path);
            }
            else if (strstr(op.path, ".jpg"))
            {
                //TODO:
            }
            else
            {
                puts("Impossible d'exporter l'image, extension nom prise en compte");
            }

            break;

        case DESELECTIONNER:
            deslectionner();
        case RECADRER:
            recadrer();
            break;
        case HELP:
            help();
            break;
        default:
            break;
        }
        op.flag = -1;

        SDL_Delay(50);

        while (play && SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_WINDOWEVENT:

                targetWindow = SDL_GetWindowFromID(e.window.windowID);

                switch (e.window.event)
                {
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    // tell which window gained focus
                    _set_id(SDL_GetWindowID(targetWindow));
                    break;
                }
                break;
            }
        }
    }

    SDL_Quit();
}

int main()
{
    start();

    SDL_Quit();
    return 0;
}
