#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "table.h"
#include "arbresphylo.h"
#include "especes.h"


void vider_buffer(){ //vide la saisie au clavier poue éviter les résidus
	char c= 0;
	while (c != '\n'&& c != EOF) c = getchar();
}

int open(arbre * mon_arbre){ //ouvre un arbre dans l'arbre courant
  FILE * f ;
  printf("Entrez le chemin du fichier arbre à ouvrir : \n");
  char nom[1000]={0};
  fscanf(stdin, "%s", nom);
  vider_buffer();
  f = fopen(nom,"r");
  if (f==NULL){
      fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", nom);
      perror (nom);
      return 0;
  }

  (*mon_arbre) = lire_arbre (f);
  fclose(f);
  return 1;
}

int opentable(arbre * mon_arbre){ //ouvre une table de correspondance et la convertit en arbre dans l'arbre courant
  //ne fonctionne pas (seg fault ici même)
  printf("Entrez le chemin du fichier tableau à ouvrir : \n");
  char nom[1000]={0};
  fscanf(stdin, "%s", nom);
  vider_buffer();

  table_de_correspondance T = creertablevide();
  if (!(lire_csv("tests/tableau_a_lire.csv", &T))) return 0;
  sequence_int lignes;
  for (int i = 0; i< T.noms_esp.longueur ; i++){
    lignes.tab[i]=i;
    lignes.longueur ++;
  }
  sequence_int colonnes;
  for (int i = 0; i< T.noms_car.longueur ; i++){
    colonnes.tab[i]=i;
    colonnes.longueur ++;
  }

  faire_arbre(lignes,colonnes,T, mon_arbre);
  return 1;

}

int ajoutesp(arbre * mon_arbre){ //ajoute une espece dans l'arbre courant
  printf("Entrez le nom de l'espèce à ajouter :\n");
  char espaj[100];
  fscanf(stdin,"%s", espaj);
  vider_buffer();
  printf("Entrez le nombre de caractéristiques de l'espèce :\n");
  int nb;
  fscanf(stdin,"%d", &nb);
  vider_buffer();
  espc espece_a_ajouter = creer_espece(espaj);
  char car[100];
  printf("Entrez les caractéristiques :\n");
  for (int i =0; i<nb ; i++){
    printf("#%d : ", i+1);
    fscanf(stdin, "%s",car);
    vider_buffer();
    ajouter_debut(car, &(espece_a_ajouter.caract));
  }
  return (ajouter_espece(mon_arbre,espece_a_ajouter));
}

int recherchesp(arbre mon_arbre){ //recherche une espece dans l'arbre courant
  char esp[100];
  printf("Entrez l'espece a rechercher\n");
	scanf("%s", esp);
  vider_buffer();
  espc espece = creer_espece(esp);
	if (!rechercher_espece(mon_arbre, &espece)) return 0; //Met dans la strcture espece la liste des caractéristiques de l'espèce recherchée.)
	printf("Les caractéristiques de cet animal sont : \n");
	cellule_t* courant;
	courant = (espece.caract).tete;
	while(courant != NULL){ // Affiche la séquence.
		printf("%s / ", courant->valeur);
		courant = courant -> suivant;
	}
	printf("\n");
  return 1;
}

int ecrire(arbre mon_arbre){
  /* ---------------------------
  ---- A COMPLETER -------------
  ----------------------------*/
  return 1;
}

int main(int argc, char* argv[]) {
  arbre mon_arbre = NULL;

  if (argc > 2) { // trop d'arguments
      fprintf (stderr, "Usage:  %s [<fichier_arbre>]\n", argv[0]);
      fprintf (stderr, "\n");
      exit(1);
  }
  else { // on ouvre le fichier passé en argument s'il existe
      if (argc == 2){
        FILE * f ;
        f = fopen(argv[1],"r");
        if (f==NULL) {
            fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", argv[1]);
            perror (argv[1]);
        }

      mon_arbre = lire_arbre (f);
      fclose(f);
      free(f);
      }
  }

  // on lance le mainloop

  char commande='n';
  char reponse[100];
  while(commande!='s'){
    printf("\n# o : Ouvrir un arbre\n# u : Ouvrir une table\n# p : Afficher l'arbre\n# a : Ajouter une espèce à l'arbre\n# r : Rechercher une espèce dans l'arbre\n# w : Écrire l'arbre dans un fichier\n# s : Terminer le programme\n");
    fscanf(stdin,"%s", reponse);
    commande = reponse[0];
    vider_buffer();
    switch(commande){ //on peut manipuler les arbres avec diverses commandes
      case 'o' :
        if (open(&mon_arbre)) printf("Ouverture réussie !\n" );
        break;
      case 'u' :
        printf("Attention : Cette fonction va causer une erreur de segmentation localisée sur un printf().\nNous n'avons pas pu résoudre ce problème et ne pouvons donc même pas tester cette fonction.\n(Entrer un caractère pour continuer...)\n");
        scanf("\n ");
        if (opentable(&mon_arbre)) printf("Ouverture réussie !\n" );
        break;
      case 'p':
        affiche_arbre (mon_arbre);
        printf ("Hauteur de l'arbre: %d\n", hauteur (mon_arbre));
        break;
      case 'a' :
        if (ajoutesp(&mon_arbre)) printf("Ajout réussi !\n" );
        break;
      case 'r' :
        if (!recherchesp(mon_arbre)) printf("L'espèce est introuvable.\n" );
        break;

      case 'w' :
        if (ecrire(mon_arbre))  printf("Enregistrement réussi.\n" );
        break;
      default : break;
    }
  }
  free(mon_arbre);
  free(reponse);
  return 0;
}
