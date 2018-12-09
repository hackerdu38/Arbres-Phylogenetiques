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

int lire_csv(char * nom_fichier, table_de_correspondance * T){//lit un fichier ecrit comme en format csv (ligne d'en tete puis donnees separees par des virgules)
	FILE * f = fopen(nom_fichier, "r");
	if (f==NULL){
		printf("Le fichier ne peut pas être ouvert en lecture\n");
		return 0;
	}

	char * ligne = NULL ;
	fscanf(f,"%s\n", ligne); // on recupere la ligne d'en tete censée contenir les caractéristiques
	int moti = 0;
	int cpt_virgule = -1; // on ne veut pas du premier indice (qui indique simplement la colonne des especes)
	for (int i = 0 ; ligne[i]!= 0; i++ ){
		if (ligne[i]== ',') { // à chaque virgule, on va stocker le nom de la caractéristique suivante
			moti = 0;
			cpt_virgule ++ ;
    }
		else {
			if (cpt_virgule >= 0) { //on ecrit dans la séquence de caractéristique ce que l'on lit
				(*T).noms_car.tab[cpt_virgule][moti] = ligne[i];
				(*T).noms_car.longueur ++;
				moti++;
			}
		}
	}
	int li =0 ;
	while (!feof(f)){//on lit ensuite les lignes du fichier jusqu'à la fin
		fscanf(f,"%s\n", ligne);
		moti = 0;
		cpt_virgule = -1; // on distingue le nom de l'espece, que  l'on place dans la sequence prevue à cet effet
		for (int i = 0 ; ligne[i]!= 0; i++ ){
			if (ligne[i]== ',') {//les donnees sont separees par des virgules
				cpt_virgule ++ ;
			}
			else {
				if (cpt_virgule < 0) {// on distingue le nom de l'espece, que  l'on place dans la sequence prevue à cet effet
					(*T).noms_esp.tab[cpt_virgule][moti] = ligne[i];
					(*T).noms_esp.longueur++;
					moti++;
				}
				else {//on rentre les donnes (0 ou 1)
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
  //cherche la colonne du sous tableau de T (défini par les indices de ses lignes et colonnes à considérer) avec le maximum de 0 ou de 1
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


table_de_correspondance creertablevide(){ //creer une table de correspondance vide
  table_de_correspondance T;
  T.noms_car.longueur = 0;
  T.noms_esp.longueur = 0;
  return T;
}
void faire_arbre (sequence_int lignes, sequence_int colonnes, table_de_correspondance T, arbre *A){
  //construit un arbre a partir de la table de correspondance
	if (lignes.longueur == 0){//la table ne contient pas d'espece
		A= NULL;
	}
	else if (lignes.longueur == 1 && colonnes.longueur == 0){//la table contient une espece et aucune caracteristique
		noeud* n = nouveau_noeud();
		n->valeur.nom = strdup(T.noms_esp.tab[lignes.tab[0]]);
		n->valeur.nature = ESPECE;//on place alors une feuille contenant l'espece
		*A = n;
	} else {
		int indice = recup_max(lignes, colonnes, T); //On recupere l'indice dans noms_car du caractere qui semble le plus haut dans l'arbre
		noeud* n2 = nouveau_noeud();
		n2 -> valeur.nom= strdup( T.noms_car.tab[indice]);
		n2->valeur.nature = CARACT; // on fait un noeud avec cette caracteristique
		*A = n2;
		sequence_int ligne_droit;
		ligne_droit.longueur = 0;
		sequence_int ligne_gauche;
		ligne_droit.longueur = 0;
		for (int i = 0; i< lignes.longueur; i++){ // on genere les sequences d'entiers definissant les sous tableau à utiliser pour l'appel recursif
			if (T.tab[colonnes.tab[indice]][lignes.tab[i]]){ //On ajoute les lignes avec un '1' pour le caractere courant dans la liste de celles à traiter du côté droit (VRAI)
				ligne_droit.tab[ligne_droit.longueur]= lignes.tab[i];
				ligne_droit.longueur += 1;
			} else { //On ajoute les lignes avec un '0' pour le caractere courant dans la liste de celles à traiter du côté gauche (FAUX)
				ligne_gauche.tab[ligne_gauche.longueur] = lignes.tab[i];
				ligne_droit.longueur += 1;
			}
		}
		colonnes.tab[indice] = colonnes.tab[colonnes.longueur-1];
		colonnes.longueur = colonnes.longueur -1; //on supprime la colonne du caractere que l'on vient de traiter
		faire_arbre(ligne_droit, colonnes, T, &((*A)->droit)); 
		faire_arbre(ligne_gauche, colonnes, T, &((*A)->gauche));
	}
}
