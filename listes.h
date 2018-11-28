#ifndef _LISTES_H
#define _LISTES_H


typedef struct cellule_t cellule_t;

struct cellule_t{
	char *valeur;
	cellule_t *suivant;
};

struct liste{
	cellule_t* tete;
};

typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */



#endif /* _LISTES_H */
