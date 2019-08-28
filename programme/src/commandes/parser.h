

#ifndef __PARSER__

#define __PARSER__

#include "../options.h"

int split(const char *str, char c, char ***arr);
int isdigitSTRING(char *ch);
char *trim(char *s);
char *trimSpace(char *s);
void parser(options *op, char *commande);

#endif
