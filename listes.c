#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listes.h"


cellule_t * creer_cellule(char * nom){
    //noeud *n = (noeud*)malloc(sizeof(noeud));
    cellule_t *p = (cellule_t *)malloc(sizeof(cellule_t));
    name(nom,p);
    p->suivant=NULL;
    return p;
}

void name(char* nom, cellule_t * cel){
  strcpy(cel->valeur, nom);
}

void ajouter_debut(char *valeur, liste_t *seq){
//Fonction qui ajoute une cellule au début d'une liste chaînée donc la valeur est passée en argument.
	cellule_t* new = creer_cellule(valeur);
	if (seq -> tete == NULL){
		seq->tete = new;
		new->suivant = NULL;
	}else{
		new->suivant= (seq->tete);
		seq->tete = new;
	}
	cellule_t* courant;
	courant = seq->tete;
}

void supprimer_caract(char * caract, liste_t *seq){
  cellule_t * courant = seq->tete;
  if (seq->tete ==NULL) return;
  if (strcmp(courant->valeur,caract)) seq->tete = seq->tete->suivant;
  else {
    while (courant->suivant != NULL && strcmp(courant->suivant->valeur,caract)){
      courant = courant->suivant;
    }
    if (courant->suivant != NULL) courant->suivant = courant->suivant->suivant;
  }
}


int appartient(char * val, liste_t *seq){
  cellule_t * courant = seq->tete;
  int i;
  if (seq->tete ==NULL) return 0;
  else {
    while (courant != NULL){
      i=0;
      while(val[i]!=0 && (courant->valeur)[i]!=0)
      if (strcmp(courant->valeur,val)) return 1;
      courant = courant->suivant;
    }
    return 0;
  }
}
