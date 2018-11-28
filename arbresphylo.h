#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include "listes.h"

/* Renvoie la hauteur de l'arbre passé en argument */
int hauteur (arbre racine);

/* Recherche une espèce dans l'arbre et renvoie en argument
 * la séquence de ses caractéristiques.
 * Note: vous devez définir un type séquence approprié et modifier le
 * type de retour de cette fonction.
 */
void ajouter_debut(char *valeur, liste_t *seq);

int rechercher_espece (arbre racine, espc *espece);



#endif
