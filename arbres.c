#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "arbres.h"
#include "listes.h"
#include "especes.h"

noeud* nouveau_noeud(void)
{
    noeud *n = (noeud*)malloc(sizeof(noeud));
    assert (n!=NULL);
    (n->valeur).nom = NULL;
    (n->valeur).nature = 0;
    n->gauche = NULL;
    n->droit  = NULL;
    return n;
}


/* buffer pour lire les caractères des espèces sous forme de "mots" (words) */
#define MAX_WORD_SIZE 255
char buffer[MAX_WORD_SIZE+1];

/* Variable globale qui contient le prochain caractère à traiter */
static char next_char = ' ';

/* Supprime tous les espaces, tabulations, retour à la ligne */
#define GLOB(f) \
    while(isspace(next_char)) { \
        next_char = fgetc(f);\
    }


/* Fonction récursive qui lit un sous-arbre */
/* Appelée une fois à la racine (debut du fichier), puis récursivement
 * pour chaque nœud interne rencontré. */
arbre lire_arbre(FILE *f)
{
    arbre racine;

    GLOB(f); /* lit dans next_char le premier caractère non vide */

    if (next_char == '/') {
        next_char = ' '; /* on ne garde pas / en mémoire */
        return NULL;
    }



    if (next_char == ')') {
        return NULL;
    }

    if (next_char != '(') {
        fprintf(stderr, "Error while reading binary tree : '(' or ')' expected at position %ld\n", ftell(f));
        exit (1);
    }

    /* On remplit le buffer tant qu'on lit des caractères alphanumériques */
    char *p = buffer; /* début du buffer */
    next_char = ' '; GLOB(f);

    do {
        *p = next_char;       /* sauvegarde du char courant */
        next_char = fgetc(f);
        p++;
        assert (p < buffer + MAX_WORD_SIZE);
    } while (! isspace (next_char) && next_char != '(' && next_char != ')');
    /* on arrète si le char suivant est un espace ou une parenthèse */
    *p='\0'; /* on ferme la chaîne de caractères dans le buffer */

    racine = nouveau_noeud();
    (racine->valeur).nom = strdup(buffer); /* dupliquer le mot lu */

    GLOB(f);

    if (next_char == ')') {
        (racine->valeur).nature = ESPECE;
        next_char = ' '; /* on est sur une feuille, on prépare la lecture du prochain nœud */
    }
    else {
        (racine->valeur).nature = CARACT;
        racine->gauche = lire_arbre (f); /* appel récursif pour le fils gauche */
        racine->droit  = lire_arbre (f); /* idem pour le droit */

        GLOB(f); /* lit jusqu'au ')' fermant */

        if (next_char != ')') {
            fprintf(stderr, "Error while reading binary tree: ')' expected\n");
            exit(1);
        }
        next_char = ' '; /* on ne garde pas la parenthèse en mémoire */
    }
    return racine;
}



void affiche_arbre (noeud *racine){
//Fonction qui permet l'affichage de l'arbre via Graphviz en utilisant le script "affichage"

	if (racine == NULL){
		printf("L'arbre est vide.\n");//Il n'y a rien à afficher
    return;
	}else{ //On crée un fichier dans lequel on va écrire les instructions
		FILE * f;
		f = fopen("arbre.dot", "w");
		fprintf(f, "digraph arbre { \n");
		sequence a_traiter; //On fait un parcours en largeur, on stocke tous les etats dans une "file d'attente" sous forme de tableau
		a_traiter.tab[0]= *racine;
		a_traiter.longueur = 1;
		int k = 0;
		while (k != a_traiter.longueur){ //Tant qu'il y a des éléments dans "a_traiter"
			if (a_traiter.tab[k].gauche != NULL){ //S'il y a un fils gauche, on écrit l'instruction dans le fichier
				fprintf(f, "	%s -> %s [label = \"non\"]\n", a_traiter.tab[k].valeur.nom , a_traiter.tab[k].gauche->valeur.nom);
				a_traiter.longueur ++; //Puis on ajoute le fils à la séquence d'éléments à traiter
				a_traiter.tab[a_traiter.longueur -1]= *(a_traiter.tab[k].gauche);
			}
			if (a_traiter.tab[k].droit != NULL){ //On fait la même chose pour le fils droit s'il existe
				fprintf(f, "	%s -> %s [label = \"oui\"]\n", a_traiter.tab[k].valeur.nom , a_traiter.tab[k].droit->valeur.nom);
				a_traiter.longueur ++;
				a_traiter.tab[a_traiter.longueur -1]= *(a_traiter.tab[k].droit);
			}
			k++;
		}
		fprintf(f,"}");
		fclose(f);
	}
	if (fopen("affichage", "r") != NULL){
		printf("(affichage) Veuillez patienter pour l'affichage de l'arbre.\n(affichage) Vous pouvez continuer vos opérations en attendant.\n");
		system("./affichage"); //pour l'affichage avec Graphviz
	}else{
		printf("Fichier script 'affichage' inexistant, veuillez procéder à l'affichage à la main");
	}
}
