/* Structures de données autour des espèces */
#ifndef _ESPECE_H_
#define _ESPECE_H_
#define LISTE_CARAC_MAX 100
enum type {ESPECE, CARACT} ;

typedef struct {
  enum type nature;
  char * nom;
} val_n;

typedef struct {
  char nom[100];
  char caract[100][100];
} espece;

//inutile pour le moment, à utiliser pour ajouter_debut dans arbresphylo.c + propre
typedef struct {
  val_n v[LISTE_CARAC_MAX];
  int l;
} l_carac;
  
#endif
