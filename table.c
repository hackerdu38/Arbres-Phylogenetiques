#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "table.h"
#include "listes.h"
#include "arbres.h"
#include "especes.h"

int lire_csv(char * nom_fichier, table_de_correspondance * T){
	FILE * f = fopen(nom_fichier, "r");
	if (f==NULL){
		printf("Le fichier ne peut pas être ouvert en lecture\n");
		return 0;
	}

	char * ligne = NULL ;
	fscanf(f,"%s\n", ligne);
	int moti = 0;
	int cpt_virgule = -1;
	for (int i = 0 ; ligne[i]!= 0; i++ ){
		if (ligne[i]== ',') {
			moti = 0;
			cpt_virgule ++ ;
    }
		else {
			if (cpt_virgule >= 0) {
				(*T).noms_car.tab[cpt_virgule][moti] = ligne[i];
				(*T).noms_car.longueur ++;
				moti++;
			}
		}
	}
	int li =0 ;
	while (!feof(f)){
		fscanf(f,"%s\n", ligne);
		moti = 0;
		cpt_virgule = -1;
		for (int i = 0 ; ligne[i]!= 0; i++ ){
			if (ligne[i]== ',') {
				cpt_virgule ++ ;
			}
			else {
				if (cpt_virgule < 0) {
					(*T).noms_esp.tab[cpt_virgule][moti] = ligne[i];
					(*T).noms_esp.longueur++;
					moti++;
				}
				else {
					(*T).tab[cpt_virgule][li] = '0'-ligne[i];
				}

			}


		}
    li++;

	}

  fclose(f);
	return 1;

}

int recup_max(sequence_int lignes, sequence_int colonnes, table_de_correspondance T){
	int max = -1;
	int indic = -1;
	for (int i=0; i< lignes.longueur; i++){
		int compt = 0;
		for (int j=0; j<colonnes.longueur; j++){
			if (T.tab[i][j]) compt +=1;
		}
		if (compt >= max || colonnes.longueur - compt >= max ){
			max = compt;
			indic = i;
		}
	}
	return indic;
}

void faire_arbre (sequence_int lignes, sequence_int colonnes, table_de_correspondance T, arbre *A){
	if (lignes.longueur == 0){
		A= NULL;
	}
	else if (lignes.longueur == 1 && colonnes.longueur == 0){
		noeud* n = nouveau_noeud();
		n->valeur.nom = strdup(T.noms_esp.tab[lignes.tab[0]]);
		n->valeur.nature = ESPECE;
		*A = n;
	} else {
		int indice = recup_max(lignes, colonnes, T); //On recupere l'indice dans noms_car
		noeud* n2 = nouveau_noeud();
		n2 -> valeur.nom= strdup( T.noms_car.tab[indice]);
		n2->valeur.nature = CARACT;
		*A = n2;
		sequence_int ligne_droit;
		ligne_droit.longueur = 0;
		sequence_int ligne_gauche;
		ligne_droit.longueur = 0;
		for (int i = 0; i< lignes.longueur; i++){
			if (T.tab[colonnes.tab[indice]][lignes.tab[i]]){
				ligne_droit.tab[ligne_droit.longueur]= lignes.tab[i];
				ligne_droit.longueur += 1;
			} else {
				ligne_gauche.tab[ligne_gauche.longueur] = lignes.tab[i];
				ligne_droit.longueur += 1;
			}
		}
		colonnes.tab[indice] = colonnes.tab[colonnes.longueur-1];
		colonnes.longueur = colonnes.longueur -1;
		faire_arbre(ligne_droit, colonnes, T, &((*A)->droit));
		faire_arbre(ligne_gauche, colonnes, T, &((*A)->gauche));
	}
}
