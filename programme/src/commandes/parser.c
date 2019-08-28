#include "parser.h"
#define NB_ARGUMENT 10
#define TAILLE_ARGUMENT 20

// Check if the character string entered is a number. Return 0 if is not a digitString else 1
int isdigitSTRING(char *ch)
{
    for (int i = 0; i < strlen(ch); i++)
    {
        if (isdigit(ch[i]) == 0)
            return false;
    }
    return true;
}

// Suppress white characters at the beginning and at the end
char *trim(char *s)
{
    if (s == NULL)
        return NULL;
    char *str_trim = malloc(strlen(s) + 1);
    strcpy(str_trim, s);

    int i = 0;
    // As long as there are spaces at the beginning
    while ((str_trim[i] != '\0') && (isspace(str_trim[i])))
    {
        if (isspace(str_trim[i]))
        {
            for (int j = 0; j < strlen(s); j++)
                str_trim[j] = str_trim[j + 1];
            i = 0;
            continue;
        }
        i++;
    }

    // As long as there are spaces at the end
    while (isspace(str_trim[strlen(str_trim) - 1]))
        str_trim[strlen(str_trim) - 1] = str_trim[strlen(str_trim)];
    return str_trim;
}

// Reduces two white characters to a white character
char *trimSpace(char *s)
{
    if (s == NULL)
        return NULL;
    char *trim_space = malloc(strlen(s) + 1);
    strcpy(trim_space, s);

    int i = 0;
    while (trim_space[i] != '\0')
    {
        if (isspace(trim_space[i]) && isspace(trim_space[i + 1]))
        {
            for (int j = i; j < strlen(s); j++)
                trim_space[j] = trim_space[j + 1];
            i = 0;
            continue;
        }
        i++;
    }
    return trim_space;
}

//Display the error
void printError(char *error)
{
    puts(error);
    puts("Please check all the command available and how to use them by using the command : help");
}

void parser(options *op, char *commande)
{
    commande = trim(commande);
    commande = trimSpace(commande);
    if (strlen(commande) == 0)
    {
        printError("You enter nothing.");
        return;
    }
    char cmd[NB_ARGUMENT][TAILLE_ARGUMENT];
    int i = 0, j = 0, taille_tableau = 0;
    for (i = 0; i <= (strlen(commande)); i++)
    {
        // if space or NULL found, assign NULL into cmd[taille_tableau]
        if (commande[i] == ' ' || commande[i] == '\0')
        {
            cmd[taille_tableau][j] = '\0';
            if (taille_tableau > NB_ARGUMENT)
            {
                puts("Error : You enter more than 9 arguments");
                return;
            }
            taille_tableau++; //for next word
            j = 0;            //for next word, init index to 0
        }
        else
        {
            if (j > TAILLE_ARGUMENT)
            {
                puts("Error : The size of one of your argument is taller than 15 characters");
                return;
            }
            cmd[taille_tableau][j] = commande[i];
            j++;
        }
    }

    int size = 0;
    int *h, *w;
    h = malloc(sizeof(int));
    w = malloc(sizeof(int));
    if (strcmp(cmd[0], "screen") == 0)
    {
        if (taille_tableau < 4)
        {
            op->taille_fenetre = malloc(sizeof(taille));
            if (taille_tableau == 1) //Si l'utilisateur entre seulement screen. On creer une fenetre de taille 700,700 (par defaut)
            {
                op->flag = FENETRE;
                op->taille_fenetre->HEIGTH = 700;
                op->taille_fenetre->WIDTH = 700;
            }
            else if (taille_tableau == 2 && isdigitSTRING(cmd[1])) //Si l'utilisateur entre screen x. On creer une fenetre de taille x, x
            {
                op->flag = FENETRE;
                *h = atoi(cmd[1]);

                op->taille_fenetre->WIDTH = *h;
                op->taille_fenetre->HEIGTH = *h;
            }
            else if (taille_tableau == 3 && isdigitSTRING(cmd[1]) && isdigitSTRING(cmd[2])) //Si l'utilisateur entre screen x y. On creer une fenetre de taille x, y
            {
                *h = atoi(cmd[1]);
                *w = atoi(cmd[2]);

                op->flag = FENETRE;
                op->taille_fenetre->WIDTH = *h;
                op->taille_fenetre->HEIGTH = *w;
            }
            else
            {
                printError("Error : The size of the window is not an number");
            }
        }
        else
        {
            printError("Error : You enter to many arguments");
        }
    }
    else if (strcmp(cmd[0], "image") == 0)
    {
        if (taille_tableau == 2)
        {
            op->flag = CHARGER_IMAGE_MEMOIRE;
            size = sizeof(cmd[1]);
            op->path = malloc(size);
            memcpy(op->path, cmd[1], size);
        }
        else
        {
            printError("Error : Your have to enter only one argument");
        }
    }
    else if (strcmp(cmd[0], "set-image") == 0)
    {
        if (taille_tableau != 1)
            puts("Warning: Any option is required for this command");
        op->flag = CHARGER_IMAGE_FENETRE;
    }
    else if (strcmp(cmd[0], "rotate") == 0)
    {
        if (taille_tableau == 2)
        {
            if (isdigitSTRING(cmd[1]))
            {
                if (atoi(cmd[1]) <= 360)
                {
                    op->flag = PIVOTER_IMAGE;
                    op->valeur = atoi(cmd[1]);
                }
                else
                {
                    printError("Error : Your argument have to be between 0 and 360 degre");
                }
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only one argument");
        }
    }
    else if (strcmp(cmd[0], "changeExtension") == 0)
    {
        if (taille_tableau == 2)
        {
            if (!isdigitSTRING(cmd[1]))
            {
                op->flag = CHANGER_EXTENSION;
                size = strlen(cmd[1]);
                op->extension = malloc(size);
                memcpy(op->extension, cmd[1], size);
            }
            else
            {
                printError("Error : Your argument don't have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only one argument");
        }
    }
    else if (strcmp(cmd[0], "horizontal") == 0)
    {
        if (taille_tableau != 1)
            puts("Warning: Any option is required for this command");
        op->flag = HORIZONTALE;
    }
    else if (strcmp(cmd[0], "vertical") == 0)
    {
        if (taille_tableau != 1)
            puts("Warning: Any option is required for this command");
        op->flag = VERTICALE;
    }
    else if (strcmp(cmd[0], "zoom") == 0)
    {
        if (taille_tableau == 2)
        {
            if (isdigitSTRING(cmd[1]))
            {
                op->flag = ZOOM;
                op->valeur = atoi(cmd[1]);
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only one argument");
        }
    }
    else if (strcmp(cmd[0], "fillColor") == 0)
    {
        if (taille_tableau == 4)
        {
            if (isdigitSTRING(cmd[1]) && isdigitSTRING(cmd[2]) && isdigitSTRING(cmd[3]))
            {
                if ((atoi(cmd[1]) <= 255) && (atoi(cmd[2]) <= 255) && (atoi(cmd[3]) <= 255))
                {
                    op->flag = REMPLIR_COULEUR;
                    op->couleur.r = atoi(cmd[1]);
                    op->couleur.g = atoi(cmd[2]);
                    op->couleur.b = atoi(cmd[3]);
                }
                else
                {
                    printError("Error : Your argument have to be between 0 and 255");
                }
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only 3 arguments");
        }
    }
    else if (strcmp(cmd[0], "contrast") == 0)
    {
        if (taille_tableau == 1)
        {
            op->flag = CONTRASTE;
            op->valeur = 255;
        }
        else if (taille_tableau == 2)
        {
            if (isdigitSTRING(cmd[1]))
            {
                if (atoi(cmd[1]) <= 255)
                {
                    op->flag = CONTRASTE;
                    op->valeur = atoi(cmd[1]);
                }
                else
                {
                    printError("Error : Your argument have to be between 0 and 255");
                }
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only one argument");
        }
    }
    else if (strcmp(cmd[0], "black-white") == 0)
    {
        if (taille_tableau == 1)
        {
            op->flag = NOIR_BLANC;
            op->valeur = 100;
        }
        else if (taille_tableau == 2)
        {
            if (isdigitSTRING(cmd[1]))
            {
                if (atoi(cmd[1]) <= 100)
                {
                    op->flag = NOIR_BLANC;
                    op->valeur = atoi(cmd[1]);
                }
                else
                {
                    printError("Error : Your argument have to be between 0 and 100");
                }
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only 1 argument");
        }
    }
    else if (strcmp(cmd[0], "negatif") == 0)
    {
        if (taille_tableau != 1)
        {
            puts("Warning: any option for this command");
        }
        op->flag = NEGATIF;
    }
    else if (strcmp(cmd[0], "brightness") == 0)
    {
        if (taille_tableau == 1)
        {
            op->flag = LUMINOSITE;
            op->valeur = 100;
        }
        else if (taille_tableau == 2)
        {
            if (isdigitSTRING(cmd[1]))
            {
                if (atoi(cmd[1]) <= 100)
                {
                    op->flag = LUMINOSITE;
                    op->valeur = atoi(cmd[1]);
                }
                else
                {
                    printError("Error : Your argument have to be between 0 and 100");
                }
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only one argument");
        }
    }
    else if (strcmp(cmd[0], "replaceColor") == 0)
    {
        if (taille_tableau == 8)
        {
            if (isdigitSTRING(cmd[1]) && isdigitSTRING(cmd[2]) && isdigitSTRING(cmd[3]) && isdigitSTRING(cmd[4]) && isdigitSTRING(cmd[5]) && isdigitSTRING(cmd[6]) && isdigitSTRING(cmd[7]))
            {
                if (atoi(cmd[1]) <= 255 && atoi(cmd[2]) <= 255 && atoi(cmd[3]) <= 255 && atoi(cmd[4]) <= 255 && atoi(cmd[5]) <= 255 && atoi(cmd[6]) <= 255 && atoi(cmd[7]) <= 255)
                {
                    op->flag = REMPLACER_COULEUR;

                    op->couleur.r = atoi(cmd[1]);
                    op->couleur.g = atoi(cmd[2]);
                    op->couleur.b = atoi(cmd[3]);

                    op->couleur2.r = atoi(cmd[4]);
                    op->couleur2.g = atoi(cmd[5]);
                    op->couleur2.b = atoi(cmd[6]);

                    op->valeur = atoi(cmd[7]);
                }
                else
                {
                    printError("Error : Your argument have to be between 0 and 255");
                }
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only 8 arguments");
        }
    }
    else if (strcmp(cmd[0], "mouse") == 0)
    {
        if (taille_tableau != 1)
        {
            perror("WARNING: any option for this command");
        }
        op->flag = SOURIS;
    }
    else if (strcmp(cmd[0], "select") == 0)
    {
        if (taille_tableau == 5)
        {
            if (isdigitSTRING(cmd[1]) && isdigitSTRING(cmd[2]) && isdigitSTRING(cmd[3]) && isdigitSTRING(cmd[4]))
            {
                op->flag = SELECT_CLAVIER;
                op->select.x = atoi(cmd[1]);
                op->select.y = atoi(cmd[2]);
                op->select.w = atoi(cmd[3]);
                op->select.h = atoi(cmd[4]);
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only 5 arguments");
        }
    }
    else if (strcmp(cmd[0], "selectMouse") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = SELECT_SOURIS;
    }
    else if (strcmp(cmd[0], "copy") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = COPIER;
    }
    else if (strcmp(cmd[0], "deselect") == 0)
    {
        op->flag = DESELECTIONNER;
    }
    else if (strcmp(cmd[0], "paste") == 0)
    {
        if (taille_tableau == 1)
        {
            op->flag = COLLER;
            op->x = 0;
            op->y = 0;
        }
        else if (taille_tableau == 3)
        {
            if (isdigitSTRING(cmd[1]) && isdigitSTRING(cmd[2]))
            {
                op->flag = COLLER;
                op->x = atoi(cmd[1]);
                op->y = atoi(cmd[2]);
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only 3 arguments");
        }

    } else if (strcmp(cmd[0], "save") == 0){
            op->flag = SAUVEGARDER;
        
    }
    else if (strcmp(cmd[0], "cancel") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = ANNULER_MODIF;
    }
    else if (strcmp(cmd[0], "removeZone") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = SUPPRIMER_ZONE;
    }
    else if (strcmp(cmd[0], "quite") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = EXIT;
    }
    else if (strcmp(cmd[0], "reframe") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = RECADRER;
    }
    else if (strcmp(cmd[0], "fermer") == 0)
    {
        if (taille_tableau != 1)
            printError("WARNING: any option for this command");
        op->flag = CLOSE_WIN;
    }
    else if (strcmp(cmd[0], "info") == 0)
    {
        if (taille_tableau == 2)
        {
            if (isdigitSTRING(cmd[1]))
            {
                op->flag = INFOPIXEL;
                op->x = atoi(cmd[1]);
                op->y = atoi(cmd[1]);
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else if (taille_tableau == 3)
        {
            if (isdigitSTRING(cmd[1]) && isdigitSTRING(cmd[2]))
            {
                op->flag = INFOPIXEL;
                op->x = atoi(cmd[1]);
                op->y = atoi(cmd[2]);
            }
            else
            {
                printError("Error : Your argument have to be an number");
            }
        }
        else
        {
            printError("Error : Your have to enter only 1 or 2 arguments");
        }
    }
    else if (strcmp(cmd[0], "export") == 0)
    {
        if (taille_tableau <= 1)
        {
            perror("ERROR: no arguments");
        }
        else if (taille_tableau > 2)
        {
            perror("ERROR: too many arguments");
        }
        else if (taille_tableau == 2)
        {

            if (isdigitSTRING(cmd[1]) != 0)
            {

                perror("ERROR ON ARGUMENT 1: is digit");
            }
            else
            {

                op->flag = EXPORT;
                size = sizeof(cmd[1]);
                op->path = malloc(size);
                memcpy(op->path, cmd[1], size);
            }
        }
    }
    else if (strcmp(cmd[0], "help") == 0)
    {
        if (taille_tableau != 1)
            puts("WARNING: any option for this command");
        op->flag = HELP;
    }
    else
    {
        printError("The command is not recognized by the system");
    }
}