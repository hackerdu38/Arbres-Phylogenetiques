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
  stringcopie(cel->valeur, nom);
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
  if (stringcomp(courant->valeur,caract)) seq->tete = seq->tete->suivant;
  else {
    while (courant->suivant != NULL && strcmp(courant->suivant->valeur,caract)){
      courant = courant->suivant;
    }
    if (courant->suivant != NULL) courant->suivant = courant->suivant->suivant;
  }
}

int stringcomp(char * val1, char * val2){
  int i=0;
  while(val1[i]!=0 && val2[i]!=0){
    if (val1[i]!= val2[i]) return 0;
    i++;
  }
  return (val1[i]==val2[i]);
}

void stringcopie(char * val1, char * val2){
  int i=0;
  if (val2 == NULL) return;
  while(val2[i]!=0){
    val1[i] = val2[i];
    i++;
  }
  val1[i]=0;
}

int appartient(char * val, liste_t *seq){
  cellule_t * courant = seq->tete;
  if (seq->tete ==NULL) return 0;
  else {
      while (courant != NULL){
        if (stringcomp(val,courant->valeur)) return 1;
        courant = courant->suivant;
      }
    return 0;
  }
}
