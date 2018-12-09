#ifndef TABLE_H
#define TABLE_H
#define TAILLE_LIM 1000

#include "listes.h"
#include "arbres.h"

typedef struct matrice table_de_correspondance;
struct matrice {
	int tab[TAILLE_LIM][TAILLE_LIM];
	sequence_str noms_car;
	sequence_str noms_esp;
};

int lire_csv(char * nom_fichier, table_de_correspondance *t);
int recup_max(sequence_int lignes, sequence_int colonnes, table_de_correspondance T);
void faire_arbre (sequence_int lignes, sequence_int colonnes, table_de_correspondance T, arbre *A);

#endif
