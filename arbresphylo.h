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

 void construire_arbre(arbre a, espc espece);

int rechercher_espece (arbre racine, espc *espece);

int ajouter_espece(arbre a, espc espece);

#endif
