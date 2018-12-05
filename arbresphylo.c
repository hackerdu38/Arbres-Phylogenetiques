#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"



int hauteur (arbre racine){
//Renvoie la hauteur d'un arbre
	if (racine == NULL){
		return 0;
	}else{
		int gauche, droit;
		gauche = 1 + hauteur(racine->gauche);
		droit = 1+hauteur(racine->droit);
		if (gauche > droit){
			return gauche;
		}else{
			return droit;
		}
	}
}

/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 * Définissez un type de retour approprié !
 */

void construire_arbre(arbre * a, espc espece){
	if ((espece.caract).tete == NULL){
		noeud * n = nouveau_noeud();
		n->valeur.nom = strdup(espece.nom);
		(n->valeur).nature=ESPECE;
		*a = n;
	}
	else {
		noeud * n = nouveau_noeud();
		n->valeur.nom = strdup((espece.caract.tete)->valeur);
		(n->valeur).nature=CARACT;
		supprimer_caract((espece.caract.tete)->valeur,&(espece.caract));
		*a= n;
		construire_arbre(&((*a)->droit), espece);
	}
}


int rechercher_espece (arbre racine, espc *espece){
/*Pour rechercher et afficher les caractéristiques d'une espèce dans un arbre.
On renvoie un entier selon si l'on a trouvé ou non l'espèce dans l'arbre.*/

	if (racine == NULL){ //Si l'arbre est vide, l'espece n'y appartient pas
		return 0;
	}
	else if (!(strcmp(racine->valeur.nom, espece->nom))){ //Si l'on trouve l'espèce
		if (!est_espece(racine->valeur)) printf("Ce que vous recherchez n'est pas une espece.\n");
		return 1;
	}
	else { //On effectue un appel récursif de la fonction.
		int trouve_a_gauche,trouve_a_droite;
		trouve_a_gauche = rechercher_espece(racine->gauche, espece);
		trouve_a_droite = rechercher_espece(racine->droit, espece);
		if (trouve_a_gauche) return 1;
		if (trouve_a_droite) {
		//On n'ajoute l'élément à la liste que si l'espèce se trouve à droite, celà signifie qu'elle possède bien cette caractéristique, si on trouve l'espece a gauche de l'élément, cela signifie qu'elle ne possède pas la caractéristique et qu'il ne faut pas l'ajouter à la séquence.
			ajouter_debut(racine->valeur.nom, &(espece->caract)) ;
			return 1;
		}
	}
	return 0;
}

/* ACTE III */
/* Ajoute une espèce à un arbre, renvoie
 */

/* ACTE III-B */

void caract_profondeur(arbre racine, int profondeur, liste_t* caracts)
{
  /*
  if hauteur(racine)<profondeur {
    //dans ce cas on retourne directement 1 sans remplire caracts.
    return ;
  }
  */
  
	if (profondeur >= 1) {
	  //descendre d'un étage à gauche et droite avec profondeur-1
	  if (racine->gauche !=  NULL) {
	    caract_profondeur(racine->gauche, profondeur-1, caracts);
	  }
	  if (racine->droit !=  NULL) {
	    caract_profondeur(racine->droit, profondeur-1, caracts);
	  } 
	}  
	if (profondeur == 0) {
		if (racine->valeur.nature == CARACT){
		  ajouter_debut(racine->valeur.nom, caracts);
		}
		return;
	}
}









int ajouter_espece (arbre * a, espc espece){
	if ((*a)==NULL){
		printf("(null) Construction du nouvel arbre...\n");
		construire_arbre(a, espece);
		return 1;
	}
	else if ((*a)->valeur.nature == ESPECE) {
		if ((espece.caract.tete)==NULL){
			printf("Une espèce (%s) a déjà ces caractéristiques !\n", (*a)->valeur.nom);
			return 0;
		}
		else {
			printf("Construction du nouvel arbre...\n");
			noeud * n = nouveau_noeud();
			(n->valeur).nom = strdup((espece.caract.tete)->valeur);
			(n->valeur).nature=CARACT;
			(n->gauche) = *a ;
			(n->droit) = NULL ;
			(*a) = n;
			supprimer_caract((*a)->valeur.nom, &(espece.caract));
			construire_arbre(&((*a)->droit), espece);
			return 1;

		}
	}
	else {
		if (appartient((*a)->valeur.nom, &(espece.caract))){
			//printf("appartient ok : %s\n", (*a)->valeur.nom);
			supprimer_caract((*a)->valeur.nom, &(espece.caract));
			//printf("caracteristiques restantes : %s\n", espece.caract.tete->valeur);
			return ajouter_espece(&((*a))->droit, espece);
		}
		else return ajouter_espece(&((*a)->gauche), espece);

	}
}
