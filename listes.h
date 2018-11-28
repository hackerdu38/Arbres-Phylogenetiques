#ifndef _LISTES_H
#define _LISTES_H



typedef struct cellule_t cellule_t;
struct cellule_t{
	char valeur[100];
	cellule_t *suivant;
};



struct liste{
	cellule_t* tete;
};



typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

void name(char * nom, cellule_t * cel);
cellule_t * creer_cellule(char *nom);
void ajouter_debut(char *valeur, liste_t *seq);
void supprimer_caract(char * caract, liste_t *seq);
int appartient(char * val, liste_t *seq);


#endif /* _LISTES_H */
