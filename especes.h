/* Structures de données autour des espèces */
#ifndef _ESPECE_H_
#define _ESPECE_H_

enum type {ESPECE, CARACT} ;

typedef struct {
  enum type nature;
  char * nom;
} val_n;

typedef struct {
  char nom[100];
  char caract[100][100];
} espece;

#endif
