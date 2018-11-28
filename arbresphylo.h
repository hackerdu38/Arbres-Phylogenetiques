#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include "listes.h"
#include "especes.h"

/* Renvoie la hauteur de l'arbre passé en argument */
int hauteur (arbre racine);

/* Recherche une espèce dans l'arbre et renvoie en argument
 * la séquence de ses caractéristiques.
 * Note: vous devez définir un type séquence approprié et modifier le 
 * type de retour de cette fonction.
 */
void ajouter_debut(char *valeur, liste_t *seq);

int rechercher_espece (arbre racine, char *espece, liste_t* seq);

//APP III-B
void caract_profondeur(arbre racine, int profondeur, liste_t * caracts);


#endif
