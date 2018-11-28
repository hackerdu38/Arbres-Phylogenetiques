/* Structures de données autour des espèces */
#ifndef _ESPECE_H_
#define _ESPECE_H_
#include "listes.h"
enum type {ESPECE, CARACT} ;

typedef struct {
  enum type nature;
  char * nom;
} val_n;

typedef struct {
  char nom[100];
  liste_t caract;
} espc;

espc creer_espece(char *nom);
#endif
